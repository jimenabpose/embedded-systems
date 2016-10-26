#ifndef LEDS_H_
#define LEDS_H_

#include <avr/io.h>

/* Leds definitions */
#define LEDS_PORT PORTB
#define LEDS_ADDR DDRB

#define OUTPUT 0XFF

#define LEDS_ON 0x00
#define LEDS_OFF 0xFF

void configureLeds();
void turnOn(int i);
void turnOff(int i);
void toggle(int i);
void ledsOff();
void ledsOn();


#endif
