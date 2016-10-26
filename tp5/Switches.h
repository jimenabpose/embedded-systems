#ifndef SWITCHES_H_
#define SWITCHES_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define SWS_ADDR DDRA
#define SWS_PIN PINA
//#define SWS_PORT PORTA

#define INPUT 0x00

void configureSwitches();

#endif
