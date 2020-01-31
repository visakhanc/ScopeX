/*
	 *	FILE		:	CAPTURE.C 
	 *	DESCRIPTION	:	Implements capture input of AVR oscilloscope
	 *					Uses Input Capture of Timer1 
	 *
	 *	AUTHOR		: 	Visakhan C
	 *	DATE		:	Apr 25, 2013
	 *
	 *	Changes:
	 *		Uses AVR Analog Comparator output (instead of ICP1) input for triggering Input Capture Unit
	 *		(May 02, 2013): Uses updated Read_Button() function
	 */	
	 

#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

#include "capture.h"
#include "ks0108.h"
#include "buttons.h"
#include "utils.h"

#define TIME_SCALE_COUNT sizeof(time_scales)

static volatile uint8_t capt_finished;
static volatile uint16_t iTimeL, iTimeH;
static LogicMode_t mode;
static Edge_t cEdge;
static uint8_t edge_count;
static uint16_t captBuf[MAX_CAPT];
static uint8_t time_scales[] = {1, 2, 5, 10, 20, 50, 100, 200}; 

static inline void Enable_LA(void)
{
	TIMSK =	(1 << TICIE1); // Input Capture Interrupt enable
}

static inline void Disable_LA(void)
{
	TIMSK &= ~(1<<TICIE1); // disable Input Capture interrupt	
}


/* Initialise Logic analyser component */
static void Init_LA(void)
{
	// Set up Analog Comparator
	DDRB &= ~((1 << PB2)|(1 << PB3));  // Analog Comparator input pins as Input
	PORTB &= ~((1 << PB2)|(1 << PB3)); // and Pull-ups disabled
	
	ACSR = (1 << ACIC);	// AIN0 as Positive input; enable Analog Comparator Input Capture
	ADCSRA &= ~((1 << ADEN)|(1 << ADIE));	// disable ADC and interrupt,
	SFIOR |= (1 << ACME); 			// to use ADC MUX for selecting Analog Comparator Negative input
	ADMUX &= ~(0x1F);	// Select ADC Ch:0 as Negative input of Analog Comparator
	
	// Set up Input Capture Unit
	TCCR1B = 0x2; //Start Timer1, Input Capture: low edge trigger, prescalar:8 (16/8 = 2MHz)
	TIFR = (1<<ICF1);	// Clear Input Capture flag
}

void LA_Measure(void) {

	uint16_t iPeriod = 1, iTimeHTemp, iTimeLTemp, iFreq, iDuty;
	uint8_t cHighRes = false;
	
	Init_LA();
	Enable_LA();
	
	
	
	do {
	
		iTimeHTemp = iTimeH;  	// critical
		iTimeLTemp = iTimeL;	// section ??!!
		
		iPeriod = iTimeHTemp + iTimeLTemp;
		if(cHighRes == false) {
			
			if(iPeriod < 500) {		
				cHighRes = true;
				TCCR1B = 0x1; //No prescaling, (falling edge capture!)
			}
		}
		else {
		
			if(iPeriod > 4000) {	
				cHighRes = false;
				TCCR1B = 0x2; //prescalar:8, (falling edge capture!)
			}
		}
		
		iPeriod >>= 1;	// time in uS
		iTimeHTemp >>= 1;
		if(cHighRes) {
			iPeriod >>= 3;  //divide by 8 - get time in uS	
			iTimeHTemp >>= 3;
		}
		
		_delay_ms(150);
		
		ks0108ClearScreen();
		ks0108GotoXY(15, 15);
		ks0108Puts("T = ");
		Write_Number(iPeriod, 5, 0);
		ks0108Puts("us");
		ks0108GotoXY(15, 30);
		ks0108Puts("f = ");
		
		// display Frequency
		if(iPeriod > 2000) 	{
		
			iFreq = 100000000/iPeriod;
			Write_Number(iFreq, 2, 0);	
			
		} else if(iPeriod > 20) {
		
			iFreq = 1000000/iPeriod;
			Write_Number(iFreq, 0, 0);	
			
		} else {
		
			iFreq = 100000/iPeriod;
			Write_Number(iFreq, 2, 0);
			ks0108Puts(" k");  
		}
		
		ks0108Puts("Hz");
		ks0108GotoXY(15, 45);
		ks0108Puts("Duty % = ");
	
		// display Duty
		iDuty = ((unsigned long)iTimeHTemp*100)/iPeriod;
		Write_Number(iDuty, 0, 0);
		
	} while(!(Button_Read() & OK_KEY));

}


