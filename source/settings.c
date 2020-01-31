/*
 *		SETTINGS.C
 *		
 *		May 12, 2013
 *		Visakhan C
 *
 */
 
#include "settings.h"
#include "ks0108.h" 

void Backlight_Init(void)
{
	BACKLIGHT_DDR |= BACKLIGHT_POS;  // configure pin as output
	BACKLIGHT_PORT &= ~(BACKLIGHT_POS);  // turn on backlight 
}


void Backlight_On(void)
{
	BACKLIGHT_PORT &= ~(BACKLIGHT_POS);
}

void Backlight_Off(void)
{
	BACKLIGHT_PORT |= BACKLIGHT_POS;
}
