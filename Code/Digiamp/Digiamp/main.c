#include <avr/io.h>
#include "main.h"
#include "SPI.h"
#include "LCD.h"

volatile char AsciiNumber[] = {0, 0, 0};
volatile bool encoder_A = false;
volatile bool encoder_B = false;
volatile bool encoder_A_prev = false;
uint8_t current_state = MAIN_MENU;
uint8_t VolValue = 0;
uint8_t GainValue = 0;
uint8_t DelayTime = 0;
uint8_t DelayDepth = 0;
volatile bool get_value_flag = false;

void print_delay_time_lcd(void)
{
	IntToAscii((DelayTime * 100) / 255);
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineOne));
	lcd_write_string_4d("< Delay Time   >");
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo));
	lcd_write_string_4d("<Value:   [%]  >");
	if (((DelayTime * 100) / 255) >= 0 && ((DelayTime * 100) / 255) < 10) {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 9));
		lcd_write_character_4d(AsciiNumber[2]);
	}
	else if ( ((DelayTime * 100) / 255) >= 10 && ((DelayTime * 100) / 255) < 100 ) {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 8));
		lcd_write_character_4d(AsciiNumber[1]);
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 9));
		lcd_write_character_4d(AsciiNumber[2]);
	}
	else {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 7));
		lcd_write_string_4d("100");
	}
}

void print_gain_lcd(void)
{
	IntToAscii((GainValue * 100) / 255);
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineOne));
	lcd_write_string_4d("< Gain Select  >");
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo));
	lcd_write_string_4d("<Value:   [%]  >");
	if (((GainValue * 100) / 255) >= 0 && ((GainValue * 100) / 255) < 10) {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 9));
		lcd_write_character_4d(AsciiNumber[2]);
	}
	else if ( ((GainValue * 100) / 255) >= 10 && ((GainValue * 100) / 255) < 100 ) {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 8));
		lcd_write_character_4d(AsciiNumber[1]);
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 9));
		lcd_write_character_4d(AsciiNumber[2]);
	}
	else {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 7));
		lcd_write_string_4d("100");
	}
}

void print_main_lcd(void)
{
	IntToAscii(((VolValue * 100) / 255));
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineOne));
	lcd_write_string_4d("<Amplifice V1.0>");
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo));
	lcd_write_string_4d("<Volume:   [%] >");
	if (((VolValue * 100) / 255) >= 0 && ((VolValue * 100) / 255) < 10) {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 10));
		lcd_write_character_4d(AsciiNumber[2]);
	}
	else if ( ((VolValue * 100) / 255) >= 10 && ((VolValue * 100) / 255) < 100 ) {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 9));
		lcd_write_character_4d(AsciiNumber[1]);
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 10));
		lcd_write_character_4d(AsciiNumber[2]);
	}
	else {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 8));
		lcd_write_string_4d("100");
	}
}

void print_delay_depth_lcd(void)
{
	IntToAscii((DelayDepth * 100) / 255);
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineOne));
	lcd_write_string_4d("< Delay Depth  >");
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo));
	lcd_write_string_4d("<Value:   [%]  >");
	if (((DelayDepth * 100) / 255) >= 0 && ((DelayDepth * 100) / 255) < 10) {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 9));
		lcd_write_character_4d(AsciiNumber[2]);
	}
	else if ( ((DelayDepth * 100) / 255) >= 10 && ((DelayDepth * 100) / 255) < 100 ) {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 8));
		lcd_write_character_4d(AsciiNumber[1]);
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 9));
		lcd_write_character_4d(AsciiNumber[2]);
	}
	else {
		lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo + 7));
		lcd_write_string_4d("100");
	}
}

void EncoderPosChanged(void)
{
	get_value_flag = false;
	switch(current_state)
	{
		case MAIN_MENU:
			switch(GetEncoderPos())
			{
				case DOWN: 
					if (VolValue <= 1) VolValue = 0;
					else VolValue -= 3;
					break;
				case UP:
					if (VolValue >= 250) VolValue = 255;
					else VolValue += 3;
					break;
				default: break;
			}
			set_volume(VolValue);
			break;
			
		case GAIN_MENU:
			switch(GetEncoderPos())
			{
				case DOWN:
					if (GainValue <= 1) GainValue = 0;
					else GainValue--;
					break;
				case UP:
					if (GainValue >= 254) GainValue = 255;
					else GainValue++;
					break;
				default: break;
			}
			set_gain(GainValue);
			break;
		
		case DELAY_DEPTH:
			switch(GetEncoderPos())
			{
				case DOWN:
					if (DelayDepth <= 1) DelayDepth = 0;
					else DelayDepth -= 3;
					break;
				case UP:
					if (DelayDepth >= 254) DelayDepth = 255;
					else DelayDepth += 3;
					break;
				default: break;
			}
			set_depth(DelayDepth);
			break;
				
		case DELAY_TIME:
			switch(GetEncoderPos())
			{
				case DOWN:
					if (DelayTime <= 1) DelayTime = 0;
					else DelayTime -= 3;
					break;
				case UP:
					if (DelayTime >= 254) DelayTime = 255;
					else DelayTime += 3;
					break;
				default: break;
			}
			set_time(DelayTime);
			break;
		default: break;
	}

}

