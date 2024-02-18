/*
 * LCD_driver.c
 *
 * Created: 11/27/2023 6:02:49 PM
 *  Author: Ahmed Al-Sheikh
 */ 
#include "LCD_driver.h"
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void LCD_init(void)
{
	#if defined eight_bit
	_delay_ms(150);
	DIO_setportdir(LCD_dataport,1);
	DIO_setpindir(LCD_controlport,E,1);
	DIO_setpindir(LCD_controlport,RW,1);
	DIO_setpindir(LCD_controlport,RS,1);
	DIO_pinwrite(LCD_controlport,RW,0);
	LCD_sendcmd(0x38);  /*EIGHT BIT MODE */
	LCD_sendcmd(0x0E);  /*DISPLAY ON CURSOR ON*/
	LCD_sendcmd(0x01);  /*CLEAR SCREEN */
	LCD_sendcmd(0x06);  /*CURSOR MOVES TO RIGHT (ENGLISH WRITING) (INCRESE ADDRESS COUNTER)*/
	#elif defined four_bit
	_delay_ms(150);
	DIO_setpindir(LCD_dataport,0,1);/*adjust the pins that is connected to the data pins at lcd*/
	DIO_setpindir(LCD_dataport,1,1);
	DIO_setpindir(LCD_dataport,2,1);
	DIO_setpindir(LCD_dataport,3,1);
	DIO_setpindir(LCD_controlport,E,1);
	DIO_setpindir(LCD_controlport,RW,1);
	DIO_setpindir(LCD_controlport,RS,1);
	DIO_pinwrite(LCD_controlport,RW,0);
	LCD_sendcmd(0x02); /* FOUR BIT MODE */
	LCD_sendcmd(0x28);
	LCD_sendcmd(0x0c);
	LCD_sendcmd(0x01);  
	LCD_sendcmd(0x06); 
	
	#endif
}
/*Enable pulse static because this function needs to be called from this file only
delay at the end to sense the falling edge of the pulse */
void enable(void)
{
	DIO_pinwrite(LCD_controlport,E,1);
	_delay_ms(2);
	DIO_pinwrite(LCD_controlport,E,0);
	_delay_ms(2);
}
void LCD_sendcmd(char cmd)
{
	#if defined eight_bit
	DIO_portwrite(LCD_dataport,cmd);
	DIO_pinwrite(LCD_controlport,RS,0);
	enable();
	_delay_ms(1);
    /*needs 35micro second to execute*/
	#elif defined four_bit
	DIO_writelownipple(LCD_dataport,cmd>>4);  /*when iam connected to low nipple at port*/
	DIO_pinwrite(LCD_controlport,RS,0);
	enable();
	DIO_writelownipple(LCD_dataport,cmd);
	DIO_pinwrite(LCD_controlport,RS,0);
	enable();
	_delay_ms(1);
	#endif
}
void LCD_sendchar (char data)
{
	#if defined eight_bit
	DIO_portwrite(LCD_dataport,data);
	DIO_pinwrite(LCD_controlport,RS,1);
	enable();
	#elif defined four_bit
	DIO_writelownipple(LCD_dataport,data>>4);/*first 4 bits from left*/
	DIO_pinwrite(LCD_controlport,RS,1);
	enable();
	DIO_writelownipple(LCD_dataport,data); /*other 4 bits*/
	DIO_pinwrite(LCD_controlport,RS,1);
	enable();
	#endif
	_delay_ms(1);
}


void LCD_clearscr(void)
{
	LCD_sendcmd(0x01);
	_delay_ms(10);
}
/*pointer points at the address of the first letter in string*/
void LCD_sendstring(char *ptr)
{
	while(*ptr!='\0')
	{
		LCD_sendchar(*ptr);
		ptr++;
	}
}
void LCD_movecursor(char row,char col)
{
	char cmd=0x80;
	if(row>2||row<1||col<1||col>16)
	{
		cmd=0x80;/*iam speaking to address counter (*1*0000000)*/
	}
	else if(row==1)
	{
		cmd=0x80+col-1;
	}
	else if(row==2)
	{
		cmd=0xC0+col-1;
	}
	LCD_sendcmd(cmd);
}	