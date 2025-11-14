/*
 * MOTOR_FUNC_DELAY.c
 *
 * Created: 12-09-2025 17:42:06
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// -------- Variable delay function --------
void delay_variable(int delay_ms) {
	while (delay_ms > 0) {
		_delay_ms(1);   // 1 ms delay
		delay_ms--;     // reduce counter
	}
}

// -------- Motor Control Functions --------
void CW(int delay_ms) {
	PORTB |= (1 << PORTB5);    // PB5 = 1
	PORTB &= ~(1 << PORTB4);   // PB4 = 0
	delay_variable(delay_ms);  // run for given time
}

void CCW(int delay_ms) {
	PORTB |= (1 << PORTB4);    // PB4 = 1
	PORTB &= ~(1 << PORTB5);   // PB5 = 0
	delay_variable(delay_ms);
}

void STP(int delay_ms) {
	PORTB &= ~((1 << PORTB4) | (1 << PORTB5)); // PB4=0, PB5=0
	delay_variable(delay_ms);
}

// -------- Main Function --------
int main(void) {
	DDRB |= (1 << DDB4) | (1 << DDB5);  // Set PB4 & PB5 as OUTPUT

	while (1) {
		CW(2000);     // Rotate clockwise for 2 sec
		STP(1000);    // Stop for 1 sec
		CCW(2000);    // Rotate counter-clockwise for 2 sec
		STP(1000);    // Stop for 1 sec
	}
}

