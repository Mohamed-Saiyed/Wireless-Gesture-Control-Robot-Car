#ifndef esp_Server
#define esp_Server

#define F_CPU 8000000UL
#include <avr/io.h>
#include <MyLib/UART.h>
#include <MyLib/LCD.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

//AT COMMANDS
const char AT_RST[]="AT+RST";
const char AT_CWMODE[]="AT+CWMODE=";
const char AT_CWJAP[]="AT+CWJAP=";
const char AT_CWLAP[]="AT+CWLAP";
const char AT_CWQAP[]="AT+CWQAP";
const char AT_CWSAP[]="AT+CWSAP=";
const char AT_CIPSTATUS[]="AT+CIPSTATUS";
const char AT_CIPSTART[]="AT+CIPSTART=";
const char AT_CIPCLOSE[]="AT+CIPCLOSE=";
const char AT_CIPMUX[]="AT+CIPMUX=";
const char AT_CIPSERVER[]="AT+CIPSERVER=";
const char AT_CIFSR[]="AT+CIFSR";


volatile char check;
//Response Checking
const  char OK = 1;
const  char   ready = 2;
const  char  no_change = 3;
const  char  send_ready = 4;

//Storing Server Information
char APIP[15];
char APMAC[20];
char STAIP[15];
char STAMAC[20];
//Wifi Network Information
char SSID[]="TE-Data 2.4GHz";
char PASSWORD[]="Dellinspiron18";
char PORT[]="80";
char Connection_ID[2];
char Connection_ID1[2];
//USART ISR storing variables
volatile  uint16_t Counter = 0; //data counter
char  rx_buffer[500]; //storing response
volatile char temp;//temporary storing variable
char ReceIved_Data[50];


char find_string(char *string , char *string_nedded)
{
	int match = 0;
	int lenOfString = strlen(string);
	int lenghtOFNeddedString=strlen(string_nedded);
	if(lenghtOFNeddedString>lenOfString)return 0 ;
	for(int i = 0 ;i <lenOfString; i++)
	{
		if(string[i] == string_nedded[match])
		{
			match++;

			if(lenghtOFNeddedString==match) return 1;

		}
		else match = 0;
	}
	

}
char Response_success()
{
	if((find_string(rx_buffer,"OK"))==1) return  OK;
	else if(find_string(rx_buffer,"no change") == 1) return no_change;
	else if(find_string(rx_buffer,"ready") == 1)return ready;
	else if(find_string(rx_buffer,">") == 1) return send_ready;
	else return 0;

}



void Get_String(char *source,char *StartFrom,char Delete ,char *EndString ,char add,char *SaveTOanArray)
{
	char lenght = 0;
	char *ptr;
	char *ptr1;


	ptr=strstr(source,StartFrom)+Delete;
	ptr1=strstr(ptr,EndString)+add;

	lenght = ptr1 - ptr ;
	strncpy(SaveTOanArray,ptr,lenght);
	
	SaveTOanArray[lenght]='\0';


}
void Get_IP_MAC()
{
	reset_buffer();
	
	UART_SEND_STRING("AT+CIFSR\r\n");
	_delay_ms(100);
	
	LCD_Clear_Screen();
	Send_A_String_WithLocation(1,1,"AP:");
	Get_String(rx_buffer,"APIP,\"",6,"\"",0,APIP);
	Send_A_String_WithLocation(6,1,APIP);
	
	Get_String(rx_buffer,"APMAC,\"",7,"\"",0,APMAC);
	Send_A_String_WithLocation(1,2,APMAC);
	
	_delay_ms(4000);

	LCD_Clear_Screen();

	Send_A_String_WithLocation(1,1,"STA: ");
	Get_String(rx_buffer,"STAIP,\"",7,"\"",0,STAIP);
	Send_A_String_WithLocation(6,1,STAIP);
	
	Get_String(rx_buffer,"STAMAC,\"",8,"\"",0,STAMAC);
	Send_A_String_WithLocation(1,2,STAMAC);
	
	reset_buffer();
}

void reset_buffer()
{
	memset(rx_buffer,0,500);
	Counter = 0 ;
}

void WiFi_Reset()
{
	UART_SEND_STRING("AT+RST\r\n");

	/*DDRC |=(1<<PC0);
	PORTC|=(1<<PC0);
	_delay_ms(5);
	PORTC&=~(1<<PC0);
	_delay_ms(5);
	DDRC &=~(1<<PC0);*/
	
	_delay_ms(20);
}


void Wifi_Mode()
{
	reset_buffer();
	UART_SEND_STRING("AT+CWMODE=3\r\n");
	_delay_ms(20);
}



