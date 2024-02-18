/*
 * LCD_driver.h
 *
 * Created: 11/27/2023 6:02:09 PM
 *  Author: Ahmed Al-Sheikh
 */ 


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_
#include "DIO_driver.h"
#include <avr/io.h>
/*#define eight_bit*/
#define four_bit
#define LCD_dataport 'A'
#define LCD_controlport 'A'
#define RS 6
#define E 5
#define RW 7
void LCD_init();
void enable();
void LCD_sendcmd(char cmd);
void LCD_sendchar (char data);
void LCD_clearscr();
void LCD_sendstring(char *ptr);
void LCD_movecursor(char row,char col);

#endif /* LCD_DRIVER_H_ */