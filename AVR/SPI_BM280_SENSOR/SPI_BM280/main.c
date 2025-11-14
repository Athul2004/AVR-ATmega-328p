/*
 * SPI_BM280.c
 *
 * Created: 02-11-2025 17:48:45
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint8_t dummy, chip_id;

	// PB0 = LED, PB2 = SS, PB3 = MOSI, PB5 = SCK
	DDRB |= (1 << DDB0) | (1 << DDB2) | (1 << DDB3) | (1 << DDB5);
	DDRB &= ~(1 << DDB4); // MISO as input

	// Enable SPI, Master, fck/16, Mode 0
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	SPCR &= ~((1 << CPOL) | (1 << CPHA));

	// Begin transaction
	PORTB &= ~(1 << PB2);              // CS LOW

	SPDR = 0xD0 | 0x80;                // send command
	while (!(SPSR & (1 << SPIF)));
	dummy = SPDR;
	(void)dummy;

	SPDR = 0x00;                        // dummy write to read response
	while (!(SPSR & (1 << SPIF)));
	chip_id = SPDR;
	

	PORTB |= (1 << PB2);               // CS HIGH

	// Indicate result
	while (1) {
		if (chip_id == 0x58)
		PORTB |= (1 << PB0);
		else
		PORTB &= ~(1 << PB0);
	}
}

