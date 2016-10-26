#include <avr/io.h>

#define LEDS_PORT PORTB
#define LEDS_ADDR DDRB

#define INPUT 0x00
#define OUTPUT 0Xff

#define LEDS_ON 0x00
#define LEDS_OFF 0xff

void leds_off() {
	LEDS_PORT = LEDS_OFF;
}

void initLeds() {
	LEDS_ADDR = OUTPUT;
}
