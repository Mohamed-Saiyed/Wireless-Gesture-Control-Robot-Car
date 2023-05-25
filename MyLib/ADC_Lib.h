#ifndef ADC_Lib
#define ADC_Lib
void ADC_Init()
{
	ADCSRA |=(1<<ADEN) |(1<<ADPS2) | (1<<ADPS1);
	ADMUX |= (1<<REFS0);
}
uint16_t ADC_Read(uint8_t channel)
{
	channel &=0x07;
	ADMUX = (ADMUX & 0xE0) | (channel);
	//ADMUX |= 0xC0 |(channel & 0x07);
	ADCSRA |=(1<<ADSC);
	while(!(ADCSRA &(1<<ADIF)));
	ADCSRA |=(1<<ADIF);
	return ADC ;
}
#endif