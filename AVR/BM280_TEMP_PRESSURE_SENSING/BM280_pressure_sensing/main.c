/*
 * BM280_pressure_sensing.c
 *
 * Created: 10-11-2025 20:48:30
 * Author : KICHU
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"   // Your UART library for serial output

int main(void)
{
	// --- Variable declarations ---
	uint16_t dig_T1, dig_P1;
	int16_t dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
	uint32_t raw_temp, raw_press, MSB, LSB, XLSB;
	float var1, var2, temp, pressure;
	uint8_t chip_id;

	UART_Init(); // Initialize UART communication

	// --- SPI pin setup ---
	// MOSI (PB3), SCK (PB5), SS (PB2), LED (PB0) as outputs
	DDRB |= (1 << DDB3) | (1 << DDB5) | (1 << DDB2) | (1 << DDB0);
	// MISO (PB4) as input
	DDRB &= ~(1 << DDB4);

	// --- SPI enable: Master mode, fosc/16, Mode 0 ---
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	SPCR &= ~((1 << CPOL) | (1 << CPHA));

	// --- Read chip ID (should be 0x58 for BMP280) ---
	PORTB &= ~(1 << PORTB2);   // SS LOW (select slave)
	SPDR = 0xD0 | 0x80;        // Read command for CHIP ID register
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;                // Dummy read
	SPDR = 0x00;               // Send dummy to receive data
	while (!(SPSR & (1 << SPIF)));
	chip_id = SPDR;            // Store chip ID
	PORTB |= (1 << PORTB2);    // SS HIGH (deselect slave)

	// --- Set CTRL_MEAS register (Normal mode, Temp+Press ON) ---
	PORTB &= ~(1 << PORTB2);
	SPDR = 0xF4 & 0x7F;        // Write address (MSB = 0)
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;
	SPDR = 0x27;               // 00100111b = normal mode, oversampling x1
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;
	PORTB |= (1 << PORTB2);
	_delay_ms(100);

	// --- Read calibration data (0x88 to 0xA1) ---
	uint8_t calib_data[24];
	PORTB &= ~(1 << PORTB2);
	SPDR = 0x88 | 0x80;        // Read starting from 0x88
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;
	for (uint8_t i = 0; i < 24; i++)
	{
		SPDR = 0x00;
		while (!(SPSR & (1 << SPIF)));
		calib_data[i] = SPDR;
	}
	PORTB |= (1 << PORTB2);

	// --- Extract calibration coefficients ---
	dig_T1 = (uint16_t)(calib_data[1] << 8 | calib_data[0]);
	dig_T2 = (int16_t)(calib_data[3] << 8 | calib_data[2]);
	dig_T3 = (int16_t)(calib_data[5] << 8 | calib_data[4]);
	dig_P1 = (uint16_t)(calib_data[7] << 8 | calib_data[6]);
	dig_P2 = (int16_t)(calib_data[9] << 8 | calib_data[8]);
	dig_P3 = (int16_t)(calib_data[11] << 8 | calib_data[10]);
	dig_P4 = (int16_t)(calib_data[13] << 8 | calib_data[12]);
	dig_P5 = (int16_t)(calib_data[15] << 8 | calib_data[14]);
	dig_P6 = (int16_t)(calib_data[17] << 8 | calib_data[16]);
	dig_P7 = (int16_t)(calib_data[19] << 8 | calib_data[18]);
	dig_P8 = (int16_t)(calib_data[21] << 8 | calib_data[20]);
	dig_P9 = (int16_t)(calib_data[23] << 8 | calib_data[22]);

	// --- Main loop ---
	while (1)
	{
		// ---------- Read Raw Temperature ----------
		PORTB &= ~(1 << PORTB2);
		SPDR = 0xFA | 0x80; // Temperature MSB register
		while (!(SPSR & (1 << SPIF)));
		(void)SPDR;
		SPDR = 0x00; while (!(SPSR & (1 << SPIF))); MSB = SPDR;
		SPDR = 0x00; while (!(SPSR & (1 << SPIF))); LSB = SPDR;
		SPDR = 0x00; while (!(SPSR & (1 << SPIF))); XLSB = SPDR;
		PORTB |= (1 << PORTB2);
		raw_temp = ((MSB << 12) | (LSB << 4) | (XLSB >> 4));

		// ---------- Read Raw Pressure ----------
		PORTB &= ~(1 << PORTB2);
		SPDR = 0xF7 | 0x80; // Pressure MSB register
		while (!(SPSR & (1 << SPIF)));
		(void)SPDR;
		SPDR = 0x00; while (!(SPSR & (1 << SPIF))); MSB = SPDR;
		SPDR = 0x00; while (!(SPSR & (1 << SPIF))); LSB = SPDR;
		SPDR = 0x00; while (!(SPSR & (1 << SPIF))); XLSB = SPDR;
		PORTB |= (1 << PORTB2);
		raw_press = ((MSB << 12) | (LSB << 4) | (XLSB >> 4));

		// ---------- Temperature compensation ----------
		var1 = (((float)raw_temp) / 16384.0 - ((float)dig_T1) / 1024.0) * ((float)dig_T2);
		var2 = ((((float)raw_temp) / 131072.0 - ((float)dig_T1) / 8192.0) *
		(((float)raw_temp) / 131072.0 - ((float)dig_T1) / 8192.0)) * ((float)dig_T3);
		float t_fine = var1 + var2;
		temp = t_fine / 5120.0; // in °C

		// ---------- Pressure compensation ----------
		float p;
		var1 = (t_fine / 2.0) - 64000.0;
		var2 = var1 * var1 * dig_P6 / 32768.0;
		var2 = var2 + var1 * dig_P5 * 2.0;
		var2 = (var2 / 4.0) + (dig_P4 * 65536.0);
		var1 = (dig_P3 * var1 * var1 / 524288.0 + dig_P2 * var1) / 524288.0;
		var1 = (1.0 + var1 / 32768.0) * dig_P1;

		if (var1 != 0)
		{
			p = 1048576.0 - raw_press;
			p = (p - var2 / 4096.0) * 6250.0 / var1;
			var1 = dig_P9 * p * p / 2147483648.0;
			var2 = p * dig_P8 / 32768.0;
			p = p + (var1 + var2 + dig_P7) / 16.0;
		}
		else p = 0;

		pressure = p / 100.0; // Convert to hPa

		// ---------- Display on UART ----------
		UART_TxString("TEMP = ");
		int t_int = (int)temp;
		int t_dec = (int)((temp - t_int) * 100);
		UART_TxNumber(t_int);
		UART_TxChar('.');
		UART_TxNumber(t_dec);
		UART_TxString(" C, ");

		UART_TxString("PRESSURE = ");
		int p_int = (int)pressure;
		int p_dec = (int)((pressure - p_int) * 100);
		UART_TxNumber(p_int);
		UART_TxChar('.');
		UART_TxNumber(p_dec);
		UART_TxString(" hPa\r\n");

		// Turn ON LED if chip is detected
		if (chip_id == 0x58)
		PORTB |= (1 << PORTB0);
		else
		PORTB &= ~(1 << PORTB0);

		_delay_ms(1000);
	}
}

