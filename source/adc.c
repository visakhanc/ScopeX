/***********************************************

		ADC.C
					
	ADC  routunes for the AVR 
	
************************************************/


#include "adc.h"

static inline void ADC_IntDisable(void) 
{
	ADCSRA &= ~(1<<ADIE); //disable ADC interrupt
}

static inline void  ADC_IntEnable(void) 
{
	ADCSRA |= (1<<ADIE); //disable ADC interrupt
}


/* Initialize ADC in auto-triggered mode with interrupt enabled  */
void ADC_Init(uint8_t CH)
{
	ADC_DDR &= ~( (1 << PA0)|(1 << PA1) );  // ADC channel 0 is input
	
	ADMUX = REF_AVCC | (1<<ADLAR) ;  // select ADC reference voltage and Left-shift (for 8-bit result)
	ADMUX |= (CH & 0x07);
	
	ADCSRA =  (1<<ADEN)|PRESCALAR_16 ; //Enables ADC
	ADCSRA |= (1<<ADSC); // start dummy conversion
	while ( !(ADCSRA & (1<<ADIF)) ) // wait for dummy conversion to finish and clear flag
		; 
	ADCSRA |= (1<<ADIF);
	
	ADCSRA |= (1<<ADIE)|(1<<ADATE);  // Enable ADC interrupt and Auto-trigger mode
	ADCSRA |= (1<<ADSC);	// start conversion (ADC ISR will take over)
}

/* Disable ADC and interrupt  */
void ADC_Disable(void)
{
	ADC_IntDisable();
	ADCSRA |= (1 << ADIF); // disable ADC while clearing interrupt flag
	
}

/*  change reference source and/or channel	*/
void ADC_SelChannel(uint8_t CH)
{
	ADMUX &= ~0x07;
	ADMUX |= (CH & 0x07);
}	
 
void ADC_SelClock(uint8_t prescalar)
{
	ADCSRA &= ~(0x07);
	ADCSRA |= (prescalar & 0x07);
}
 

/*  Do a single converion and returns result in 8-bits */
uint8_t ADC_Read_8bit(void)
{
	ADC_IntDisable();
	ADMUX |= (1<<ADLAR);//enablele ADLAR (for 8-bit result)
	ADCSRA |= (1<<ADSC); // start conversion
	while ( !(ADCSRA & (1<<ADIF)) ) 
		; // wait for the conversion to finish

	ADCSRA |= (1<<ADIF); // clear ADIF flag by writing  1 to it
	return ADCH; // return 8-bit result
}


/*  Do a single converion and returns result in 16-bits */
uint16_t ADC_Read_10bit(void)
{
	ADC_IntDisable();
	ADMUX &= ~(1<<ADLAR); // clear ADLAR bit for full 10-bit conversion
	ADCSRA |= (1<<ADSC); // start conversion
	while ( !(ADCSRA & (1<<ADIF)) ) 
		; // wait for the conversion to finish
		
	ADCSRA |= (1<<ADIF); // clear ADIF flag by writing  1 to it
	return ADC;
	
}