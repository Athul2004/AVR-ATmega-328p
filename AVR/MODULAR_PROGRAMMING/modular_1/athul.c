/*
 * athul.c
 *
 * Created: 26-09-2025 20:46:13
 *  Author: KICHU
 */ 
#include <avr/io.h>

void timer0_init(void)
{
	TCCR0A|=(1<<WGM01);
	OCR0A=249;// for count 250
	TCNT0=0;// making timer counter 0
	TCCR0B|=(1<<CS00);
	TCCR0B|=(1<<CS01);//prescalar 64
	TIFR0|=(1<<OCF0A);//setting flag to 0 by writing one
}

void athul(uint16_t ms)
{
	timer0_init();
	while(ms--)// CREATES DELAY FOR MS MILLISECOND
	{
		while(!(TIFR0&(1<<OCF0A))) // 1MS LOOP
		{
			
		}
		TIFR0|=(1<<OCF0A);
		
		
	}
}