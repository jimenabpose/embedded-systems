#include "ej3.h"

unsigned char buf[30];
int total;
int switches[8];
int showingLed;

void saveSwitches(int num) {
	EEPROM_write_int(num * 10, switches[num]);
	total++;
	EEPROM_write_int(80, total);
}

ISR(PCINT0_vect) {
	char swn = ~(SWS_PIN );

	switch (swn) {
	case (1 << 0):
		switches[0] = switches[0] + 1;
		saveSwitches(0);
		break;
	case (1 << 1):
		switches[1] = switches[1] + 1;
		saveSwitches(1);
		break;
	case (1 << 2):
		switches[2] = switches[2] + 1;
		saveSwitches(2);
		break;
	case (1 << 3):
		switches[3] = switches[3] + 1;
		saveSwitches(3);
		break;
	case (1 << 4):
		switches[4] = switches[4] + 1;
		saveSwitches(4);
		break;
	case (1 << 5):
		switches[5] = switches[5] + 1;
		saveSwitches(5);
		break;
	case (1 << 6):
		switches[6] = switches[6] + 1;
		saveSwitches(6);
		break;
	case (1 << 7):
		switches[7] = switches[7] + 1;
		saveSwitches(7);
		break;

	default:
		break;
	}
	showSwitch(showingLed);
}

void getTotal() {
	char aux[100];
	sprintf(aux, "The total is: %d\r\n", total);
	USART_SendString(aux);
}

void getSwitch(int i) {
	char aux[100];
	sprintf(aux, "The sw%d is: %d\r\n", i, switches[i]);
	USART_SendString(aux);
}

void showSwitch(int i) {
	showingLed = i;
	if(i <= 7) {
		setLeds(~switches[showingLed]);
	} else {
		setLeds(~total);
	}
}

void checkSwitchesCommand(int end) {
	if (strncmp(buf, "get_total", 9) == 0) {
		getTotal();
	} else if (strncmp(buf, "get_sw", 6) == 0) {
		unsigned int x = strtol(&buf[7], &buf[end], 0);
		if (x >= 0 && x <= 7) {
			getSwitch(x);
		} else {
			USART_SendString("Bad command\r\n");
		}
	} else if (strncmp(buf, "show_sw", 7) == 0) {
		unsigned int x = strtol(&buf[8], &buf[end], 0);
		if (x >= 0 && x <= 8) {
			showSwitch(x);
			char aux[100];
			if(x == 8) {
				sprintf(aux, "Showing total \r\n");
			} else {
				sprintf(aux, "Showing sw%d \r\n", x);
			}
			USART_SendString(aux);
		} else {
			USART_SendString("Bad command\r\n");
		}
	} else {
		USART_SendString("Bad command\r\n");
	}
}

void switchesCounter() {
	unsigned char rec = '\0';
	int i = 0;
	while (1) {
		while (rec != ';') {
			rec = USART_Receive();
			buf[i] = rec;
			i = (i + 1) % 30;
		}
		buf[i + 1] = '\0';
		checkSwitchesCommand(i);
		i = 0;
		rec = '\0';
	}
}

void generalConfig() {
	int i;
	for (i = 0; i < 8; i++) {
		switches[i] = 0;
	}
	total = 0;
	showingLed = 0;
}

void load() {
	int i;
	for (i = 0; i < 8; i++) {
		switches[i] = EEPROM_read_int(i * 10);
	}
	total = EEPROM_read_int(80);
}

void ej3() {
	configureLeds();
	configureSwitches();
	USART_Init(MYUBRR);
	generalConfig();
	load();

	switchesCounter();
}
