/*
 * ACTIVE_HIGH_SWICH.c
 *
 * Created: 11-09-2025 23:20:25
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
	DDRC=0b00000000; // DC0 -input connected to switch
	DDRD=0b00001000; // DC3 - output connected to LED
	//PORTC = 0b00000001;
	
	while (1)
	{
		if (PINC==0b00000000)
		{
			PORTD=0b00001000;
		}
		else
		{
			PORTD=0b00000000;
		}
	}
}


