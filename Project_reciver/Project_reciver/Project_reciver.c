/*
 * Project_reciver.c
 *
 * Created: 4/18/2020 7:30:14 AM
 *  Author: Mohamed_sayed
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <MyLib/UART.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <MyLib/esp_Server.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <MyLib/Ultrasonic.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
void PWM_init();
char recived_data[10];
void get_data_Recieved();
volatile int data , AY , AX;
int main(void)
{
	UART_init(19200);
	UCSRB |=(1<<RXCIE);
	sei();

	PWM_init();
	WIFI_Config();
    while(1)
    {
	   get_data_Recieved();  
	
	   if (AY >= 3)
	   {
		   OCR1B = 8000;
		   OCR1A = 8000;
		   PORTC &=~(1<<PC0);
		   PORTA &=~(1<<PA0);
		   PORTC =(1<<PC1);
		   PORTA =(1<<PA1);
		   
	   }
	   else if (AY <= -3 )
	   {
		   OCR1B = 8000;
		   OCR1A = 8000;
		   PORTC =(1<<PC0);
		   PORTA =(1<<PA0);
		    PORTC &=~(1<<PC1);
		    PORTA &=~(1<<PA1);
			
	   }
	    
		else if(AX > 23 )
		{
			OCR1B = 5000;
			OCR1A = 5000;
			PORTC &=~(1<<PC0);
			PORTC &=~(1<<PC1);
			PORTA &=~(1<<PA1);
			PORTA =(1<<PA0);
	
		}
		else if(AX < 17)
		{
			OCR1B = 5000;
			OCR1A = 5000;
			PORTA &=~(1<<PA0);
			PORTA &=~(1<<PA1);
			PORTC &=~(1<<PC1);
			PORTC =(1<<PC0);
			
		}	
		else
		{
			PORTC =0x00;
			PORTA =0x00;
		}   
    }
}

void get_data_Recieved()
{
	if (find_string(rx_buffer,"+IPD")==1)
	{
	
		Get_data_Recieved(recived_data);
		(data = Get_data_Recieved_value(recived_data));
	    if(data <= 8 && data >= -8)
		{
			AY = data ; 
		}
		else if(data <= 28 && data >= 13)
		{
			AX = data ;
		}
		reset_buffer();
	}
}

void PWM_init()
{
		
		DDRD |=(1<<PD5);
		TCCR1A |=(1<<WGM11) | (1<<COM1A1) | (1<<COM1B1);
		TCCR1B |=(1<<WGM12) |(1<<WGM13) | (1<<CS11);
		DDRD |=(1<<PD4);
		ICR1 = 19999;
		
}