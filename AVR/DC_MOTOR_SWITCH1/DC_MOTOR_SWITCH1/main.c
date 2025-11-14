/*
 * DC_MOTOR_SWITCH1.c
 *
 * Created: 15-09-2025 21:23:49
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
	DDRB |= (1 << DDB5);   // Set PB5 as output
	DDRB |= (1 << DDB4);   // Set PB4 as output
	DDRD &= ~(1 << DDD2);  // Set PD2 as input (switch)

	while (1)
	{
		if (PIND & (1 << PIND2))   // If switch is pressed (logic high at PD2)
		{
			PORTB |= (1 << PORTB5);
			PORTB &= ~(1 << PORTB4);   // CW
			_delay_ms(2000);

			PORTB &= ~(1 << PORTB4);
			PORTB &= ~(1 << PORTB5);   // STOP
			_delay_ms(2000);

			PORTB |= (1 << PORTB4);
			PORTB &= ~(1 << PORTB5);   // CCW
			_delay_ms(2000);

			PORTB &= ~(1 << PORTB4);
			PORTB &= ~(1 << PORTB5);   // STOP
			_delay_ms(2000);
		}
		else
		{
			PORTB &= ~(1 << PORTB4);   // STOP if switch not pressed
			PORTB &= ~(1 << PORTB5);
		}
	}
}



