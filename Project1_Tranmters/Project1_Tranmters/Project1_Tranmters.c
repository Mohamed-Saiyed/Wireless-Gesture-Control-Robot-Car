/*
 * Project1_Tranmters.c
 *
 * Created: 4/18/2020 6:29:55 AM
 *  Author: Mohamed_sayed
 */ 

#define F_CPU 8000000UL
#include <MyLib/esp_Cleint.h>
#include <MyLib/UART.h>
#include <MyLib/I2C.h>
#include <MyLib/MPU6050.h>
#include <avr/io.h>
#include <MyLib/LCD.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
volatile  int8_t AX ,Forward , RIGHT;
volatile  int8_t AY , Backword , LEFT;
int main(void)
{
	MPU_Init(2,4);
	UART_init(19200);
	UCSRB |=(1<<RXCIE);
	sei();
	InitilizeLcd();
	WIFI_Config();

	
	while(1)
	{
		 MPU_X_Y_Read();
		AX = Ax / 1000 ;
		AY = Ay / 1000 ; 
	   Send_Data(AX+20);
	   Send_Data(AY);
		
	}
}