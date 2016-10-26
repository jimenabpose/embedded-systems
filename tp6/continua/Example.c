#include <avr/io.h>
#include <avr/delay.h>


#define OUTPUT 0XFF

#define LED_ON 0x0
#define LED_OFF 0x1

#define LED_POS 0x40;

// PORTB2 es IN1
// PORTB3 es IN2
// PORTB4 es ENABLE A

int main() {
	DDRB = OUTPUT;
	//PORTB2 es IN1
	PORTB = PORTB | (1<<PORTB2);
	while(1) {

		// PORTB4 es ENABLE A
		PORTB = PORTB ^ (1<<PORTB4);

		// El led esta en PORTB7
		PORTB = PORTB ^ (1<<PORTB7);

		_delay_ms(500);
	}


//	PB2 -> input1
//	PB3 -> input2
//	PB4 -> enableA

// Conectar:
// PORTB5 a IN3
// PORTB6 a IN4
// PORTB8 a ENABLE B

// out 3 y 4 del puente H a otra bornera

// current sensing B a tierra???

}
