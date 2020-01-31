/*
 *		UTILS.C
 *
 *		Utility functions
 *		Apr 24, 2013
 */
 
 #include "ks0108.h"
 #include "utils.h"
 
 void Write_Number(uint16_t num, uint8_t dot_pos, uint8_t round_off)
 {
	
	uint8_t i=0;
	char arr[5];
	uint16_t p;
	
	do {
	
		p = num/10;
		arr[i++] =  num - p*10;
		num = p;
	
	} while(num);
	
	while(i--) {
		
		if( (round_off) && (i == (round_off-1) ) ) break;
		
		ks0108PutChar(arr[i]+48);
		if( (dot_pos) && (i == dot_pos) )
			ks0108PutChar('.');
	}
	
}