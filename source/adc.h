/***********************************************

		ADC.H
					
	ADC  routunes for the AVR device
	
************************************************/

#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

/*		DEFINITIONS		*/

#define ADC_DDR DDRA
#define ADC_PORT PORTA

#define REF_AREF 0
#define REF_AVCC (1<<REFS0)
#define REF_INTERNAL ((1<<REFS1)|(1<<REFS0))
//#define CHANNEL_MASK (0b00011111)
#define PRESCALAR_4 (2<<ADPS0)
#define PRESCALAR_8 (3<<ADPS0) 
#define PRESCALAR_16 (4<<ADPS0) 
#define PRESCALAR_32 (5<<ADPS0) 
#define PRESCALAR_64 (6<<ADPS0) 
#define PRESCALAR_128 (7<<ADPS0) 



/*		FUNCTION PROTOTYPES		*/

void ADC_Init(uint8_t REF);
void ADC_Disable(void);
void ADC_SelChannel(uint8_t CH);
void ADC_SelClock(uint8_t prescalar);

uint8_t ADC_Read_8bit(void);
uint16_t ADC_Read_10bit(void);


#endif