void set_volume(uint8_t volume_in)	 { SPI_write_16bit(VOLUME_POT, volume_in, SPI_PREAMP_CS); }
void set_gain(uint8_t gain_in)		 { SPI_write_16bit(GAIN_POT, gain_in, SPI_PREAMP_CS); }
void set_depth(uint8_t depth_in)	 { SPI_write_16bit(DELAY_DEPTH_POT, depth_in, SPI_DELAY_CS); }
void set_time(uint8_t time_in)		 { SPI_write_16bit(DELAY_TIME_POT, time_in, SPI_DELAY_CS); }

void Greetings(void)
{
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineOne));
	lcd_write_string_4d("Greetings :)    ");
	lcd_write_instruction_4d(lcd_SetCursor | (lcd_LineTwo));
	lcd_write_string_4d("Amplifice is ON ");
}

void InitInterrupts(void)
{
	EICRA |= (1 << ISC10) | (1 << ISC00); // ANY LOGICAL CHANGE.
	EIMSK |= (1 << INT0) | (1 << INT1);
	sei();
}

void InitDevice(void)
{
	InitInterrupts();
	InitSwitches();
    Init_LCD();
	lcd_init_4d();
	Init_SPI();
	Greetings();
	set_depth(0);
	set_gain(0);
	set_time(0);
	set_volume(0);
}


void InitSwitches(void) { DDRD &= ~(1 << SW0) & ~(1 << ENC_A) & ~(1 << ENC_B); }

volatile int GetEncoderPos()
{
	volatile int RetVal = 0;
	encoder_A = ((PIND & (1 << ENC_A)) == (1 << ENC_A));
	encoder_B = ((PIND & (1 << ENC_B)) == (1 << ENC_B));
	_delay_us(150);
	if((!encoder_A) && (encoder_A_prev)){
		if(encoder_B) RetVal = 1;
		else RetVal = -1;
	}
	else RetVal = 0;
	encoder_A_prev = encoder_A;     // Store value of A for next time
	return RetVal;
}

ISR(INT0_vect) { EncoderPosChanged(); }
ISR(INT1_vect) { EncoderPosChanged(); }

void IntToAscii(uint8_t value_in)
{
	for (uint8_t i = 0; i < 3; i++)
	{
		AsciiNumber[2 - i] = (value_in % 10) + 0x30;
		value_in /= 10;
	}	
}


void menu_states(void)
{
	bool OutConfirm = false;
	while (!OutConfirm)
	{
		switch (current_state)
		{
			case GAIN_MENU:
				if (!get_value_flag) {
					print_gain_lcd();
					get_value_flag = true;
				}
				if (!(PIND&(1 << SW0)))
				{
					get_value_flag = false;
					while(!(PIND&(1 << SW0)));
					current_state = DELAY_DEPTH;
				}
				break;
			case DELAY_DEPTH:
				if (!get_value_flag) {
					print_delay_depth_lcd();
					get_value_flag = true;
				}
				if (!(PIND&(1 << SW0)))
					{
					get_value_flag = false;
					while(!(PIND&(1 << SW0)));
					current_state = DELAY_TIME;
				}
				break;
			case DELAY_TIME:
				if (!get_value_flag) {
					print_delay_time_lcd();
					get_value_flag = true;
				}				
				if (!(PIND&(1 << SW0)))
				{
					while(!(PIND&(1 << SW0)));
					current_state = MAIN_MENU;
					get_value_flag = false;
					OutConfirm = true;
				}
			break;
			default: break;
		}
	}
}

int main(void)
{
	InitDevice();
    while (1) 
    {
		if (!get_value_flag) {
			print_main_lcd();
			get_value_flag = true;
		}
		if (!(PIND&(1 << SW0)))
		{
			get_value_flag = false;
			while(!(PIND&(1 << SW0)));
			current_state = GAIN_MENU;
			menu_states();
		}
    }
}

