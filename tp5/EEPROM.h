#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);

void EEPROM_write_string(unsigned int uiAddress, unsigned char * ucData, int size);
void EEPROM_read_string(unsigned int uiAddress, unsigned char * ucData, int size);

void EEPROM_write_int(unsigned int uiAddress, int data);
int EEPROM_read_int(unsigned int uiAddress);


#endif
