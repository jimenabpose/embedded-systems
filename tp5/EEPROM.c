#include "EEPROM.h"

/* Se deben controlar las interrupciones para que todas estas funciones sean atomicas */

void EEPROM_write(unsigned int uiAddress, unsigned char ucData) {
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));

	/* Set up address and Data Registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
}

unsigned char EEPROM_read(unsigned int uiAddress) {
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));

	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}

void EEPROM_write_string(unsigned int uiAddress, unsigned char * ucData, int size) {
	int i;
	for(i = 0; i < size; i++) {
		EEPROM_write(uiAddress+i, ucData[i]);
	}
}

void EEPROM_read_string(unsigned int uiAddress, unsigned char * ucData, int size) {
	int i;
	unsigned int auxAddress = uiAddress;
	for(i = 0; i < size; i++) {
		ucData[i] = EEPROM_read(auxAddress);
		auxAddress ++;
	}
}

void EEPROM_write_int(unsigned int uiAddress, int data) {
	char dataString[4];
	int i;
	itoa(data, dataString, 10);
	for(i = 0; i < 4; i++) {
		EEPROM_write(uiAddress+i,dataString[i]);
	}
}

int EEPROM_read_int(unsigned int uiAddress) {
	char dataString[4];
	int i;
	for(i = 0; i < 4; i++) {
		dataString[i] = EEPROM_read(uiAddress+i);
	}
	return atoi(dataString);
}
