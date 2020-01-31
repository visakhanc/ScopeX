/*
 *	FILE		:	MENU.C 
 *	DESCRIPTION	:	Menu API for AVR oscilloscope
 *
 *	AUTHOR		: 	Visakhan C
 *	DATE		:	Feb 20, 2012
 *					Apr 17, 2013 (Update: array index access to menu items instead of pointers)
 */

#include <util/delay.h>
#include "menu.h"
#include "ks0108.h"
#include "buttons.h"

extern uint8_t small_font[] PROGMEM;
extern uint8_t Times_12[] PROGMEM;

static void DisplayMenu(const Menu *theMenu)
{
	uint8_t y_pos = 2;
	uint8_t n = 0;
	
	ks0108ClearScreen();
	ks0108GotoXY(30,y_pos);
	ks0108SelectFont(Times_12, ks0108ReadFontData, BLACK);
	ks0108Puts(theMenu->title);
	
	ks0108SelectFont(small_font, ks0108ReadFontData, BLACK);
	y_pos += 13;
	while(n < theMenu->item_count) {
		
		ks0108GotoXY(45,y_pos);
		ks0108Puts(theMenu->items[n].text);
		n++;
		y_pos += 11;
	}
}
	
void Do_Menu(const Menu *theMenu)
{
	uint8_t button_val;
	uint8_t y_pos = 14;
	uint8_t n = 0;

	DisplayMenu(theMenu);
	
	ks0108DrawRoundRect(30, y_pos, 70, 10, 5, BLACK);
	
	do {
		
		_delay_ms(140);
		button_val = Button_Read();
		
		switch (button_val) {
		
			case DOWN_KEY: 
				
				DisplayMenu(theMenu);
				if(n < theMenu->item_count-1) {
					n++;
					y_pos += 11;
				}
				ks0108DrawRoundRect(30, y_pos, 70, 11, 5, BLACK);
				
				break;
				
			case UP_KEY: 
			
				DisplayMenu(theMenu);
				if(n > 0) {
					n--;
					y_pos -= 11;
				}
				ks0108DrawRoundRect(30, y_pos, 70, 11, 5, BLACK);
				
				break;
				
			case OK_KEY:
			case RIGHT_KEY: 
				
				theMenu->items[n].Callback();  // Call the callback function for selected menu item
				DisplayMenu(theMenu);
				ks0108DrawRoundRect(30, y_pos, 70, 11, 5, BLACK);
				break;
				
				
			case LEFT_KEY:   // previous menu (if any)
				return;
		
		}
		
	} while(1);
	
}
