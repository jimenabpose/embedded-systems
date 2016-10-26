#ifndef USART_H_
#define USART_H_

#include <avr/io.h>

/* USART definitions */
#define FOSC 1000000                       // Clock Speed
#define BAUD 2400							// Baud Rate
#define MYUBRR (FOSC/(16.0*BAUD) -1)

#define BAUD1 2400
#define BAUD2 4800
#define BAUD3 9600
#define MYUBRR1 (FOSC/(16.0*BAUD1) -1)
#define MYUBRR2 (FOSC/(16.0*BAUD2) -1)
#define MYUBRR3 (FOSC/(16.0*BAUD3) -1)

void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_SendString(char * str);

#endif
