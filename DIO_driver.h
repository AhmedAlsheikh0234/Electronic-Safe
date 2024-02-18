/*
 * DIO_Declerations.h
 *
 * Created: 10/5/2023 2:44:21 AM
 *  Author: Ahmed Al-Sheikh
 */ 


#ifndef DIO_DECLERATIONS_H_
#define DIO_DECLERATIONS_H_
void DIO_setpindir(unsigned char PORT,unsigned char PIN,unsigned char dir);

void DIO_pinwrite(unsigned char PORT,unsigned char pin,unsigned char val);

void DIO_togglepin(unsigned char PORT,unsigned char PIN);

unsigned char DIO_read(unsigned char PORT,unsigned char PIN);

void DIO_setportdir(unsigned char PORT,unsigned char dir);

void DIO_portwrite(unsigned char PORT,unsigned char val);

unsigned char DIO_readport(unsigned char PORT);

void DIO_toggleport(unsigned char PORT);

void DIO_writelownipple(unsigned char port,unsigned char val);

void DIO_writehighnipple(unsigned char port,unsigned char val);

void DIO_connectpullup(unsigned char port,unsigned char pin,unsigned char connect);
#endif /* DIO_DECLERATIONS_H_ */