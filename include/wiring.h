#ifndef WIRING_H
#define WIRING_H


/*!
* @brief Pullup resistors are used in circuits to ensure that an input pin 
* settle at an expected logical value (HIGH) when the pin is disconnected or 
* high-impedance. The pullup() method sets the core processors internal pullup 
* resistor on a pin. By default the internal pullup is disabled.
*/
void pullup(int inpin);

/*!
* @brief Pullup resistors are used in circuits to ensure that an input pin settle at 
* an expected logical value (HIGH) when the pin is disconnected or high-impedance. 
* The noPullup() method disables the internal pullup resistor on a pin on the core processors. 
* By default the internal pullup is disabled.
*/
void noPullup(int inpin);

/*!
* @brief The pinMode() method sets the specified digital I/O pin as INPUT or OUTPUT. 
* A digital or binary I/O pin can have two possible values: HIGH or LOW. Is it possible 
* to set or read the value of a digital I/O pin by using the digitalWrite() and digitalRead() 
* methods.
*/
void pinMode(int pin, int is_output);

/*!
* @brief The digitalWrite() method sets the value of a digital output pin. 
* Possible values are HIGH or LOW
*/
void digitalWrite(int outpin, int is_high);

/*!
* @brief The digitalRead() method reads the value of a digital input pin
*/
int digitalRead(int pin);

/*!
* @brief The portMode() method sets a specified digital I/O port as INPUT or OUTPUT. 
* A digital I/O port is a group of 8 pins. By writing 0 to a port it will set individually 
* each of the 8 pins to 0 (LOW). Possible values range from 0 to 255. It possible to read 
* or write a value of a digital I/O port by using the portRead() and portWrite() methods.
*/
void portMode(int port,int is_output);

/*!
* @brief The portRead() method reads the value of the digital input port specified.
*/
int portRead(int port);

/*!
* @brief The portWrite() method writes a value to the digital output port specified.
*/
void portWrite(int port, int byte);

typedef void INT_FUNC();

/*!
* @brief The interruptMode method sets the mode in which an external interrupt is generated. 
* External interrupts can be triggered at different stages in the value of a pin, 
* LOW when a pin is low, CHANGE when the pin changes, RISING when the pin goes from low to high or 
* FALLING when the pin goes from high to low.
*/
int interruptMode(uint8_t interrupt,int mode);

/*!
* @brief It is possible to generate and attend external interrupts on the Wiring hardware. 
* In addition to being regular digital pins, note that some of these pins are also used for 
* libraries like Wire or Serial/Serial1. The attachInterrupt() method sets the function that 
* executes whenver an external interrupt is generated. It also sets the mode in which external 
* interrupts can be triggered depending on the state of the interruption pin, LOW when a pin is low, 
* CHANGE when the pin changes state, RISING when the pin goes from low to high or FALLING when the pin 
* goes from high to low. The Interruption mode can also be set at a later time by using the 
* interruptMode() method. WARNING: you should avoid doing long procedures in interrupt routines, 
* also see the call to interrupts() in the example above enabling interrupts to allow the use of Serial 
* in the interrupt routine.
* @enum [HIGH,LOW, CHANGE, RISING, FALLING]
*/
void attachInterrupt(uint8_t interrupt, INT_FUNC function, int mode);

/*!
* @brief It is possible to generate and attend external interrupts on the Wiring hardware. 
* In addition to being regular digital pins, note that some of these pins are also used for libraries 
* like Wire or Serial/Serial1. The attachInterrupt() method sets the function that executes whenever 
* an external interrupt is generated, and the detachInterrupt() method clears the function used to 
* attend a specific interrupt. WARNING: you should avoid doing long procedures in interrupt routines, 
* also see the call to interrupts() in the example above enabling interrupts to allow the use of Serial 
* in the interrupt routine.
*/
void detachInterrupt(uint8_t interrupt);

/*!
* @brief The noInterrupts() and interrupts() methods disable and enable interrupts, respectively, 
* in the Wiring hardware. By default interruptions on the Wiring board are enabled to allow the environment, 
* libraries and time to work. Note that all the Wiring functionality will stop by disabling interrupts. 
* These methods are useful to mark critical sections of code where timing is so important that it can
* not be interrupted by other tasks (like Serial, Wire, other libraries or timing activities). 
* The methods are provided for advanced users who know exactly what they are doing. 
* After disabling interrupts it is necessary to re-enable them or all other I/O activities in the 
* Wiring board will not work again in the current program.
*/
void interrupts();

/*!
* @brief The noInterrupts() and interrupts() methods disable and enable interrupts, respectively, 
* in the Wiring hardware. By default interruptions on the Wiring board are enabled to allow the environment, 
* libraries and time to work. Note that all the Wiring functionality will stop by disabling interrupts. 
* These methods are useful to mark critical sections of code where timing is so important that it can
* not be interrupted by other tasks (like Serial, Wire, other libraries or timing activities). 
* The methods are provided for advanced users who know exactly what they are doing. 
* After disabling interrupts it is necessary to re-enable them or all other I/O activities in the 
* Wiring board will not work again in the current program.
*/
void noInterrupts();


#endif