void LA_Capture(Edge_t edge)
{
	uint8_t k, x, y, button_val, t_scale, init_k = 1, t_pos = 5, temp;
	uint16_t dist;
	
	Disable_LA();
	
	mode = CAPTURE;
	Init_LA();
	cEdge = edge;
	if(edge == LOW_EDGE) 
		TCCR1B |= (1 << ICES1);  // high edge trigger (inverted for Analog Comparator)
	
	edge_count = 0;
	capt_finished = false;
	
	Enable_LA();
	
	while(!capt_finished)  // Wait until capture finishes
		;  


	do {
	
		/*  Write time-stamps (in uS) to GLCD */
		
	/*	pos_x = 5; pos_y = 5; k = 0;
		
		ks0108GotoXY(pos_x, pos_y);
		for(i = 0; i < 4; i++) {
			for(j = 0; j < 5; j++) {
				Write_Number(captBuf[k++],0);
				ks0108Puts("   ");
			}
			pos_y += 12;
			ks0108GotoXY(pos_x, pos_y);
		}
	*/
		k = init_k;
		x = 0;
		y = 21;
		t_scale = time_scales[t_pos];
	
		ks0108ClearScreen();
		ks0108DrawLine(x, y, x, y+21, BLACK);
		y += 21;
		
		if(edge == HIGH_EDGE) {
			y = 21;
			ks0108GotoXY(0, 21);
			dist = captBuf[k++]/(t_scale*2);
			ks0108DrawLine(x, y, x+dist, y, BLACK);
			x += dist;
			ks0108DrawLine(x, y, x, y+21, BLACK);
			y += 21;
		}
		
		do {
		
			dist = captBuf[k++]/(t_scale*2);			// gets time in uS							 
			if( x+dist > 127 ) {
				ks0108DrawLine(x, y, 127, y, BLACK);
				break;
			}
			ks0108DrawLine(x, y, x+dist, y, BLACK);		//			|
			x += dist;									//			|
			ks0108DrawLine(x, y, x, y-21, BLACK);		//			|
			y -= 21;									//	________|
			
			dist = captBuf[k++]/(t_scale*2);			// gets time in uS
			if( x+dist > 127 ) {
				ks0108DrawLine(x, y, 127, y, BLACK);
				break;					
			}											//  ________
			ks0108DrawLine(x, y, x+dist, y, BLACK);		//			|
			x += dist;									//			|
			ks0108DrawLine(x, y, x, y+21, BLACK);		//			|
			y += 21;									//			|
			
		} while(k < MAX_CAPT);
		
		
		// Display time scale
		ks0108GotoXY(37, 7);
		ks0108Puts("T/Div = ");
		Write_Number(t_scale*10, 0, 0);
		ks0108Puts(" uS");
		
		ks0108DrawHoriLine(0, 50, 127, BLACK); 
		for(temp = 0; temp < 128; temp += 10) 
			ks0108DrawVertLine(temp, 48, 5, BLACK);
		
		_delay_ms(150);
	
		do { 
			
			button_val = Button_Read();
		
		} while( !(button_val & (LEFT_KEY|RIGHT_KEY|OK_KEY|UP_KEY|DOWN_KEY)) );
		
		switch(button_val) {
		
			case DOWN_KEY	: 	if(t_pos < TIME_SCALE_COUNT-1) t_pos++; break;
			case UP_KEY		: 	if(t_pos > 0) t_pos--; break;
			case RIGHT_KEY	: 	if(init_k < MAX_CAPT-1) {
									init_k++;
									if(edge == LOW_EDGE) 
										edge = HIGH_EDGE;
									else edge = LOW_EDGE;
								}
								break;
								
			case LEFT_KEY	:	 if(init_k > 1) {
									init_k--;
									if(edge == LOW_EDGE) 
										edge = HIGH_EDGE;
									else edge = LOW_EDGE;
								} 
			
		}
		
		/*
		if(button_val == DOWN_KEY) {
			if(t_pos < TIME_SCALE_COUNT-1) t_pos++; 
		}
		else if (button_val == UP_KEY) {
			if(t_pos > 0) t_pos--;
		}
		else if (button_val == RIGHT_KEY) {
			if(init_k < MAX_CAPT-1) {
				init_k++;
				if(edge == LOW_EDGE) 
					edge = HIGH_EDGE;
				else edge = LOW_EDGE;
			}
		}
		else if(button_val == LEFT_KEY) {
			if(init_k > 1) {
				init_k--;
				if(edge == LOW_EDGE) 
					edge = HIGH_EDGE;
				else edge = LOW_EDGE;
			}
		}		
		*/
	} while(button_val != OK_KEY);
	
}

/*  Timer1 Input Capture ISR  */
ISR(TIMER1_CAPT_vect)
{

	static uint16_t prev_ICR;
	uint16_t curr_ICR;
	uint16_t diff;
	
	curr_ICR = ICR1;
	diff = curr_ICR - prev_ICR;
	
	if( (mode == CAPTURE) && (capt_finished == false) ) {
	
		captBuf[edge_count++] = diff;
		if(edge_count == MAX_CAPT)
			capt_finished = true;
	}

	if(cEdge == LOW_EDGE) {
		
		iTimeH = diff;
		TCCR1B &= ~(1<<ICES1);  // Next, high edge (inverted for Ana. Comp)
		cEdge = HIGH_EDGE;
	}
	else {
	
		iTimeL = diff;
		TCCR1B |= (1<<ICES1); // Next, low edge (inverted for Ana. Comp)
		cEdge = LOW_EDGE;
	}	
	
	prev_ICR = curr_ICR;
	//TIFR = (1<<ICF1);
	
}

