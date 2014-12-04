#ifndef WBOARDDEFS_H
#define WBOARDDEFS_H




// #define TOTAL_PINS 10
// #define TOTAL_ANALOG_PINS 2
// #define FIRST_ANALOG_PIN 24
/*! The following code is based on modifying the registers here
* http://g-lab.ca/esp8266ex-gpio-registers/
* and example code here 
* http://g-lab.ca/esp8266ex-gpio-application-programming-interface/
* To conform to http://wiring.org.co/reference
*/
// #define WIRING_PORTS 4

// #define LEDGPIO 2

// gpio_output_set((1<<LEDGPIO), 0, (1<<LEDGPIO), 0);
// gpio_output_set(0, (1<<LEDGPIO), (1<<LEDGPIO), 0);


// PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
// PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);





#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14

#define PIN_15 15

#define PORTA 0
#define PA0 PIN_0
#define PA1 PIN_1
#define PA2 PIN_2
#define PA3 PIN_3
#define PA4 PIN_4
#define PA5 PIN_5
#define PA6 PIN_6
#define PA7 PIN_7



#define PORTB 0
#define PB0 PIN_8
#define PB1 PIN_9
#define PB2 PIN_10
#define PB3 PIN_11
#define PB4 PIN_12
#define PB5 PIN_13
#define PB6 PIN_14
#define PB7 PIN_15




#endif