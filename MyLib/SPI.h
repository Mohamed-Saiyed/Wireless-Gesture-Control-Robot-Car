#ifndef SPI
#define SPI

void SPI_MASTER_INIT()
{
	DDRB |=(1<<PB5);
	DDRB |=(1<<PB4);
	DDRB &=~(1<<PB6);
	DDRB |=(1<<PB7);
	SPCR |=(1<<SPE) | (1<<MSTR);
}

void SPI_SLAVE_INIT()
{
	DDRB &=~(1<<PB5);
	DDRB &=~(1<<PB4);
	DDRB |=(1<<PB6);
	DDRB &=~(1<<PB7);
	SPCR =(1<<SPE) | (1<<SPIE);
}
void SPI_SEND(uint8_t data)
{
	SPDR = data;
	while(!(SPSR &(1<<SPIF)));
}
uint8_t SPI_RECEIVE()
{
	while(!(SPSR &(1<<SPIF)));
	return SPDR;
}
void SPI_SEND_STRING(char *data)
{
	uint8_t i = 0 ;
	while(data[i] != 0 )
	{
		SPI_SEND(data[i]);
		i++;
	}
}











#endif