/*
 * EEPROM_driver.h
 *
 * Created: 12/4/2023 12:54:49 AM
 *  Author: Ahmed Al-Sheikh
 */ 


#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_
void EEPROM_write(unsigned short address,unsigned char data);
unsigned char EEPROM_read(unsigned short address);




#endif /* EEPROM_DRIVER_H_ */
