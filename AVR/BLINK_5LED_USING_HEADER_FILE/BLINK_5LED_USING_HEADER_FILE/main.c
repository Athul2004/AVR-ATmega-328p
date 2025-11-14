/*
 * BLINK_5LED_USING_HEADER_FILE.c
 *
 * Created: 29-09-2025 14:46:42
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "gpio.h"
#include<stdint.h>

int main(void)
{

	DDRB |= (1<<DDB5)|(1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1); // Initialise 5 pins as output

	while (1)
	{
		
		PORTB ^= (1<<PORTB5)|(1<<PORTB4)|(1<<PORTB3)|(1<<PORTB2)|(1<<PORTB1); // Turn ON all LEDs
		gpio(2000);

		

	}
}
