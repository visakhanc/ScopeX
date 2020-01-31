/* 
 *		SCOPE.C
 *
 *		Apr 10, 2013
 *
 *		
 *		Contains ADC ISR
 *
 *		Changes:	ADC average value computed from 32-bit running sum, instead of array of 16_bit sums
 *								Trigger point detection problem corrected 
 *								Handles two channels, but display one at a time; 100 byte buffer for each channel
 */
 
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

#include "ks0108.h"
#include "scope.h"
#include "adc.h"
#include "buttons.h"
#include "utils.h"

const uint8_t raster_screen[] PROGMEM = {

	 255,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1
	, 1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1
	, 1,3,1,1,1,1,1,1,1,1,1,1,3,1,1,1
	, 1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1
	, 1,1,3,1,1,1,1,1,1,1,1,1,1,3,1,1
	, 1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1
	, 1,1,1,1,255,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	, 255,8,0,0,0,0,0,0,0,0,0,8,0,0,0,0
	, 0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0
	, 0,8,0,0,0,0,0,0,0,0,0,0,8,0,0,0
	, 0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0
	, 0,0,8,0,0,0,0,0,0,0,0,0,0,8,0,0
	, 0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0
	, 0,0,0,8,255,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	, 255,32,0,0,0,0,0,0,0,0,0,32,0,0,0,0
	, 0,0,0,0,0,0,32,0,0,0,0,0,0,0,0,0
	, 0,32,0,0,0,0,0,0,0,0,0,0,32,0,0,0
	, 0,0,0,0,0,0,0,32,0,0,0,0,0,0,0,0
	, 0,0,32,0,0,0,0,0,0,0,0,0,0,32,0,0
	, 0,0,0,0,0,0,0,0,32,0,0,0,0,0,0,0
	, 0,0,0,32,255,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	, 255,0,0,0,0,0,0,0,0,0,0,128,0,0,0,0
	, 0,0,0,0,0,0,128,0,0,0,0,0,0,0,0,0
	, 0,128,0,0,0,0,0,0,0,0,0,0,128,0,0,0
	, 0,0,0,0,0,0,0,128,0,0,0,0,0,0,0,0
	, 0,0,128,0,0,0,0,0,0,0,0,0,0,128,0,0
	, 0,0,0,0,0,0,0,0,128,0,0,0,0,0,0,0
	, 0,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	, 255,1,1,0,0,1,0,0,1,0,0,3,0,0,0,1
	, 0,0,1,0,0,0,3,0,0,0,1,0,0,1,0,0
	, 0,3,0,0,0,1,0,0,1,0,0,0,3,0,0,0
	, 1,0,0,1,0,0,0,3,0,0,0,1,0,0,1,0
	, 0,0,3,0,0,0,1,0,0,1,0,0,0,3,0,0
	, 0,1,0,0,1,0,0,0,3,0,0,0,1,0,0,0
	, 1,0,0,1,255,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	, 255,8,0,0,0,0,0,0,0,0,0,8,0,0,0,0
	, 0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0
	, 0,8,0,0,0,0,0,0,0,0,0,0,8,0,0,0
	, 0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0
	, 0,0,8,0,0,0,0,0,0,0,0,0,0,8,0,0
	, 0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0
	, 0,0,0,8,255,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	, 255,32,0,0,0,0,0,0,0,0,0,32,0,0,0,0
	, 0,0,0,0,0,0,32,0,0,0,0,0,0,0,0,0
	, 0,32,0,0,0,0,0,0,0,0,0,0,32,0,0,0
	, 0,0,0,0,0,0,0,32,0,0,0,0,0,0,0,0
	, 0,0,32,0,0,0,0,0,0,0,0,0,0,32,0,0
	, 0,0,0,0,0,0,0,0,32,0,0,0,0,0,0,0
	, 0,0,0,32,255,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	, 255,128,128,128,128,128,128,128,128,128,128,192,128,128,128,128
	, 128,128,128,128,128,128,192,128,128,128,128,128,128,128,128,128
	, 128,192,128,128,128,128,128,128,128,128,128,128,192,128,128,128
	, 128,128,128,128,128,128,128,192,128,128,128,128,128,128,128,128
	, 128,128,192,128,128,128,128,128,128,128,128,128,128,192,128,128
	, 128,128,128,128,128,128,128,128,192,128,128,128,128,128,128,128
	, 128,128,128,128,255,0,0,0,0,0,0,0,0,0,0,0
	, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

}; 


extern uint8_t small_font[] PROGMEM;

/*  GLOBALS  */

static uint8_t ch1_samples[100], ch2_samples[100];
static volatile bool plot, dual_ch; 
static volatile uint8_t adc_avg, vpp_ch1, vpp_ch2;
static volatile ScopeChannel_t curr_ch;


/*  FUNCTIONS  */

