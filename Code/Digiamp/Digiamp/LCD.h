#ifndef LCD_H_
#define LCD_H_
#include "main.h"

#define lcd_D7_port     PORTC                   // lcd D7 connection
#define lcd_D6_port     PORTC                   // lcd D6 connection
#define lcd_D5_port     PORTC                   // lcd D5 connection
#define lcd_D4_port     PORTC                   // lcd D4 connection
#define lcd_E_port      PORTC                   // lcd Enable pin
#define lcd_RS_port     PORTC                   // lcd Register Select pin

#define lcd_D7_bit      PORTC5
#define lcd_D6_bit      PORTC4
#define lcd_D5_bit      PORTC3
#define lcd_D4_bit      PORTC2
#define lcd_E_bit       PORTC1
#define lcd_RS_bit      PORTC0

#define lcd_D7_ddr      DDRC
#define lcd_D6_ddr      DDRC
#define lcd_D5_ddr      DDRC
#define lcd_D4_ddr      DDRC
#define lcd_E_ddr       DDRC
#define lcd_RS_ddr      DDRC

// LCD module information
#define lcd_LineOne     0x00                    // start of line 1
#define lcd_LineTwo     0x40                    // start of line 2

// LCD instructions
#define lcd_Clear           0b00000001          // replace all characters with ASCII 'space'
#define lcd_Home            0b00000010          // return cursor to first position on first line
#define lcd_EntryMode       0b00000110          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0b00001000          // turn display off
#define lcd_DisplayOn       0b00001100          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0b00110000          // reset the LCD
#define lcd_FunctionSet4bit 0b00101000          // 4-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0b10000000          // set cursor position

void Init_LCD();
void lcd_write_4(uint8_t);
void lcd_write_instruction_4d(uint8_t);
void lcd_write_character_4d(uint8_t);
void lcd_write_string_4d(uint8_t *);
void lcd_init_4d(void);

#endif