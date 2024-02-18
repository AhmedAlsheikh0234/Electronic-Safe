/*
 * SAFE.c
 *
 * Created: 12/4/2023 1:53:26 AM
 *  Author: Ahmed Al-Sheikh
 */ 


#include <avr/io.h>
#include "keybad_driver.h"
#include "LCD_driver.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#define maxtries 2
#define status_loc 0x30
#define pass_loc1 0x31
#define pass_loc2 0x32
#define pass_loc3 0x33
#define pass_loc4 0x34
unsigned char arr[4];     /*password stored in an array*/
int main(void)
{
	keybad_init();
	LCD_init();
	unsigned char val=NOTPRESSED,flag=0,i,tries=maxtries;
	if (EEPROM_read(status_loc)==NOTPRESSED)    /*check if there is already a stored password (not stored location in EEPROM is 0xff*/
	{
		LCD_sendstring("set pass:");
		for (i=0;i<=3;i++)              /*entry of new password loop (4 digit password)*/
		{
			do 
			{
				val=keybad_checkpress();
			} while (val==NOTPRESSED);
			LCD_sendchar(val);
			_delay_ms(500);
			LCD_movecursor(1,10+i);
			LCD_sendchar('*');
			EEPROM_write(pass_loc1+i,val);
		}
		EEPROM_write(status_loc,0x00);           /*status to indicate that password is set*/
	}
    while(flag==0)
    {
       LCD_clearscr();
	   LCD_sendstring("Check Pass:");
	   for (i=0;i<=3;i++)                  /*pass word entry loop*/
	   {
		   do
		   {
			   arr[i]=keybad_checkpress();
		   } while (arr[i]==NOTPRESSED);
		   LCD_sendchar(arr[i]);
		   _delay_ms(500);
		   LCD_movecursor(1,12+i);
		   LCD_sendchar('*');
	   }
	   if (EEPROM_read(pass_loc1)==arr[0] && EEPROM_read(pass_loc2)==arr[1] && EEPROM_read(pass_loc3)==arr[2] && EEPROM_read(pass_loc4)==arr[3])   /*check password if right or wrong*/
	   {
		   LCD_clearscr();
		   LCD_sendstring("Welcome");
		   LCD_movecursor(2,1);
		   LCD_sendstring("Right Password");
		   flag=1;                              /*exit from big loop and finish program*/
	   }
	   else
	   {
		   tries=tries-1;                /*if password is wrong*/
		   if (tries>0)          /*tries before zero*/
		   {
			   LCD_clearscr();
			   LCD_sendstring("Try again");
			   _delay_ms(1000);
			   LCD_clearscr();
			   LCD_sendstring("tries left:");
			   LCD_sendchar(tries+48);
			   _delay_ms(1000);               
		   }
		   else                      /*zero tries left*/
		   {
			   LCD_clearscr();
			   LCD_sendstring("wrong password");
			   LCD_movecursor(2,1);
			   LCD_sendstring("safe closed");
			   flag=1;
		   }
	   }
		   
    }
}