void Wifi_Network()
{
	reset_buffer();
	UART_SEND_STRING("AT+CWJAP=");
	UART_TRANSMIT('"');
	UART_SEND_STRING(SSID);
	UART_TRANSMIT('"');
	UART_TRANSMIT(',');
	UART_TRANSMIT('"');
	UART_SEND_STRING(PASSWORD);
	UART_TRANSMIT('"');
	UART_SEND_STRING("\r\n");
	_delay_ms(20);
}
void TCB_Server()
{
	reset_buffer();
	UART_SEND_STRING("AT+CIPSERVER=1,");
	UART_SEND_STRING(PORT);
	UART_SEND_STRING("\r\n");
	_delay_ms(20);
}

void Wifi_Connection_Mode()
{
	reset_buffer();
	UART_SEND_STRING("AT+CIPMUX=1\r\n");
	_delay_ms(20);
}
void wifi_disconnect()
{
	reset_buffer();
	UART_SEND_STRING("AT+CWQAP\r\n");
	_delay_ms(20);
}
void Wifi_Send_Date(uint16_t send_data_size , char *Send_Command)
{
	char _send_data_size[send_data_size];
	Get_String(rx_buffer,"+IPD,",5,",",0,Connection_ID);
	itoa(send_data_size,_send_data_size,10);
	strcpy(Send_Command,"AT+CIPSEND=");
	strcat(Send_Command,Connection_ID1);
	strcat(Send_Command,",");
	strcat(Send_Command,_send_data_size);
	ltrim(_send_data_size);
}

void Wifi_Close(char *Close_Command)
{
	strcpy(Close_Command,"AT+CIPCLOSE=");
	strcat(Close_Command,Connection_ID);
	UART_SEND_STRING(Close_Command);
	UART_SEND_STRING("\r\n");
}
void WIFI_Config()
{
		//Restarting wifi
		memset(rx_buffer,0,500);
		Send_A_String_WithLocation(1,1,"Restarting Wifi..");
		Send_A_String_WithLocation(1,2,"Please Wait..");
		WiFi_Reset();
		//while(Response_success() != ready)
		
		//setting wifi mode
		_delay_ms(1000);
		LCD_Clear_Screen();
		Send_A_String_WithLocation(1,1,"Setting Mode..");
		Send_A_String_WithLocation(1,2,"Please Wait..");
		Wifi_Mode();
		while(Response_success() != OK);
		
		//setting connection mode
		_delay_ms(1000);
		LCD_Clear_Screen();
		Send_A_String_WithLocation(1,1,"Setting Conection");
		Send_A_String_WithLocation(1,2,"Please wait..");
		Wifi_Connection_Mode();
		while(Response_success() != OK);
		
		//disconnect any connecting Wifi network first
		wifi_disconnect();
		_delay_ms(1000);

		//Wifi AP Setting
		while(1)
		{
			//connect the stored Network
			LCD_Clear_Screen();
			Send_A_String_WithLocation(1,1,"Connecting AP..");
			Send_A_String_WithLocation(1,2,"Please wait..");
			Wifi_Network();
			_delay_ms(8000);
			//if it is connected successfully
			if ((Response_success()==OK))
			{
				Send_A_Command(0x01);
				_delay_ms(2);
				Send_A_String_WithLocation(1,1,"Success..");
				_delay_ms(2000);
				break;
			}
			//if it is not connected successfully
			else
			{
				Send_A_Command(0x01);
				_delay_ms(2);
				Send_A_String_WithLocation(1,1,"Try again.");
				_delay_ms(2000);
			}
			
		}
		
		//Configure TCP server
		LCD_Clear_Screen();
		Send_A_String_WithLocation(1,1,"Configure TCP..");
		Send_A_String_WithLocation(1,2,"Please wait..");
		TCB_Server();
		_delay_ms(2000);
		
		//Getting Server Info
		Get_IP_MAC();
		_delay_ms(1000);
		LCD_Clear_Screen();
		//Reseting rx_buufer
		reset_buffer();
		
	
    

	
}


void Get_data_Recieved(char *txt)
{
	Get_String(rx_buffer,":",1," ",0,txt);	
}

uint16_t Get_data_Recieved_Size(char *txt)
{
	uint8_t Size_data; 
	Size_data = strlen(txt);
	return Size_data;
}

uint16_t Get_data_Recieved_value(char *txt)
{
	uint16_t Value =atoi(txt);
	return Value;
}


void Check_Request()	
{
	while(find_string(rx_buffer,"+IPD")!=1);
}

void ltrim(char *string)
{
	int i=0;
	while(string[i]==' ')
	{
		i++;
		string=string+i;
	}
}
ISR(USART_RXC_vect)
{
	SREG  &=~(1<<7);
		
	temp = UART_RECEIVE();
	rx_buffer[Counter] = temp;
	Counter++;
	if(UDR == 0x0D)
	{
		rx_buffer[Counter]=0;
	}
	
	if(Counter == 500)
	{
		Counter = 0;
	}
	

	SREG  |= (1<<7);
}

#endif