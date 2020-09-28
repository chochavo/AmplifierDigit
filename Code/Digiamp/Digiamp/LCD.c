#include "LCD.h"

void Init_LCD(void)
{
	lcd_D7_ddr |= (1<<lcd_D7_bit);                  // 4 data lines - output
	lcd_D6_ddr |= (1<<lcd_D6_bit);
	lcd_D5_ddr |= (1<<lcd_D5_bit);
	lcd_D4_ddr |= (1<<lcd_D4_bit);
	lcd_E_ddr  |= (1<<lcd_E_bit);                    // E line - output
	lcd_RS_ddr |= (1<<lcd_RS_bit);                  // RS line - output
}

void lcd_init_4d(void)
{
	// Power-up delay
	_delay_ms(100);                                 // initial 40 mSec delay

	// Set up the RS and E lines for the 'lcd_write_4' subroutine.
	lcd_RS_port &= ~(1<<lcd_RS_bit);                // select the Instruction Register (RS low)
	lcd_E_port &= ~(1<<lcd_E_bit);                  // make sure E is initially low

	// Reset the LCD controller
	lcd_write_4(lcd_FunctionReset);                 // first part of reset sequence
	_delay_ms(20);                                  // 4.1 mS delay (min)

	lcd_write_4(lcd_FunctionReset);                 // second part of reset sequence
	_delay_us(300);                                 // 100uS delay (min)

	lcd_write_4(lcd_FunctionReset);                 // third part of reset sequence
	_delay_us(300);                                 // this delay is omitted in the data sheet
	
	lcd_write_4(lcd_FunctionSet4bit);               // set 4-bit mode
	_delay_us(90);                                  // 40uS delay (min)

	// Function Set instruction
	lcd_write_instruction_4d(lcd_FunctionSet4bit);   // set mode, lines, and font
	_delay_us(90);                                  // 40uS delay (min)

	// Display On/Off Control instruction
	lcd_write_instruction_4d(lcd_DisplayOff);        // turn display OFF
	_delay_us(90);                                  // 40uS delay (min)

	// Clear Display instruction
	lcd_write_instruction_4d(lcd_Clear);             // clear display RAM
	_delay_ms(8);                                   // 1.64 mS delay (min)

	// ; Entry Mode Set instruction
	lcd_write_instruction_4d(lcd_EntryMode);         // set desired shift characteristics
	_delay_us(90);                                  // 40uS delay (min)

	// Display On/Off Control instruction
	lcd_write_instruction_4d(lcd_DisplayOn);         // turn the display ON
	_delay_us(90);                                  // 40uS delay (min)
}


void lcd_write_string_4d(uint8_t theString[])
{
	volatile int i = 0;                             // character counter*/
	while (theString[i] != 0)
	{
	lcd_write_character_4d(theString[i]);
	i++;
	_delay_us(90);                              // 40 uS delay (min)
//	_delay_us(40);
	}
	}

	void lcd_write_character_4d(uint8_t theData)
	{
	lcd_RS_port |= (1<<lcd_RS_bit);                 // select the Data Register (RS high)
	lcd_E_port &= ~(1<<lcd_E_bit);                  // make sure E is initially low
	lcd_write_4(theData);                           // write the upper 4-bits of the data
	lcd_write_4(theData << 4);                      // write the lower 4-bits of the data
	}

	void lcd_write_instruction_4d(uint8_t theInstruction)
	{
	lcd_RS_port &= ~(1<<lcd_RS_bit);                // select the Instruction Register (RS low)
	lcd_E_port &= ~(1<<lcd_E_bit);                  // make sure E is initially low
	lcd_write_4(theInstruction);                    // write the upper 4-bits of the data
	lcd_write_4(theInstruction << 4);               // write the lower 4-bits of the data
	}

	void lcd_write_4(uint8_t theByte)
	{
	lcd_D7_port &= ~(1<<lcd_D7_bit);                        // assume that data is '0'
	if (theByte & 1<<7) lcd_D7_port |= (1<<lcd_D7_bit);     // make data = '1' if necessary

	lcd_D6_port &= ~(1<<lcd_D6_bit);                        // repeat for each data bit
	if (theByte & 1<<6) lcd_D6_port |= (1<<lcd_D6_bit);

	lcd_D5_port &= ~(1<<lcd_D5_bit);
	if (theByte & 1<<5) lcd_D5_port |= (1<<lcd_D5_bit);

	lcd_D4_port &= ~(1<<lcd_D4_bit);
	if (theByte & 1<<4) lcd_D4_port |= (1<<lcd_D4_bit);

	// write the data
	// 'Address set-up time' (40 nS)
	lcd_E_port |= (1<<lcd_E_bit);                   // Enable pin high
	_delay_us(70);                                   // implement 'Data set-up time' (80 nS) and 'Enable pulse width' (230 nS)
	//_delay_us(20);
	lcd_E_port &= ~(1<<lcd_E_bit);                  // Enable pin low
	//delay_us(20);
	_delay_us(70);                                   // implement 'Data hold time' (10 nS) and 'Enable cycle time' (500 nS)
	}