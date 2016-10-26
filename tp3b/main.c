#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include "USART.h"
#include "Timer1.h"

/* Leds definitions */
#define LEDS_PORT PORTB
#define LEDS_ADDR DDRB

#define INPUT 0x00
#define OUTPUT 0XFF

#define LEDS_ON 0x00
#define LEDS_OFF 0xFF

unsigned char buf[30];

void echo() {
	USART_Init(MYUBRR);
	while(1) {
		unsigned char rec = USART_Receive();
		USART_Transmit(rec);
	}
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

void checkCommand() {
	if(strncmp(buf, "turn_on", 7) == 0) {
		int x = buf[8] - '0';
//		char str[100];
//		sprintf(str,"\n\nRecibi: %c\t atoi: %d\t strtol: %d\n", buf[8], x, z);
//		USART_SendString(str);
		turnOn(x);
	} else if(strncmp(buf, "turn_off", 8) == 0) {
		int x = buf[9] - '0';
		turnOff(x);
	} else if(strncmp(buf, "toggle", 6) == 0) {
		int x = buf[7] - '0';
		toggle(x);
	} else {
		USART_SendString("Bad command\r\n");
	}
}

void initLigths() {
	USART_Init(MYUBRR);
	LEDS_ADDR = OUTPUT;
	LEDS_PORT = LEDS_OFF;
}

void lights() {
	initLigths();
	unsigned char rec = '\0';
	int i = 0;
	while(1) {
		while(rec != ';') {
			rec = USART_Receive();
			buf[i] = rec;
			i = (i + 1) % 30;
		}
		buf[i+1] = '\0';
		i = 0;
		checkCommand();
		rec = '\0';
	}
}


void getDate() {
	char aux[100];
	sprintf(aux,"The date is: %d\r\n",segs);
	USART_SendString(aux);
}

void setDate(unsigned int x) {
	segs = x;
	char aux[100];
	sprintf(aux,"Date setted to: %d\r\n",x);
	USART_SendString(aux);
}

void reset() {
	segs = 0;
	USART_SendString("Reseted\r\n");
}

void checkCommandDateTime(int end) {
	int k, acum = 0;
	if(strncmp(buf, "get_date", 8) == 0) {
		getDate();
	} else if(strncmp(buf, "set_date", 8) == 0) {
		unsigned int x = strtol(&buf[9],&buf[end],0);
		if(x != 0) {
			setDate(x);
		} else {
			USART_SendString("Bad command\r\n");
		}
	} else if(strncmp(buf, "reset", 5) == 0) {
		reset();
	} else {
		USART_SendString("Bad command\r\n");
	}
}

void initDateTime() {
	USART_Init(MYUBRR);
	configureTimer1();
}

void dateTime() {
	initDateTime();
	unsigned char rec = '\0';
	int i = 0;
	while(1) {
		while(rec != ';') {
			rec = USART_Receive();
			buf[i] = rec;
			i = (i + 1) % 30;
		}
		buf[i+1] = '\0';
		checkCommandDateTime(i);
		i = 0;
		rec = '\0';
	}
}

int main() {
	dateTime();
	return 0;
}


// This code waits for a character and transmits the character back (with interrupts)


//#include <avr/io.h>
//#include <stdint.h>                     // needed for uint8_t
//
//#include <avr/interrupt.h>
//
//
//
//#define FOSC 1000000                       // Clock Speed
//#define BAUD 2400							// Baud Rate
//#define MYUBRR (FOSC/(16*BAUD) -1)
//
//#define LEDS_PORT PORTB
//#define LEDS_ADDR DDRB
//#define LEDS_ON 0x00
//
//
//volatile char ReceivedChar;
//
//
//int main( void )
//{
//	LEDS_ADDR = 0xff;
//	LEDS_PORT = ~LEDS_ON;
//
//    /*Set baud rate */
//    UBRR0H = (unsigned char) (MYUBRR >> 8);
//    UBRR0L = (unsigned char) MYUBRR;
//
//    UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
//    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp
//
//    sei();
//
//    while(1) {
//    	while ( !( UCSR0A & (1<<UDRE0)) )
//    	;
//    	UDR0 = 'a';
//
//
//    	LEDS_PORT =  LEDS_ON;
//    		/* Wait for data to be received */
//    		while ( !(UCSR0A & (1<<RXC0)) )
//    		;
//    		/* Get and return received data from buffer */
//    		return UDR0;
//    }
//}
//
//ISR (USART_RX_vect)
//{
//	LEDS_PORT = LEDS_ON;
//    ReceivedChar = UDR0;                       // Read data from the RX buffer
//    UDR0 = ReceivedChar;                       // Write the data to the TX buffer
//}
