#ifndef UART_H
#define UART_H


void UART_init(uint32_t BaudRate);
unsigned char UART_RECEIVE();
void UART_TRANSMIT(char data);
void UART_SEND_STRING(char *str);
void UART_SEND_CONST_STRING(const char *data);



#endif /*UART_H*/