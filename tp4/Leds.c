#include "Leds.h"

void configureLeds() {
	LEDS_ADDR = OUTPUT;
	LEDS_PORT = LEDS_OFF;
}

void turnOn(int i) {
	int x = 0xFE;
	int k;
	for(k = 0; k < i; k++) {
		x = x << 1;
		x = x | 0x01;
	}
	LEDS_PORT = LEDS_PORT & x;
}

void turnOff(int i) {
	int x = 0x01;
	x = x << i;
	LEDS_PORT = LEDS_PORT | x;
}

void toggle(int i) {
	int x = 0x01;
	x = x << i;
	LEDS_PORT = LEDS_PORT ^ x;
}

void ledsOff() {
	LEDS_PORT = LEDS_OFF;
}

void ledsOn() {
	LEDS_PORT = LEDS_ON;
}

void setLeds(int leds) {
	LEDS_PORT = leds;
}