/* pSamp are 8-bit samples from ADC; So scaling by 4 reduces these values to  max: 63, for plotting */
void Begin_Scope(ScopeChannel_t ch) 
{
	uint8_t x, t, button_val = 4, t_scale = 1;
	uint16_t vpp;
	
	_delay_ms(170);
	
	plot = dual_ch = false;
	curr_ch = ch;
	
	switch (ch) {
		
		case CH1: 		ADC_Init(0); break;
		case CH2: 		ADC_Init(1); break;
		case BOTH_CH: 	ADC_Init(0);
						dual_ch = true;
						curr_ch = CH1;
						break;
	}
	
	ks0108SelectFont(small_font, ks0108ReadFontData, BLACK);
		
	
	do {
		
		if(plot == true) {
		
			ks0108DrawBitmap(raster_screen);
			x = t = 0;
			
			
			while(t < 99) {
				
				if(dual_ch == true || ch == CH1) 
					ks0108DrawLine(t, 63 - ch1_samples[x]/4, t+t_scale, 63 - ch1_samples[x+1]/4, BLACK);
					//ks0108SetDot(t, 63 - ch1_samples[x]/4, BLACK);
				if(dual_ch == true || ch == CH2)
					ks0108DrawLine(t, 63 - ch2_samples[x]/4, t+t_scale, 63 - ch2_samples[x+1]/4, BLACK);
					//ks0108SetDot(t, 63 - ch2_samples[x]/4, BLACK);
				x++;
				t += t_scale;
			}
			
			plot = false;
			
		}
		
		
		ks0108GotoXY(103,2);
		ks0108Puts("CH1");
		ks0108GotoXY(103, 12);
		
		if(ch == CH2) 
			ks0108Puts(" OFF");
		else { //if(curr_ch == CH1) {
			vpp = vpp_ch1 * 41;
			if(vpp_ch1 > 24) {
				Write_Number(vpp, 3, 1);
				ks0108Puts(" V");
			}
			else {
				Write_Number(vpp, 0, 0);
				ks0108Puts(" mV");
			}
		}
		
		ks0108GotoXY(103,32);
		ks0108Puts("CH2");
		ks0108GotoXY(103, 42);
		
		if(ch == CH1) 
			ks0108Puts(" OFF");
		else {//if(curr_ch == CH2) {
			vpp = vpp_ch2 * 41;
			if(vpp_ch2 > 24) {
				Write_Number(vpp, 3, 1);
				ks0108Puts(" V");
			} 
			else {
				Write_Number(vpp, 0, 0);
				ks0108Puts(" mV");
			}
		}
		
		_delay_ms(50);
		button_val = Button_Read();
			
		if(button_val & RIGHT_KEY) {
			if(t_scale < 4) {
				t_scale <<= 1;
			}
		}
		else if(button_val & LEFT_KEY) {
			if(t_scale > 1) {
				t_scale >>= 1;
			}
		}
		
	} while( !(button_val & OK_KEY) );
	
	/* while leaving disable ADC and its interrupt */
	ADC_Disable();
	
}


/* ADC ISR  */
ISR(ADC_vect)
{	
	static uint8_t i, adc_val, adc_min, adc_max;
	static ScopeState_t status = AVG_COMPUTING;
	static uint32_t samp_sum;
	static uint16_t samp_count;
	static uint8_t *buf;
	
	switch(status) {
	
		case AVG_COMPUTING: 
	
			adc_val = ADCH;
			if(adc_val < adc_min) adc_min = adc_val;
			if(adc_val > adc_max) adc_max = adc_val;
			
			samp_sum += adc_val;
			if( (++samp_count) == 1024) {

				adc_avg = (uint8_t)(samp_sum << 10);  // divide by 4096
				if(curr_ch == CH1) 
					vpp_ch1 = adc_max - adc_min;
				else
					vpp_ch2 = adc_max - adc_min;
					
				status = AVG_COMPUTED;
				samp_count = samp_sum = 0;
				adc_max = 0;
				adc_min = 255;
			}
			break;
				
		case AVG_COMPUTED: 
	
			if( ADCH < adc_val)
				status = FALLING_EDGE;
			adc_val = ADCH;
			
			break;
	
		case FALLING_EDGE:
		
			if( ADCH > adc_val ) 
				status = RISING_EDGE;
			adc_val = ADCH;
			break;
				
		case RISING_EDGE:
		
			if( ADCH > adc_avg) {
			
				status = TRIGGERED;
				if(curr_ch == CH1)
					buf = ch1_samples;
				else
					buf = ch2_samples;
			}
			break;
		
		case TRIGGERED:
			
			adc_val = ADCH;
			if(plot == false) {  // needed? yes!
				
				buf[i++] = adc_val;

				if(i == 100) {
					
					i = 0;
					plot = true;
					
					if(dual_ch == true) {
						if(curr_ch == CH1) {
							curr_ch = CH2;
							ADC_SelChannel(1);
						}
						else {
							curr_ch = CH1;
							ADC_SelChannel(0);
						}
					}
					status = AVG_COMPUTING;
				}	
			
			}
			else
				status = AVG_COMPUTING;
			
			break;
			
			
		default: status = AVG_COMPUTING;
		
	}
	
}
