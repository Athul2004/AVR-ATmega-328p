/*
 * USART_TXT.c
 *
 * Created: 26-10-2025 14:35:17
 * Author : KICHU
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    UBRR0H = 0;
	UBRR0L = 103; //SET BAUD RATE AS 9600
	UCSR0B |= (1 << TXEN0); // ENABLE TRANSMITION
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8 BIT DATA MODE
	
	char a[] = "Hello\n"; //this is our data
	int i;
    while (1) 
	{
		for(i = 0; a[i] != '\0'; i++)
		{
			while(!(UCSR0A & (1 << UDRE0)));
			UDR0 = a[i];
		}
		_delay_ms(1000);
	}
		
    
}

