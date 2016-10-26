#include "ej2.h"

double getVin(unsigned int value) {
	return value*5/1024.0;
}


double convertToG(unsigned int value) {
	return (getVin(value)-1.88)/0.330;
}

void ej2() {
	USART_Init(MYUBRR);
	configureADC();

	char aux[100];

	USART_SendString("Initialization\r\n");

	while(1) {

		unsigned int result = startADC(0);
		double vin = getVin(result);
		double gvalue = convertToG(result);
		sprintf(aux,"Value: %d \t Vin: %f \t gValue: %g \r\n",result, vin, gvalue);
		USART_SendString(aux);
		_delay_ms(500);

	}
}
