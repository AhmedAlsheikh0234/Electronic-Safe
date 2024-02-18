/*
 * macros.h
 *
 * Created: 10/5/2023 3:22:58 AM
 *  Author: Ahmed Al-Sheikh
 */ 


#ifndef MACROS_H_
#define MACROS_H_
#define set_bit(reg,bit)  reg|=(1<<bit)
#define clr_bit(reg,bit)  reg&=~(1<<bit)
#define toggle_bit(reg,bit)  reg^=(1<<bit)
#define  read_bit(reg,bit)   ((reg&(1<<bit))>>bit)

#endif /* MACROS_H_ */
