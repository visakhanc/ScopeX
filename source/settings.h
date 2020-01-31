/*
 *		SETTINGS.H
 *		
 *		May 12, 2013
 *		Visakhan C
 *
 */
 
#ifndef SETTINGS_H
#define SETTINGS_H
 
#include <avr/io.h>

#define BACKLIGHT_DDR	DDRD
#define BACKLIGHT_PORT	PORTD
#define BACKLIGHT_POS 	(1 << PD5)

void Backlight_Init(void);
void Backlight_On(void);
void Backlight_Off(void);
 
#endif
 
 