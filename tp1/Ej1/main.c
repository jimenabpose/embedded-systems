#include <avr/io.h>
#include <util/delay.h>

#define LEDS_PORT PORTB
#define LEDS_ADDR DDRB

#define SWS_PIN PIND
#define SWS_ADDR DDRD

#define INPUT 0x00
#define OUTPUT 0Xff

#define LEDS_ON 0x00
#define LEDS_OFF 0xff

void led_on(int num) {
	LEDS_PORT =  num;
}

void leds_on() {
	LEDS_PORT =  LEDS_ON;
}

void leds_off() {
	LEDS_PORT = LEDS_OFF;
}

void ej1a() {
	LEDS_ADDR = OUTPUT;
	int i = 0xFE;
	leds_off();
	led_on(i);

	while(1) {

	}
}

void ej1b() {
	LEDS_ADDR = OUTPUT;
	int i = 0xFE;
	leds_off();

	while(1) {
		led_on(i);
		_delay_ms(1000);
		leds_off();
		_delay_ms(1000);
	}
}

void ej1c() {
	LEDS_ADDR = OUTPUT;
	int i = 0x0f;
	int k = 0xf0;

	while(1) {
		leds_off(i);
		led_on(i);
		_delay_ms(250);
		leds_off(i);
		led_on(k);
		_delay_ms(250);
	}
}

void ej2a() {
	LEDS_ADDR = OUTPUT;
	SWS_ADDR = INPUT;

	while(1) {
		LEDS_PORT = SWS_PIN;
		leds_off();
	}
}

void ej2b() {
	LEDS_ADDR = OUTPUT;
	SWS_ADDR = INPUT;

	int i = 0;
	LEDS_PORT = LEDS_OFF;
	while(1) {
		int sws = SWS_PIN;
		if(sws != 0xFF) {
			LEDS_PORT =  ~(LEDS_ON | (0x1 << i));
			i = (i + 1) % 8;
			_delay_ms(500);
		}
	}
}

void ej2c() {
	LEDS_ADDR = OUTPUT;
	SWS_ADDR = INPUT;
	static int status = 0xFF;
	LEDS_PORT = status;
	while(1) {
		int sws = SWS_PIN;
		if(sws != 0xFF) {
			status = status & sws;
			LEDS_PORT =  status;
			_delay_ms(500);
		}
		if(status == 0x00) {
			_delay_ms(500);
			status = 0xFF;
			LEDS_PORT = status;
		}
	}
}

void ej2d() {
	// Esto es para el b, el a no tiene estado...
	LEDS_ADDR = OUTPUT;
	SWS_ADDR = INPUT;
	LEDS_PORT = LEDS_OFF;
	int i = 1;
	while(1) {
		int sws = SWS_PIN;
		if(sws == 0xFE) {
			LEDS_PORT =  0xFF << i;
			i = (i + 1) % 9;
			_delay_ms(500);
		}
		if(sws == 0xFD) {
			i = 1;
			leds_off();
			_delay_ms(500);
		}
	}
}

int reset() {
	leds_off();
	return 0xFF;
}

int a() {
	int sws = SWS_PIN;
	//int i = 0;
	while(sws == 0xFF) {
		sws = SWS_PIN;
		int leds = LEDS_PORT;
		leds = leds >> 1;
		leds = leds | 0x80;
		if(LEDS_PORT == LEDS_OFF) {
			leds = 0x7F;
		}
		LEDS_PORT =  leds;
		//i = (i + 1) % 8;
		_delay_ms(200);
	}
	if(sws == 0xFE) {
		sws = reset();
	}
	return sws;
}

int b() {
	int sws = SWS_PIN;
	//int i = 0;
	while(sws == 0xFF) {
		sws = SWS_PIN;
		LEDS_PORT =  ~((~LEDS_PORT) << 1);
		if(LEDS_PORT == LEDS_OFF) {
			LEDS_PORT = 0xFE;
		}
		//i = (i + 1) % 8;
		_delay_ms(200);
	}
	if(sws == 0xFD) {
		sws = reset();
	}
	return sws;
}

int c() {
	int sws = SWS_PIN;
	int goingLeft = 1;
	leds_off();
	while(sws == 0xFF) {
		sws = SWS_PIN;
		if(goingLeft) {
			int leds = LEDS_PORT;
			leds = leds << 1;
			LEDS_PORT =  leds;
			_delay_ms(200);
			if(LEDS_PORT == 0) {
				goingLeft = 0;
			}
		} else {
			int leds = (LEDS_PORT << 1);
			leds = leds | 0x01;
			LEDS_PORT = leds;
			_delay_ms(200);
			if(LEDS_PORT == 0xFF) {
				goingLeft = 1;
			}
		}
	}
	if(sws == 0xFB) {
		sws = reset();
	}
	return sws;
}

