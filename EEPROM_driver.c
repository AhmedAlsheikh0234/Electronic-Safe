/*
 * EEPROM_driver.c
 *
 * Created: 12/3/2023 3:42:02 PM
 *  Author: Ahmed Al-Sheikh
 */ 


#include <avr/io.h>
#include "macros.h"

void EEPROM_write(unsigned short address,unsigned char data)
{
	EEARL=(char)address;      /*address register 16 bit*/
	EEARH=(char)(address>>8);
	EEDR=data;                /*data register*/
	set_bit(EECR,EEMWE);    /*master write 1*/
	set_bit(EECR,EEWE);     /*write 1*/
	while (read_bit(EECR,EEWE)==1);    /*wait till write is 0*/
}
unsigned char EEPROM_read(unsigned short address)
{
	EEARL=(char)address;      
	EEARH=(char)(address>>8);
	set_bit(EECR,EERE);    /*read 1*/
	return EEDR;          /*return data from the required address*/
}
