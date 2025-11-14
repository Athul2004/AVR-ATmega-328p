/*
 * lcd.c
 *
 * Created: 11-10-2025 20:53:36
 *  Author: KICHU
 */ 
#define F_CPU 16000000UL
#include "lcd.h"
#include <util/delay.h>
#include <stdint.h>

//  lets start with that enable pulse
static void lcd_enable_pulse(void)
{
	LCD_EN_PORT |=  (1 << LCD_EN_PIN);               // enable pin =1
	_delay_us(1);                                                           // these delay values come from datasheet
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);                 // enable pin =0
	_delay_us(50); 					// allow LCD to latch
}

// this function sends a nibble to the data pins (b3..b0 -> D7..D4)
static void lcd_send_nibble(uint8_t nib)
{
	// Clear PD2..PD5 by our mapping
	LCD_D_PORT &= ~((1<<LCD_D7_PIN)|(1<<LCD_D6_PIN)|(1<<LCD_D5_PIN)|(1<<LCD_D4_PIN));  // Making all data pins 0 initially

	// now set the pins according to the data/command
	if (nib & 0x8) LCD_D_PORT |= (1<<LCD_D7_PIN);
	if (nib & 0x4) LCD_D_PORT |= (1<<LCD_D6_PIN);
	if (nib & 0x2) LCD_D_PORT |= (1<<LCD_D5_PIN);
	if (nib & 0x1) LCD_D_PORT |= (1<<LCD_D4_PIN);
	lcd_enable_pulse();
}

// this function allows us to send a byte
static void lcd_send_byte(uint8_t value, uint8_t rs)  	  // here we receive data and rs value
{
	if (rs==1)
	{
		LCD_RS_PORT |=  (1<<LCD_RS_PIN);  		 // IT’S A Data. SO RS pin =1
	}
	else
	{
		LCD_RS_PORT &= ~(1<<LCD_RS_PIN); 			 // it’s a Command. So RS pin0
	}
	lcd_send_nibble(value >> 4);                     // sending upper nibble
	lcd_send_nibble(value & 0x0F);                // sending lower nibble
}

// this function sends commands (instructions)
void lcd_cmd(uint8_t c)
{
	lcd_send_byte(c, 0);
	// Clear (0x01) and Return Home (0x02) need longer delays in write-only mode
	if (c == 0x01 || c == 0x02)
	_delay_ms(2);
}

// This function allows us to send data
void lcd_data(uint8_t d)
{
	lcd_send_byte(d, 1);
}

// this function allows us to set the cursor

void lcd_set_cursor(uint8_t row, uint8_t col)		// receives row and column value 2X16 LCD
{
	uint8_t addr = (row ? 0x40 : 0x00) + (col & 0x0F);	// this is a ternary operator.
	lcd_cmd(0x80 | addr);                                                       // send (80 + addr) as a command.
}


//This function allows us to print a string
void lcd_print(const char *s)
{
	while (*s)
	{
		lcd_data((uint8_t)*s++);
	}

}
// this function allows us to clear the lcd
void lcd_clear(void)
{
	lcd_cmd(0x01);
}

// this function allows us to return the cursor to home
void lcd_home(void)
{
	lcd_cmd(0x02);
}

// this function initialises the lcd. (initialisation sequence from datasheet)

void lcd_init(void)
{
	// Make control and data pins outputs
	LCD_RS_DDR |= (1<<LCD_RS_PIN);
	LCD_EN_DDR |= (1<<LCD_EN_PIN);
	LCD_D_DDR  |= (1<<LCD_D7_PIN)|(1<<LCD_D6_PIN)|(1<<LCD_D5_PIN)|(1<<LCD_D4_PIN);

	_delay_ms(20);               // power-up wait
	LCD_RS_PORT &= ~(1<<LCD_RS_PIN); 				// RS=0

	//  8-bit wake-up sequence (sent as high nibbles). why nibbles?
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);   		 // make EN =0 .
	lcd_send_nibble(0x03);
	_delay_ms(5);
	lcd_send_nibble(0x03);
	_delay_us(150);
	lcd_send_nibble(0x03);
	_delay_us(150);

	//Switch to 4-bit
	lcd_send_nibble(0x02);
	_delay_us(150);

	// note that from here onwards its cmd !

	//Function set: 4-bit, 2 lines, 5x8 font
	lcd_cmd(0x28);

	//Display off

	lcd_cmd(0x08);
	//Clear
	lcd_cmd(0x01);

	//Entry mode: increment, no shift
	lcd_cmd(0x06);


	// Display on, cursor off, blink off
	lcd_cmd(0x0C);
}

// function to print integers. (we use recursion)
void lcd_print_uint16(uint16_t v)
{
	if (v >= 10)
	{
		lcd_print_uint16(v / 10);  				 // print higher digits first
	}
	lcd_data('0' + (v % 10));       				// then print the last digit
}
