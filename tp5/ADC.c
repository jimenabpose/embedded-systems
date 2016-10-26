#include "ADC.h"

// Function to initialise the ADC feature
void configureADC() {

	ADCSRA = 0X00; // Clear previous ADC results and status flags

	ADMUX = 0X00; // 0x40 for 10 bits

//	ADCSRA = 0X87; // 10000111 We have set the ADSC bit to start a conversion, and the
//	ADCSRA = (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);

	// ADPS bits are set so that the prescaler is 128

//	ACSRA = 0X80; // ADEN is set, to enable the ADC
	ADCSRA |= (1<<ADEN);


}

// Function to perform an ADC conversion, Takes 0-8 as input
// to select which input to convert
unsigned int startADC(unsigned char channel) {

//	unsigned char i;

	ADCH = 0x00; // Clear the previous result

//	i = channel & 0x07; // Decide which line to perform ADC conversion on

	ADMUX = channel; // Enter which line to perform in the ADC control register

	ADCSRA |= 1 << ADSC;

	while (ADCSRA & (1 << ADSC));  // wait for conv. to complete

//	unsigned char temp = ADCH; //unsigned int temp=ADC;   for 10 bits
	unsigned int temp = ADC;

	return temp;

}

/* ---------------- Sample ADC Call -----------------------*/

//unsigned char result=adc_start(0); // This performs ADC conversion on Pin A0 and stores the result
// to variable "result"
