#ifndef USART_H_
#define USART_H_

#include <avr/io.h>

/* USART definitions */
#define FOSC 1000000                       // Clock Speed
#define BAUD 2400							// Baud Rate
#define MYUBRR (FOSC/(16.0*BAUD) -1)

void USART_Init( unsigned int baud );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_SendString(char * str);

#endif
