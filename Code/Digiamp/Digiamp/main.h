#ifndef MAIN_H_
#define MAIN_H_
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SW0 PORTD0
#define ENC_A PORTD2
#define ENC_B PORTD3

#define UP 1
#define DOWN -1

enum menu_states { MAIN_MENU = 2, GAIN_MENU, DELAY_DEPTH, DELAY_TIME };

void EncoderPosChanged(void);
void set_volume(uint8_t volume_in);
void set_gain(uint8_t gain_in);
void set_depth(uint8_t depth_in);
void set_time(uint8_t time_in);
void Greetings(void);
void InitInterrupts(void);
void InitDevice(void);
void InitSwitches(void);
volatile int GetEncoderPos();
void IntToAscii(uint8_t value_in);
void menu_states(void);

#endif /* MAIN_H_ */