#include "Switches.h"

void configureSwitches() {
	SWS_ADDR = INPUT;

//	SWS_PORT = (1<<0)|(1<<1)|(1<<2);

//	SREG
	/* Habilito PCINT 0 1 y 2 */
	PCICR = (1<<PCIE0);
	PCMSK0 = 0x07;

	sei();
}
