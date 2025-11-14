/*
 * ADC.c
 *
 * Created: 19-10-2025 17:02:23
 * Author : KICHU
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


void ADC_Init(void)
{
    ADMUX |= (1 << REFS0); // Reference = AVCC (5V) IN
	ADCSRA |= (1 << ADEN)| (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // ENABLE PRESCLAR
}

uint16_t ADC_Read(uint8_t channel) // ADC READINGS
{
	channel &= 0x07;                   //Limit to 0-7
	ADMUX = (ADMUX & 0xF8) | channel;   //select channel
	ADCSRA |= (1 << ADSC);            //START CONVERSATION
	while (ADCSRA & (1 << ADSC));
	return (ADCL | (ADCH << 8));
}
int main(void)
{
	uint16_t adc_value;
	lcd_init();
	ADC_Init(); //call ADC initialization function
	while (1)	
    {
		float temp;
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_print("Temperature:");
		adc_value = ADC_Read(0);
		temp= adc_value*0.488;
		lcd_set_cursor(1,0);
		lcd_print_float(temp);
		lcd_data(0xDF);
		lcd_print("C");
		_delay_ms(500);
		
    }
}

