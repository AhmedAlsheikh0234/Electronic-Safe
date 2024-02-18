/*
 * DIO_driver.c
 *
 * Created: 10/5/2023 2:40:29 AM
 *  Author: Ahmed Al-Sheikh
 */ 
/*
PORT = DDR     PIN=pin number     dir=i/o?      val=1 or 0
*/
#include <avr/io.h>
#include "macros.h"
/*
set direction function ( Input or Output )
*/
void DIO_setpindir(unsigned char PORT,unsigned char PIN,unsigned char dir)
{
	switch(PORT)
	{
		case'a':
		case'A':
		if(dir==1)
		{
			set_bit(DDRA,PIN);
		}
		else
		{
			clr_bit(DDRA,PIN);
		}
		break;
		case'b':
		case'B':
		if(dir==1)
		{
			set_bit(DDRB,PIN);
		}
		else
		{
			clr_bit(DDRB,PIN);
		}
		break;
		case'c':
		case'C':
		if(dir==1)
		{
			set_bit(DDRC,PIN);
		}
		else
		{
			clr_bit(DDRC,PIN);
		}
		break;
		case'D':
		case'd':
		if(dir==1)
		{
			set_bit(DDRD,PIN);
		}
		else
		{
			clr_bit(DDRD,PIN);
		}
		break;
		default:
		break;
	}
}

/*
when port is output then set or clear
*/
void DIO_pinwrite(unsigned char PORT,unsigned char PIN,unsigned char val)
{
	switch(PORT)
	{
		case'A':
		case'a':
		if(val==1)
		{
			set_bit(PORTA,PIN);
		}
		else
		{
			clr_bit(PORTA,PIN);
		}
		break;
		case'b':
		case'B':
		if(val==1)
		{
			set_bit(PORTB,PIN);
		}
		else
		{
			clr_bit(PORTB,PIN);
		}
		break;
		case'c':
		case'C':
		if(val==1)
		{
			set_bit(PORTC,PIN);
		}
		else
		{
			clr_bit(PORTC,PIN);
		}
		break;
		case'D':
		case'd':
		if(val==1)
		{
			set_bit(PORTD,PIN);
		}
		else
		{
			clr_bit(PORTD,PIN);
		}
		break;
		default:
		break;
	}
}

/*
when port is output toggle
*/
void DIO_togglepin(unsigned char PORT,unsigned char PIN)
{
	switch(PORT)
	{
		case'A':
		case'a':
		toggle_bit(PORTA,PIN);
		break;
		case'b':
		case'B':
		toggle_bit(PORTB,PIN);
		break;
		case'c':
		case'C':
		toggle_bit(PORTC,PIN);
		break;
		case'D':
		case'd':
		toggle_bit(PORTD,PIN);
		break;
		default:
		break;
	}
}  

/*
when port is input
*/
char DIO_read(unsigned char PORT,unsigned char PIN)
{
	unsigned char return_val=0;
	switch(PORT)
	{
		case'A':
		case'a':
		return_val=read_bit(PINA,PIN);
		break;
		case'B':
		case'b':
		return_val=read_bit(PINB,PIN);
		break;
		case'C':
		case'c':
		return_val=read_bit(PINC,PIN);
		break;
		case'D':
		case'd':
		return_val=read_bit(PIND,PIN);
		break;
		default:
		break;
	}
	return return_val;
}

/*
set whole PORT direction (input or output)
*/
void DIO_setportdir(unsigned char PORT,unsigned char dir)
{
	switch(PORT)
	{
		case'A':
		case'a':
		DDRA=dir;
		break;
		case'B':
		case'b':
		DDRB=dir;
		break;
		case'C':
		case'c':
		DDRC=dir;
		break;
		case'D':
		case'd':
		DDRD=dir;
		break;
		default:
		break;
	}
}

/*
when whole port is output write value (0 or 1) in whole port
*/
void DIO_portwrite(unsigned char PORT,unsigned char val)
{
	switch(PORT)
	{
		case'A':
		case'a':
		PORTA=val;
		break;
		case'B':
		case'b':
		PORTB=val;
		break;
		case'C':
		case'c':
		PORTC=val;
		break;
		case'D':
		case'd':
		PORTD=val;
		break;
		default:
		break;
	}
}

/*
when whole port is input
*/
unsigned char DIO_readport(unsigned char PORT)
{
	unsigned char return_val=0;
	switch(PORT)
	{
		case'a':
		case'A':
		return_val=PINA;
		break;
		case'b':
		case'B':
		return_val=PINB;
		break;
		case'c':
		case'C':
		return_val=PINC;
		break;
		case'd':
		case'D':
		return_val=PIND;
		break;
		default:
		break;
	}
	return return_val;
}

/*
toggle whole port when output
*/
void DIO_toggleport(unsigned char PORT)
{
	switch(PORT)
	{
		case'A':
		case'a':
		PORTA^=0xff;
		break;
		case'B':
		case'b':
		PORTB^=0xff;
		break;
		case'C':
		case'c':
		PORTC^=0xff;
		break;
		case'D':
		case'd':
		PORTD^=0xff;
		break;
		default:
		break;
	}
	
}
/*
when you need 4 pins of port (port is output)
takes first 4 bits from value and writes them on the 4 pins of port
*/
void DIO_writelownipple(unsigned char port,unsigned char val)
{
	val=val & 0x0f;
	switch(port)
	{
		case'A':
		case'a':
		PORTA=PORTA&0xf0;
		PORTA|=val;
		case'B':
		case'b':
		PORTB=PORTB&0xf0;
		PORTB|=val;
		case'C':
		case'c':
		PORTC=PORTC&0xf0;
		PORTC|=val;
		case'D':
		case'd':
		PORTD=PORTD&0xf0;
		PORTD|=val;
	}
}
void DIO_writehighnipple(unsigned char port,unsigned char val)
{
	val<<=4;
	switch(port)
	{
		case'A':
		case'a':
		PORTA&=0x0f;
		PORTA|=val;
		case'B':
		case'b':
		PORTB&=0x0f;
		PORTB|=val;
		case'C':
		case'c':
		PORTC&=0x0f;
		PORTC|=val;
		case'D':
		case'd':
		PORTD&=0x0f;
		PORTD|=val;
	}
}
void DIO_connectpullup(unsigned char port,unsigned char pin,unsigned char connect)
{
	DIO_pinwrite(port,pin,connect);
}
