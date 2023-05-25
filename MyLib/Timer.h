#ifndef Timer
#define Timer
#define PWM    1
#define NORMAL 2
#define CTC    3
#include <avr/interrupt.h>
void Timer1_init(char prescaler)
{
	if (prescaler == 1)
	{
		TCCR1B |=(1<<CS10);
	}
	else if (prescaler == 8)
	{
		TCCR1B |=(1<<CS11);
	}
	else if (prescaler == 64)
	{
		TCCR1B |=(1<<CS10) | (1<<CS11);
	}
	else if (prescaler == 256)
	{
		TCCR1B |=(1<<CS12);
	}
	else if (prescaler == 1024)
	{
		TCCR1B |=(1<<CS10) | (1<<CS12);
	}
	
	
}
void TIMER1_PWM(char com  , uint16_t freq , uint8_t prescaler)
{
	TCCR1A |=(1<<WGM11);
	TCCR1B |=(1<<WGM12) |(1<<WGM13);
	int TOP = 	(F_CPU/(freq*prescaler)) - 1;
	if (com == 'A')
	{
		DDRD |=(1<<PD5);
		TCCR1A |=(1<<COM1A1);
	}
	else if (com == 'B')
	{
		DDRD |=(1<<PD4);
		TCCR1A |=(1<<COM1B1);
	}
	ICR1 = TOP ;		

}
void Duty_cycle(char com , float duty_cycle )
{
  	if (com == 'A')
  	{
	  	 (OCR1A = ICR1 * duty_cycle);
  	}
  	else if (com == 'B')
  	{
	  	(OCR1B = ICR1 * duty_cycle);
  	}
}
void TIMER1_NORMAL()
{
	TCCR1A &=~(1<<WGM11)  | (1<<WGM10);
	TCCR1B &=~(1<<WGM12)  | (1<<WGM13);
	TCCR1A |=(1<<FOC1A) | (1<<FOC1B);
	TCNT1 = 0;
	TIMSK  |=(1<<TOIE1);
	sei();
	
}
void TIMER1_CTC(char com , uint16_t Top)
{	
  TCCR1A |=(1<<FOC1A) | (1<<FOC1B);
  TCCR1B |=(1<<WGM12);
  TIMSK  |=(1<<OCIE1A);
  sei();
  TCNT1 = 0 ;
  OCR1A = Top;
}

void TIMER1_CLK_GENRATION(char com , int freq , uint8_t prescaler)
{
	TCCR1A |=(1<<FOC1A) | (1<<FOC1B);
	TCCR1B |=(1<<WGM12);
	uint16_t TOP = 	(F_CPU/(freq * prescaler)) - 1;
	if (com == 'A')
	{
		DDRD |=(1<<PD5);
		TCCR1A |=(1<<COM1A0);
	}
	else if (com == 'B')
	{
		 DDRD |=(1<<PD4);
		TCCR1A |=(1<<COM1B0);
	}
	TCNT1 = 0 ;
	OCR1A = TOP;
}
void Timer0_init(char prescaler)
{
	if (prescaler == 1)
	{
		TCCR0 |=(1<<CS00);
	}
	else if (prescaler == 8)
	{
		TCCR0 |=(1<<CS01);
	}
	else if (prescaler == 64)
	{
		TCCR0 |=(1<<CS00) | (1<<CS01);
	}
	else if (prescaler == 256)
	{
		TCCR0 |=(1<<CS02);
	}
	else if (prescaler == 1024)
	{
		TCCR0 |=(1<<CS00) | (1<<CS02);
	}
	
	
}
void TIMER0_NORMAL()
{
	TCCR0 &=~(1<<WGM01)  | (1<<WGM00);
	TCCR0 |=(1<<FOC0);
	TCNT0 = 0;
	TIMSK  |=(1<<TOIE0);
	sei();
	
}
void TIMER0_CTC(uint16_t Top)
{
	TCCR0 |=(1<<FOC0) | (1<<WGM01);
	TIMSK  |=(1<<OCIE0);
	sei();
	TCNT0 = 0 ;
	OCR0 = Top;
}

#endif