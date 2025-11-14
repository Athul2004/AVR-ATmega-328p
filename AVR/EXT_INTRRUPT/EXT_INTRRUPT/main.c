
/*
 * EXT_INTRRUPT.c
 *
 * Created: 05-10-2025 13:24:42
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect)
{
	PORTB^=(1<<PORTB5);
	_delay_ms(10000);
}

int main(void)
{
	DDRB|=(1<<DDB5); // PB5 OUTPUT
	DDRD&=~(1<<DDD2); // PD2 as input
	PORTD|=(1<<PORTD2); // making internal pull up on pd2
	DDRB|=(1<<DDB4); // pb4 as output
	sei(); // enable SREG 7th bit
	EIMSK|=(1<<INT0); // enable int0 on pd2
	EICRA|=(1<<ISC01); // int0 falling edge
	while (1)
	{
		PORTB^=(1<<PORTB4);
		_delay_ms(1000);
	}
	
}




