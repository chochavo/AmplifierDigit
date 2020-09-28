#include "SPI.h"

void SPI_write_16bit(uint8_t address_in, uint8_t data_in, uint8_t CE_type)
{
	SPI_PORT &=~(1 << CE_type);
	_delay_us(2);
	SPDR = address_in;
	while(!(SPSR & (1<<SPIF)));
	SPDR = data_in;
	while(!(SPSR & (1<<SPIF)));
	SPI_PORT |= (1 << CE_type);
}

void Init_SPI(void)
{
	SPI_DDR = (1<<PORTB3)|(1<<PORTB5)|(1<<PORTB2)|(1 << PORTB1);
	SPI_PORT |= (1 << SPI_PREAMP_CS) | (1 << SPI_DELAY_CS);
	//SPI_PORT &= ~(1<<SPI_PREAMP_CS) & ~(1 << SPI_DELAY_CS);
	SPCR = (1<<SPE)|(1<<MSTR);
	SPSR = (1<<SPI2X);
	_delay_ms(1);
	SPI_write_16bit(0b01000000, 0xFF, SPI_PREAMP_CS);
}