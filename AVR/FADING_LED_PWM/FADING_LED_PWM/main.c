/*
 * FADING_LED_PWM.c
 *
 * Created: 29-09-2025 01:49:17
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRD |= (1 << DDD6); //SET DDD6 AS OUTPUT FOR PWM
	TCCR0A |= (1 << WGM00 )|(1 << WGM01); //FOR FAST PWM MODE.
	TCCR0A |= (1 << COM0A1);  //FOR NON INVERTING
	TCCR0B |= (1 << CS00) | (1 << CS01); // 64 PRESCALING
	OCR0A = 0;
	//FADE IN FADE OUT USING INCREMENTING AND DECREMENTING DUTY CYCLE.
	while(1)
	{
		
		for (int i = 0; i <= 255; i++)
		{
			OCR0A = i;
			_delay_ms(20);
		}
		for (int i = 255; i >= 0; i--)
		{
			OCR0A = i;
			_delay_ms(20);
		}
		_delay_ms(1000);

		
	}
}

