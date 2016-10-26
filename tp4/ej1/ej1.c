//#include "ej1.h"
//
//int hours, mins, segs;
//int showHours, showMins, showSegs;
//int running;
//
//void save(int addr, int num) {
////	char string[8];
////	itoa(num, string, 10);
////	EEPROM_write_string(addr,string);
//
//	EEPROM_write_int(addr, num);
//}
//
//ISR(TIMER1_COMPA_vect) {
//	if (running) {
//		newSeg();
//	}
//	switch (showingMode) {
//	case (SHOW_SEGS):
//		setLeds(~segs);
//		break;
//	case (SHOW_MINS):
//		setLeds(~mins);
//		break;
//	case (SHOW_HOURS):
//		setLeds(~hours);
//		break;
//	default:
//		break;
//	}
//}
//
//ISR(PCINT0_vect) {
//	char swn = ~SWS_PIN;
//
//	switch (swn) {
//	// Show segs
//	case (1 << 0):
//		showingMode = SHOW_SEGS;
//		running = 1;
//		save(SEGS_ADDR, segs);
//		break;
//		// Show mins
//	case (1 << 1):
//		showingMode = SHOW_MINS;
//		running = 1;
//		save(MINS_ADDR, mins);
//		break;
//		// Show hours
//	case (1 << 2):
//		showingMode = SHOW_HOURS;
//		running = 1;
//		save(HOURS_ADDR, hours);
//		break;
//		// Config segs
//	case (1 << 3):
//		showingMode = SHOW_SEGS;
//		running = 0;
//		break;
//		// Config mins
//	case (1 << 4):
//		showingMode = SHOW_MINS;
//		running = 0;
//		break;
//		// Config hours
//	case (1 << 5):
//		showingMode = SHOW_HOURS;
//		running = 0;
//		break;
//		// Config +
//	case (1 << 6):
//		swsPlus();
//		break;
//		// Config -
//	case (1 << 7):
//		swsMinus();
//		break;
//
//	default:
//		break;
//	}
//}
//
//void newSeg() {
//	segs++;
//	save(SEGS_ADDR, segs);
//	if (segs == 60) {
//		segs = 0;
//		mins++;
//		save(MINS_ADDR, mins);
//		if (mins == 60) {
//			mins = 0;
//			hours++;
//			if (hours == 24) {
//				hours = 0;
//			}
//			save(HOURS_ADDR, hours);
//		}
//	}
//}
//
//void swsPlus() {
//	if (!running) {
//		switch (showingMode) {
//		case (SHOW_SEGS):
//			segs = (segs + 1) % 60;
//			setLeds(~segs);
//			break;
//		case (SHOW_MINS):
//			mins = (mins + 1) % 60;
//			setLeds(~mins);
//			break;
//		case (SHOW_HOURS):
//			hours = (hours + 1) % 24;
//			setLeds(~hours);
//			break;
//		default:
//			break;
//		}
//	}
//}
//
//void swsMinus() {
//	if (!running) {
//		switch (showingMode) {
//		case (SHOW_SEGS):
//			segs = (segs - 1) % 60;
//			setLeds(~segs);
//			break;
//		case (SHOW_MINS):
//			mins = (mins - 1) % 60;
//			setLeds(~mins);
//			break;
//		case (SHOW_HOURS):
//			hours = (hours - 1) % 24;
//			setLeds(~hours);
//			break;
//		default:
//			break;
//		}
//	}
//}
//
//void generalConfig() {
//	segs = 0; mins = 0; hours = 0;
//	running = 1;
//	showingMode = SHOW_SEGS;
//}
//
//void loadStatus() {
////	char string[8];
////	EEPROM_read_string(SEGS_ADDR,string,8);
////	segs = atoi(string);
////	EEPROM_read_string(MINS_ADDR,string,8);
////	mins = atoi(string);
////	EEPROM_read_string(HOURS_ADDR,string,8);
////	hours = atoi(string);
//
//	segs = EEPROM_read_int(SEGS_ADDR);
//	mins = EEPROM_read_int(MINS_ADDR);
//	hours = EEPROM_read_int(HOURS_ADDR);
//}
//
//void ej1() {
//	configureLeds();
//	configureSwitches();
//	configureTimer1();
//	generalConfig();
//	loadStatus();
//
//	while (1)
//		;
//
//	/*
//	 * clock: 1000000 Hz
//	 * prescaler: 64
//	 * 1000000/64 = 15625; -> tengo que contar hasta 15625
//	 */
//}