int d() {
	int sws = SWS_PIN;
	int goingRight = 1;
	LEDS_PORT = 0xFF;
	while(sws == 0xFF) {
		sws = SWS_PIN;
		if(goingRight) {
			int leds = LEDS_PORT;
			leds = leds >> 1;
			LEDS_PORT =  leds;
			_delay_ms(200);
			if(LEDS_PORT == 0x00) {
				goingRight = 0;
			}
		} else {
			int leds = LEDS_PORT >> 1;
			leds = leds | 0x80;
			LEDS_PORT = leds;
			_delay_ms(200);
			if(LEDS_PORT == 0xFF) {
				goingRight = 1;
			}
		}
	}
	if(sws == 0xF7) {
		sws = reset();
	}
	return sws;
}

int e() {
	int sws = SWS_PIN;
	int i = 1;
	int goingRight = 1;
	while(sws == 0xFF) {
		sws = SWS_PIN;
		if(goingRight) {
			LEDS_PORT =  0xFF << i;
			_delay_ms(200);
			i = (i + 1) % 9;
			if(LEDS_PORT == 0) {
				goingRight = 0;
			}
		} else {
			int leds = LEDS_PORT >> 1;
			leds = leds | 0x80;
			LEDS_PORT = leds;
			_delay_ms(200);
			if(LEDS_PORT == 0xFF) {
				goingRight = 1;
			}
		}
	}
	if(sws == 0xEF) {
		sws = reset();
	}
	return sws;
}

int f() {
	int sws = SWS_PIN;
	int goingRight = 1;
	LEDS_PORT = 0xFF;
	while(sws == 0xFF) {
		sws = SWS_PIN;
		if(goingRight) {
			int leds = LEDS_PORT;
			leds = leds >> 1;
			LEDS_PORT =  leds;
			_delay_ms(200);
			if(LEDS_PORT == 0x00) {
				goingRight = 0;
			}
		} else {
			int leds = LEDS_PORT << 1;
			leds = leds | 0x01;
			LEDS_PORT = leds;
			_delay_ms(200);
			if(LEDS_PORT == 0xFF) {
				goingRight = 1;
			}
		}
	}
	if(sws == 0xDF) {
		sws = reset();
	}
	return sws;
}

int g() {
	int sws = SWS_PIN;
	int goingLeft = 1;
	int leds = LEDS_PORT;
	leds_off();
	LEDS_PORT = 0xFE;
	_delay_ms(200);
	while(sws == 0xFF) {
		sws = SWS_PIN;
		leds = LEDS_PORT;
		if(goingLeft) {
			leds = leds << 1;
			leds = leds | 0x01;
			LEDS_PORT = leds;
			if(LEDS_PORT == LEDS_OFF) {
				LEDS_PORT = 0x7F;
				goingLeft = 0;
			}
		} else {
			leds = leds >> 1;
			leds = leds | 0x80;
			LEDS_PORT = leds;
			if(LEDS_PORT == 0xFF){
				LEDS_PORT = 0xFE;
				goingLeft = 1;
			}
		}
		_delay_ms(200);
	}
	if(sws == 0xBF) {
		sws = reset();
	}
	return sws;
}

int h() {
	int sws = SWS_PIN;
	int left = 0x7F;
	int right = 0xFE;
	leds_off();
	LEDS_PORT = left & right;
	_delay_ms(200);
	while(sws == 0xFF) {
		sws = SWS_PIN;
		right = (right << 1);
		right = right | 0x01;
		left = (left >> 1);
		left = left | 0x80;
		LEDS_PORT = left & right;
		if(LEDS_PORT == LEDS_OFF) {
			left = 0x7F;
			right = 0xFE;
			LEDS_PORT = left & right;
		}
		_delay_ms(200);
	}

	if(sws == 0x7F) {
		sws = reset();
	}
	return sws;
}

int h2() {
	int sws = SWS_PIN;
	int i = 1;
	while(sws == 0xFF) {
		sws = SWS_PIN;
		i = 1;
		while(sws == 0xFF && i < 256) {
			sws = SWS_PIN;
			LEDS_PORT = ~i;
			i++;
			_delay_ms(200);
		}
	}

	if(sws == 0x7F) {
		sws = reset();
	}
	return sws;
}

void ej3() {
	LEDS_ADDR = OUTPUT;
	SWS_ADDR = INPUT;
	leds_off();
	int sws = SWS_PIN;
	while(1) {
		if(sws == 0xFE) {
			_delay_ms(200);
			sws = a();
		} else if(sws == 0xFD) {
			_delay_ms(200);
			sws = b();
		} else if(sws == 0xFB) {
			_delay_ms(200);
			sws = c();
		} else if(sws == 0xF7) {
			_delay_ms(200);
			sws = d();
		} else if(sws == 0xEF) {
			_delay_ms(200);
			sws = e();
		} else if(sws == 0xDF) {
			_delay_ms(200);
			sws = f();
		} else if(sws == 0xBF) {
			_delay_ms(200);
			sws = g();
		} else if(sws == 0x7F) {
			_delay_ms(200);
			sws = h();
		} else {
			sws = SWS_PIN;
		}
	}
}

int main() {
	ej3();
	return 0;
}
