#include "PWM.h"

void configurePWM() {
	//Para que use PWM
	TCCR0 |= (1<<WGM01) | (1<<WGM00);


}
