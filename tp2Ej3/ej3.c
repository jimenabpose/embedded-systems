#include "ej3.h"

#define LEDS_PORT PORTB
#define LEDS_ADDR DDRB

#define SWS_PIN PIND
#define SWS_ADDR DDRD

#define INPUT 0x00
#define OUTPUT 0Xff

#define LEDS_ON 0x00
#define LEDS_OFF 0xff

void newSeg();
void swsPlus();
void swsMinus();

enum showing {
	SHOW_HOURS,
	SHOW_MINS,
	SHOW_SEGS,
} showingMode;

int hours, mins, segs;
int showHours, showMins, showSegs;
int running;

ISR(TIMER1_COMPA_vect) {
	if(running) {
		newSeg();
	}
	switch(showingMode) {
	case(SHOW_SEGS): LEDS_PORT = ~segs; break;
	case(SHOW_MINS): LEDS_PORT = ~mins; break;
	case(SHOW_HOURS): LEDS_PORT = ~hours; break;
	default: ;
	}
}

ISR(PCINT3_vect) {
	char swn = ~SWS_PIN;

	switch (swn) {
	// Show segs
	case (1<<0) : showingMode = SHOW_SEGS; running = 1; break;
	// Show mins
	case (1<<1) : showingMode = SHOW_MINS; running = 1; break;
	// Show hours
	case (1<<2) : showingMode = SHOW_HOURS; running = 1; break;
	// Config segs
	case (1<<3) : showingMode = SHOW_SEGS; running = 0; break;
	// Config mins
	case (1<<4) : showingMode = SHOW_MINS; running = 0; break;
	// Config hours
	case (1<<5) : showingMode = SHOW_HOURS; running = 0; break;
	// Config +
	case (1<<6) : swsPlus(); break;
	// Config -
	case (1<<7) : swsMinus(); break;

	default :;
	}
}

void newSeg() {
	segs ++;
	if(segs == 60) {
		segs = 0;
		mins ++;
		if(mins == 60) {
			mins = 0;
			hours ++;
			if(hours == 24) {
				hours = 0;
			}
		}
	}
}

void swsPlus() {
	if(!running) {
		switch(showingMode) {
		case(SHOW_SEGS): segs = (segs + 1) % 60; LEDS_PORT = ~segs; break;
		case(SHOW_MINS): mins = (mins + 1) % 60; LEDS_PORT = ~mins; break;
		case(SHOW_HOURS): hours = (hours + 1) % 24; LEDS_PORT = ~hours; break;
		default: ;
		}
	}
}

void swsMinus() {
	if(!running) {
		switch(showingMode) {
		case(SHOW_SEGS): segs = (segs - 1) % 60; LEDS_PORT = ~segs; break;
		case(SHOW_MINS): mins = (mins - 1) % 60; LEDS_PORT = ~mins; break;
		case(SHOW_HOURS): hours = (hours - 1) % 24; LEDS_PORT = ~hours; break;
		default: ;
		}
	}
}

void configureTimer11() {
	/*
		 * TCNT es el valor del timer (lo que se va incrementando)
		 * OCR es contra lo que se compara
		 */

		// Hago que haga el clear cuando machea con A
		TCCR1A = (1<<COM1A1);

		// Seteo el prescaler de 64
		TCCR1B = (1<<CS10) | (1<<CS11) | (1<<WGM12);

		// Fuerzo a que se compare con A
	//	TCCR1C = (1<<FOC1A);


		// Seteo el output compare en 15625 = 0x3D09
		OCR1AH = 0x3D;
		OCR1AL = 0x09;

		// Habilito el RTC1 y habilito que se compare con el OCR1AH
		TIMSK1 = (1<<OCIE1A);
}

void configureSwitches() {
	/* Usar de la 24 a la 3 */
	/* INT0 es PD2 */
//	EIMSK = (1<<INT0);

	PCICR = (1<<PCIE3);
	PCMSK3 = 0xFF;
}

void configureInterruptions() {
	configureTimer11();
	configureSwitches();

	// Habilito las interrupciones
	sei();
}

void generalConfig() {
	running = 1;
	showingMode = SHOW_SEGS;
}

int ej3() {
	LEDS_ADDR = OUTPUT;
	LEDS_PORT = LEDS_OFF;

	configureInterruptions();
	generalConfig();
	while(1);

	/*
	 * clock: 1000000 Hz
	 * prescaler: 64
	 * 1000000/64 = 15625; -> tengo que contar hasta 15625
	 */
}
