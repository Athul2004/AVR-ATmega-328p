/*
 * DELAY_1024.c
 *
 * Created: 19-09-2025 19:26:29
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s(void)
{
	unsigned int i, count = 61;
	for(i = 0;i<count;i++) //This will run for 61 times for getting 1sec delay (1 sec / 16.384ms = 61 times)
	{
		TCNT0 = 0;
		TCCR0A = 0; // FOR NORMAL CLOCK SOURCE
		TCCR0B |= (1 << CS02) | (1 << CS00); //101 FOR 1024 PRESCALING,SO SET CS02 and CS02 TO 1.(16Mhz/1024 = 15.625Khz)
		TIFR0 |= (1 << TOV0);  //SET OVERFLOW FLAG 0 BY WRITING 1 TO IT.
		while (!(TIFR0 & (1 << TOV0))); //WAITING TIMER OVERFLOW FLAG TO SET SO THAT WE GET 16.384ms DELAY.
	}
}



int main(void)
{
	
	DDRB |= (1 << DDB5);
	
	while (1)
	{
		PORTB ^= (1 << PORTB5);  // FOR BLINKING LED.
		delay_1s();
		
	}
}

