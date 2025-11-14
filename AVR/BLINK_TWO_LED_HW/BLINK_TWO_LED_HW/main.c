/*
 * BLINK_TWO_LED_HW.c
 *
 * Created: 14-09-2025 14:43:46
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
	DDRD = (1 << PD2) | (1 << PD3);   // Set PD2 and PD3 as output

	while (1)   // infinite loop
	{
		PORTD = (1 << PD2);   // RED LED ON (PD3 HIGH)
		_delay_ms(1000);

		PORTD = (1 << PD3);   // GREEN LED ON (PD2 HIGH)
		_delay_ms(1000);
	}
}


