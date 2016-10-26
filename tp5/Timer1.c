#include "Timer1.h"

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

		sei();
}
