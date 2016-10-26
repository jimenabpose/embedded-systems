//#include "ej2.h"
//
//unsigned char buf[30];
//unsigned int runningSpeed;
//int ledSpeed;
//
//void saveSpeed() {
//	EEPROM_write_int(0,runningSpeed);
//	EEPROM_write_int(10,ledSpeed);
//}
//
//void changeSpeed(unsigned int newSpeed, int led) {
//	ledsOff();
//	ledSpeed = led;
//	turnOn(led);
//	runningSpeed = newSpeed;
//	USART_Init(runningSpeed);
//	saveSpeed(runningSpeed);
//}
//
//
//char * chartobin(int c)
//{
//    static char binarr[8];
//    int i;
//    for(i=7; i>=0; i--)
//    {
//        binarr[i]=(c%2) + '0';
//        c=c/2;
//    }
//    return binarr;
//}
//
//void ascii() {
//	while(1) {
//		char string[75];
//		unsigned char rec = USART_Receive();
//		sprintf(string,"\r\nASCII\t valor: %x\t simbolo: %c\t bits: %s\r\n",rec,rec,chartobin(rec));
//		USART_SendString(string);
//	}
//}
//
//ISR(PCINT0_vect) {
//	char swn = ~(SWS_PIN|0xF8);
//
//	switch (swn) {
//	// Speed1
//	case (1<<0) : changeSpeed(MYUBRR1,0); break;
//	// Speed2
//	case (1<<1) : changeSpeed(MYUBRR2,1); break;
//	// Speed3
//	case (1<<2) : changeSpeed(MYUBRR3,2); break;
//
//	default : break;
//	}
//
//}
//
//void load() {
//	runningSpeed = EEPROM_read_int(0);
//	ledSpeed = EEPROM_read_int(10);
//	changeSpeed(runningSpeed,ledSpeed);
//}
//
//void ej2() {
//	configureLeds();
//	configureSwitches();
//	load();
//	ascii();
//}
