#ifndef EJ1_H_
#define EJ1_H_

#include <stdlib.h>
#include <string.h>
#include "../Timer1.h"
#include "../Leds.h"
#include "../Switches.h"
#include "../EEPROM.h"
#include "../USART.h"

#define SEGS_ADDR 0
#define MINS_ADDR 50
#define HOURS_ADDR 100

enum showing {
	SHOW_HOURS,
	SHOW_MINS,
	SHOW_SEGS,
} showingMode;

void ej1();

void newSeg();
void swsPlus();
void swsMinus();

#endif
