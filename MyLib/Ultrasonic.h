#ifndef Ultrasonic

#define Ultrasonic
#define PORT      PORTC
#define DDR_PORT  DDRC
#define PIN       PINC
#define ECHO       1
#define TRIGGER    0
#define TRIGGER_ON  (PORT |=(1<<TRIGGER))
#define TRIGGER_OFF (PORT &=~(1<<TRIGGER))
#include <avr/io.h>
#include <util/delay.h>
void Ultrasonic_Init()
{
  DDR_PORT |=(1 << TRIGGER);
  DDR_PORT &=~(1 << ECHO);
}
uint32_t Ultrasonic_Read()
{
   uint32_t Distance = 0 ;
   TRIGGER_OFF;
   _delay_us(10);
   TRIGGER_ON;
   _delay_us(10);
   TRIGGER_OFF;
   if (!(PIN &(1<<ECHO)))
   {
	   while(!(PIN &(1<<ECHO)));
	   Timer_Start();
	   while((PIN &(1<<ECHO)));
	   Timer_Stop();
   } 
   
   Distance = TCNT1 / 58.82;
   return Distance ;  

}
void Timer_Start()
{
	TCCR1B |=(1<<CS11);
	TCCR1A &=~(1<<WGM11)  | (1<<WGM10);
	TCCR1B &=~(1<<WGM12)  | (1<<WGM13);
	TCCR1A |=(1<<FOC1A) | (1<<FOC1B);
	TCNT1 = 0;
}
void Timer_Stop()
{
	TCCR1A = 0x00;
	TCCR1B = 0x00;
}

#endif