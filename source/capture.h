/*
 *	FILE		:	CAPTURE.H 
 *	DESCRIPTION	:	Implements capture unit of AVR oscilloscope
 *					Uses Input Capture of Timer1
 *
 *	AUTHOR		: 	Visakhan C
 *	DATE		:	Feb 16, 2013
 *	
 */

#include <stdint.h>

#define		MAX_CAPT 	100

typedef enum { MEASURE, CAPTURE } LogicMode_t;
typedef enum {LOW_EDGE, HIGH_EDGE} Edge_t;

void LA_Measure(void);
void LA_Capture(Edge_t);

 