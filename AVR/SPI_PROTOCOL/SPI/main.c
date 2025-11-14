/*
 * SPI.c
 *
 * Created: 30-10-2025 23:34:03
 * Author : KICHU
 */ 

#include <avr/io.h>
#include <util/delay.h>

// Define the SPI pins
#define DDR_SPI DDRB
#define PORT_SPI PORTB
#define PIN_MOSI PB3
#define PIN_MISO PB4
#define PIN_SCK  PB5
#define PIN_SS   PB2

void spi_master_init(void) {
  // Set MOSI, SCK, and SS as output
  DDR_SPI |= (1 << PIN_MOSI) | (1 << PIN_SCK) | (1 << PIN_SS);
  
  // Set MISO as input
  DDR_SPI &= ~(1 << PIN_MISO);

  // Enable SPI (SPE), set as Master (MSTR), and set clock rate (fck/16)
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

char spi_master_transmit(char data) {
  // 1. Pull SS LOW to select slave
  PORT_SPI &= ~(1 << PIN_SS);

  // 2. Write data to the SPI Data Register
  SPDR = data;

  // 3. Wait for the transmission to complete
  //    The SPIF bit in SPSR is set when transfer is done
  while (!(SPSR & (1 << SPIF)));
  
  // 4. Pull SS HIGH to deselect slave
  PORT_SPI |= (1 << PIN_SS);

  // 5. Return the data that was in the register (sent from slave)
  return SPDR;
}

int main(void) {
  spi_master_init();
  // (Serial port init would go here if you want to print)
  
  while (1) {
    char received_data = spi_master_transmit('H');
    // 'received_data' should now be 'A'
    _delay_ms(1000);
  }
  return 0;
}
