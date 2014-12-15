#include "BoardDefs.h"
#include "wiring.h"
#include "ets_sys.h"
#include "gpio.h"
#include "eagle_soc.h"
#include "osapi.h"
#include "user_interface.h"

extern void ets_isr_attach(int intr, void *handler, void *arg);
extern void ets_isr_mask(unsigned intr);
extern void ets_isr_unmask(unsigned intr);

static int port_a[] = {PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7};
static int port_b[] = {PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7};

void pullup(int inpin)
{
	PIN_PULLUP_EN(inpin);

}

void noPullup(int inpin)
{
	PIN_PULLUP_DIS(inpin);
}

void pinMode(int pin, int is_output)
{
	// Set GPIO12 as input, then gpio_output_set (0, 0, 0, BIT12).
	if(is_output == INPUT)
	{
		GPIO_DIS_OUTPUT(pin);
	}
	else{
		GPIO_OUTPUT_SET(pin,0);
	}
}

void digitalWrite(int outpin, int val)
{
	GPIO_OUTPUT_SET(outpin,val & 0x1);
}

int digitalRead(int pin)
{
	return GPIO_INPUT_GET(pin);
}

int* getPortPins(int port)
{
	int * port_pins;
	if(port == PORTA)
	{
		port_pins = &port_a[0];
	}
	else if(port == PORTB)
	{
		port_pins = &port_b[0];
	}
	else
	{
		return 0x0;
	}
}

int portMode(int port,int is_output)
{
	int * port_pins = getPortPins(port);
	int lcv;

	if(port_pins == 0)
		return INVALID_PORT;

	for(lcv=0;lcv<8;lcv++)
	{
		pinMode(port_pins[lcv],is_output);
	}
}

int portRead(int port)
{
	int * port_pins = getPortPins(port);;
	int result = 0;
	int lcv = 0;
	if(port_pins == 0)
		return INVALID_PORT;	
	for(lcv=0;lcv<8;lcv++)
	{
		result |= digitalRead(port_pins[lcv]) << lcv;
	}
	return result;
}

int portWrite(int port, int byte)
{
	int * port_pins = getPortPins(port);;
	int result = 0;
	int lcv = 0;

	if(port_pins == 0)
		return INVALID_PORT;

	for(lcv=0;lcv<8;lcv++)
	{
		result = (byte >> lcv) & 0x1;
		digitalWrite(port_pins[lcv], result);
	}
}



INT_FUNC interrupt_functions[16] ={0};

void interrupt_handler(int8_t key)
{
	int pin = 0;
	uint32_t gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

	for(pin=0;pin<16;pin++)
	{
		if((gpio_status >> pin) & 0x1)
		{
			//Debounce interrupt timer???
			//gpio_pin_intr_state_set(GPIO_ID_PIN(0), GPIO_PIN_INTR_DISABLE);
			//    os_timer_disarm(&some_timer);
			//    os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);
			//   os_timer_arm(&some_timer, 50, 0);
			/*End of Debounce logic */

			/*TODO Maybe fire off a thread call to avoid user from getting watchdogs occuring*/
			/*Call the function that works the interrupt*/
			if(interrupt_functions[pin] != 0x0)
				interrupt_functions[pin](); 

			//clear interrupt status
			GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status & BIT(0));
		}
	}


}
int interruptMode(unsigned char interrupt,int mode)
{
	int pin_number = interrupt;
	int int_mode = GPIO_PIN_INTR_DISABLE;
	/*GPIO_PIN_INTR_DISABLE = 0, ESP Has the following interrupt typtes 
	GPIO_PIN_INTR_POSEDGE = 1,
	GPIO_PIN_INTR_NEGEDGE = 2,
	GPIO_PIN_INTR_ANYEGDE = 3,
	GPIO_PIN_INTR_LOLEVEL = 4,
	GPIO_PIN_INTR_HILEVEL = 5*/
	switch(mode)
	{
		case RISING:
			int_mode = GPIO_PIN_INTR_POSEDGE;
		break;
		case FALLING:
			int_mode = GPIO_PIN_INTR_NEGEDGE;
		break;
		case CHANGE:
			int_mode = GPIO_PIN_INTR_ANYEGDE;
		break;
		case HIGH:
			int_mode = GPIO_PIN_INTR_HILEVEL;
		break;
		case LOW:
			int_mode = GPIO_PIN_INTR_LOLEVEL;
		break;
		case DISABLED:
			int_mode = GPIO_PIN_INTR_DISABLE;
			break;
		default:
			return -1; /*TODO Error codes*/
	}
	gpio_pin_intr_state_set(GPIO_ID_PIN(pin_number), int_mode);
	return 0;
}
int attachInterrupt(unsigned char interrupt, INT_FUNC function , int mode)
{	
	int pin_number = interrupt;
	int status = 0;
	interrupt_functions[pin_number] = function;

	status = interruptMode(interrupt,mode);
	if( status != 0)
	{
		return status;
	}
	

	ETS_GPIO_INTR_ATTACH(interrupt_handler,0x0);
    ETS_GPIO_INTR_DISABLE();
    /*WTF IS THIS STUFF DOING? */
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
//    gpio_output_set(0, 0, 0, GPIO_ID_PIN(pin_number));
    gpio_register_set(GPIO_PIN_ADDR(pin_number), 
    		GPIO_PIN_INT_TYPE_SET(GPIO_PIN_INTR_DISABLE)
          | GPIO_PIN_PAD_DRIVER_SET(GPIO_PAD_DRIVER_DISABLE)
          | GPIO_PIN_SOURCE_SET(GPIO_AS_PIN_SOURCE)
          );
	
	//clear gpio status
    GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, BIT(pin_number));
 	status = interruptMode(interrupt,mode);
    //enable interrupt

    ETS_GPIO_INTR_ENABLE();
}

int detachInterrupt(unsigned char interrupt)
{
	int pin = interrupt;
	//interrupt_functions[pin] = 0x0;
	//disable interrupt
    gpio_pin_intr_state_set(GPIO_ID_PIN(pin), GPIO_PIN_INTR_DISABLE);
}

void interrupts()
{
	ETS_GPIO_INTR_ENABLE();
}

void noInterrupts()
{
	ETS_GPIO_INTR_DISABLE();
}

unsigned long millis(void) {
    return system_get_time()/1000L;
}

unsigned long micros(void) {
    return system_get_time();
}

void delay(unsigned long ms) {
	delayMicroseconds(ms*1000);
}

void delayMicroseconds(unsigned long us) {
    os_delay_us(us);
}
