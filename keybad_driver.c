/*
 * keybad_driver.c
 *
 * Created: 11/29/2023 2:45:27 PM
 *  Author: Ahmed Al-Sheikh
 */ 


#include <avr/io.h>
#include "keybad_driver.h"
#include "DIO_driver.h"

void keybad_init(void)
{
	DIO_setpindir(keybadport,0,1); /*the 4 output pins are connected to rows*/
	DIO_setpindir(keybadport,1,1);
	DIO_setpindir(keybadport,2,1);
	DIO_setpindir(keybadport,3,1);
	DIO_setpindir(keybadport,4,0); /*those 4 connected to cols*/
	DIO_setpindir(keybadport,5,0); /*when you find problems if connected hardware delete the pull up function and connect external pull up on cols pins*/
	DIO_setpindir(keybadport,6,0);
	DIO_setpindir(keybadport,7,0);
	DIO_connectpullup(keybadport,4,1);
	DIO_connectpullup(keybadport,5,1);
	DIO_connectpullup(keybadport,6,1);
	DIO_connectpullup(keybadport,7,1);
}
unsigned char keybad_checkpress(void)
{
	unsigned char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};
	unsigned char row,col,x;
	unsigned char return_val=NOTPRESSED;
	for (row=0;row<4;row++)
	{
		DIO_pinwrite(keybadport,0,1);
		DIO_pinwrite(keybadport,1,1);
		DIO_pinwrite(keybadport,2,1);
		DIO_pinwrite(keybadport,3,1);
		DIO_pinwrite(keybadport,row,0);
		for (col=0;col<4;col++)
		{
			x=DIO_read(keybadport,(col+4)); /*starts to read the condition of button from pin 4
		                                    reads first row all cols then second row all cols and so on*/
			if (x==0)
			{
				return_val=arr[row][col];
				break; /*this exits from small for loop if button is pressed*/
			}
		}
		if (x==0)
		{
			break;  /* exit from big for loop if button is pressed*/
		}
	}
	return return_val;	
}