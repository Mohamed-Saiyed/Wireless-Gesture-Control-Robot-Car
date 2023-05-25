#ifndef LCD
	#define LCD
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdlib.h>
	

	#define LCD_DPORT         PORTB
	#define DataDir_DPORT     DDRB
	#define LCDControl        PORTD
	#define DataDir_LCDControl DDRD
	#define Enable     4
	#define ReadWrite  5
	#define RS         6
	/*void InitilizeLcd(void);
	void Check_IF_LCD_isBusy(void);
	void Send_A_Pulse (void);
	void Send_A_Command(unsigned char command);
	void Send_A_Character(unsigned char character);
	void Send_A_String(char *string);
	void Send_A_String_WithLocation(uint8_t x ,uint8_t y , char *string);
	void Gotoloction(uint8_t x ,uint8_t y);
	void Send_An_Int_WithLocation(uint8_t x ,uint8_t y , int DisplyNum , char NumOfDigits);
*/
	void Check_IF_LCD_isBusy()
	{
		DataDir_DPORT = 0; // DDRB=0x00
		LCDControl |=(1<<ReadWrite);
		LCDControl  &=~(1<<RS);

		while (LCD_DPORT >= (0x80)); //PORTB = 0b10000000 BF = 1;
	
		
		
	
		Send_A_Pulse();
				
		DataDir_DPORT = 0xFF; //0xFF means DDRD = 0b11111111
	}

	void Send_A_Pulse()
	{
		LCDControl  |=(1<<Enable);
		asm volatile ("nop");
		asm volatile ("nop");
		LCDControl &=~(1<<Enable);
	}

	void Send_A_Command(unsigned char command)
	{
		
		_delay_us(50);
		Check_IF_LCD_isBusy();
		LCD_DPORT = command;
		LCDControl &=~(1<<ReadWrite);
		LCDControl &=~(1<<RS);
		Send_A_Pulse();
		LCD_DPORT = 0;
	}

	void Send_A_Character(unsigned char character)
	{
		_delay_us(50);
		Check_IF_LCD_isBusy();
		LCD_DPORT  = character;
		LCDControl  &= ~(1<<ReadWrite);
		LCDControl  |=(1<<RS);
		Send_A_Pulse();
		LCD_DPORT = 0;
	
	}
	void Send_A_String(char * string)
	{
		while(*string > 0)
		{
			Send_A_Character(*string++);
		}
	
	}
	void Send_A_String_WithLocation(uint8_t x ,uint8_t y , char *string)
	{
		Gotoloction(x , y);
		Send_A_String(string);
	}
	int coloms [4]={0,64,20,84};
	void Gotoloction(uint8_t x ,uint8_t y)
	{
		Send_A_Command(0x80 + coloms[y-1] + (x-1));
	}
	void InitilizeLcd()
	{
		DataDir_LCDControl |=(1<<Enable);
		DataDir_LCDControl |=(1<<ReadWrite) ;
		DataDir_LCDControl |=(1<<RS);
		_delay_ms(20);

		Send_A_Command(0x01); //Clear Screen 0x01 = 00000001
		_delay_ms(2);
		Send_A_Command(0x38); //8-bit mode
		_delay_us(50);
		Send_A_Command(0b00001110);
		_delay_us(50);
	}		
	void Send_An_Int_WithLocation(uint8_t x ,uint8_t y , int DisplyNum , char NumOfDigits)
	{
		char CONVERTEDINT [NumOfDigits];
		itoa(DisplyNum , CONVERTEDINT , 10);
		//Gotoloction(x,y);
		for(uint8_t i = 0; i < NumOfDigits ; i++) Send_A_String(" ");
		Send_A_String_WithLocation(x , y , CONVERTEDINT);
	}
	void LCD_Clear_Screen()
	{
		Send_A_Command(0x01);
		_delay_ms(2);
	}
#endif