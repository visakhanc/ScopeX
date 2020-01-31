/*	
 *		5 BUTTON INTERFACE FOR AVR-OSCILLOSCOPE
 *
 *		Author	: Visakhan C
 *		Date	: May 02, 2013
 *
 */
 


#ifndef BUTTONS_H
#define BUTTONS_H

#include <avr/io.h>

#define BUTTON_PORT	PORTD
#define BUTTON_PIN	PIND
#define BUTTON_DDR	DDRD

#define	OK_KEY		(1<<PD1)
#define	UP_KEY		(1<<PD2)
#define DOWN_KEY	(1<<PD3)
#define RIGHT_KEY	(1<<PD4)
#define LEFT_KEY	(1<<PD0)


void Button_Init(void);
uint8_t Button_Read(void);

#endif