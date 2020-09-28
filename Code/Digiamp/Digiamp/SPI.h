#ifndef SPI_H_
#define SPI_H_
#include "main.h"
#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define SPI_DELAY_CS  PORTB2
#define SPI_PREAMP_CS	  PORTB1
#define SPI_read_command	  0b00001100
#define SPI_write_command	  0b00000000
#define SPI_increment_command 0b00000100
#define SPI_decrement_command 0b00001000

#define GAIN_POT 0
#define VOLUME_POT 0b00010000

#define DELAY_DEPTH_POT 0b00010001
#define DELAY_TIME_POT 0b00010010

void SPI_write_16bit(uint8_t address_in, uint8_t data_in, uint8_t CE_type);
void Init_SPI(void);



#endif /* SPI_H_ */