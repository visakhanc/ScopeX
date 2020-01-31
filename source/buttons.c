/*	
 *		5 BUTTON INTERFACE FOR AVR-OSCILLOSCOPE
 *
 *		Author	: Visakhan C
 *		Date	: Dec 14, 2012
 *				  Update (May 02, 2013) : Button_Read() now returns the status by value (not by pointer)
 */


#include "buttons.h"

void Button_Init(void)
{
	
	BUTTON_DDR &= ~(OK_KEY|UP_KEY|DOWN_KEY|LEFT_KEY|RIGHT_KEY) ; 	// button ports as input
	BUTTON_PORT |= OK_KEY|UP_KEY|DOWN_KEY|LEFT_KEY|RIGHT_KEY ;		// enable pull-ups

}

/*
void button_read(uint8_t *key_stat)
{
	
	*key_stat = ~(BUTTON_PIN);
	
}
*/

uint8_t Button_Read(void)
{
	return (~BUTTON_PIN) & (OK_KEY|UP_KEY|DOWN_KEY|LEFT_KEY|RIGHT_KEY);	
}
