/*
 * keybad_driver.h
 *
 * Created: 11/29/2023 2:46:13 PM
 *  Author: Ahmed Al-Sheikh
 */ 


#ifndef KEYBAD_DRIVER_H_
#define KEYBAD_DRIVER_H_
#define keybadport 'B'
#define NOTPRESSED 0xff
void keybad_init(void);
unsigned char keybad_checkpress(void);



#endif /* KEYBAD_DRIVER_H_ */