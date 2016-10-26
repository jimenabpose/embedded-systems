#include "USART.h"

void USART_Init( unsigned int baud ) {
	/* Set baud rate */
	UBRR0H = (unsigned char) (baud>>8);
	UBRR0L = (unsigned char) baud;

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp
}

void USART_Transmit( unsigned char data ) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}


unsigned char USART_Receive( void ) {
//	char str[100];
//	sprintf(str,"\nbaud: %d\t UBRR0H: %d\t UBRR0L: %d\t MYUBRR; %d\r\n", myBaud, myUBRR0H, myUBRR0L, MYUBRR);
//	USART_SendString(str);
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );

	/* Get and return received data from buffer */
	return UDR0;
}

void USART_SendString(char * str) {
	int i;
	for(i = 0; str[i] != '\0'; i++) {
		USART_Transmit(str[i]);
	}
}
