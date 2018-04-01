/*
 * usart.h
 *
 * Created: 27-3-2018 09:20:15
 *  Author: snick
 */ 


#ifndef USART_H_
#define USART_H_


#define USART0 0
#define USART1 1

typedef unsigned char u_char;

void usart_select(int n);
void usart_init(long int baudrate);
void usart_tx(u_char data);
u_char usart_rx();


#endif /* USART_H_ */