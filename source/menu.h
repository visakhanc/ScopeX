/*
 *	FILE		: 	MENU.H
 *	DESCRIPTION	:	Menu API for AVR Oscilloscope
 *
 *	AUTHOR		: 	Visakhan C
 *	DATE		:	Feb 20, 2012
 *					Apr 17, 2013 (Update: array index access to menu items instead of pointers)
 */
 
#ifndef MENU_H
#define MENU_H

#include <stdint.h>



/*  Defines  */

typedef struct _MenuItem {

	char* text;
	void (*Callback)(void);
	
} MenuItem;


typedef struct _Menu {

	char *title;
	MenuItem *items;
	uint8_t item_count;
	
} Menu;



/*  Functions  */

void Do_Menu(const Menu *pMenu);

#endif