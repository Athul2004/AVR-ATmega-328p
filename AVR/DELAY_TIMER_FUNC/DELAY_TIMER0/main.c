/*
 * DELAY_1024.c
 *
 * Created: 19-09-2025 19:26:29
 * Author : KICHU
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>

void delay_1s(void){
	unsigned int i;
	unsigned int count=976;
	for(i=0; i<count; i++){
		TCNT0=0;
		TCCR0A=0;
		TCCR0B|=(1<<CS00);
		TCCR0B|=(1<<CS01);
		TIFR0|=(1<<TOV0);
		
		while(!(TIFR0 & (1<<TOV0)));
	}
}
int main(void)
{
	DDRB|=(1<<DDB5);
	while (1)
	{
		PORTB^=(1<<PORTB5);
		delay_1s();

	}
}


