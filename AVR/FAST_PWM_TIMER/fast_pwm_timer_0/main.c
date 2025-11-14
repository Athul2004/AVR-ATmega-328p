/*
 * fast_pwm_timer_0.c
 *
 * Created: 24-09-2025 20:58:59
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRD |= (1 << DDD6); //SET DDD6 AS OUTPUT FOR PWM
	TCCR0A |= (1 << WGM00) | (1 << WGM01); //FOR FAST PWM MODE.
	TCCR0A |= (1 << COM0A1);  //FOR NON INVERTING
	TCCR0B |= (1 << CS00) | (1 << CS01); // 64 PRESCALING
	OCR0A = 200; // SETPOINT,ANY VALUE LESS THAN 255  SINCE IT'S AN 8 BIT REGISTER.
	
	while(1)
	{
		
	}
}
