/*
 * motor_func.c
 *
 * Created: 12-09-2025 16:31:45
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

// Function prototypes
void CW(void);
void CCW(void);
void STP(void);

int main(void)
{
	// Set PB4 and PB5 as outputs
	DDRB |= (1 << DDB4) | (1 << DDB5);

	while (1)
	{
		CW();      // Rotate motor clockwise
		_delay_ms(5000);

		STP();     // Stop motor (brake)
		_delay_ms(2000);

		CCW();     // Rotate motor counter-clockwise
		_delay_ms(5000);

		STP();     // Stop motor (brake)
		_delay_ms(2000);
	}
}

// Clockwise rotation
void CW(void)
{
	PORTB |= (1 << PORTB5);   // PB5 = 1
	PORTB &= ~(1 << PORTB4);  // PB4 = 0
}

// Counter-clockwise rotation
void CCW(void)
{
	PORTB |= (1 << PORTB4);   // PB4 = 1
	PORTB &= ~(1 << PORTB5);  // PB5 = 0
}

// Stop motor
void STP(void)
{
	PORTB &= ~((1 << PORTB4) | (1 << PORTB5)); // PB4=0, PB5=0
}
