#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>


void configureADC();
unsigned int startADC(unsigned char channel);

#endif
