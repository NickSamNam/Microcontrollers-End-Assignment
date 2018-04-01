/*
* usart.c
*
* Created: 27-3-2018 09:14:28
*  Author: snick
*/

#include "usart.h"

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stddef.h>

#define FOSC 8000000	// Oscillator frequency

#define UBBR_VAL(baud) FOSC/16/baud-1

u_char usart_n;

void usart_select(int n)
{
	usart_n = n;
}

void usart_init(long int baudrate)
{
	long int ubbr_val = UBBR_VAL(baudrate);
	switch(usart_n) {
		case USART0:
		/* Set baud rate */
		UBRR0H = ubbr_val >> 8;
		UBRR0L = ubbr_val;
		/* Enable receiver and transmitter */
		UCSR0B = _BV(RXEN) | _BV(TXEN);
		/* Set frame format: N,8,1 */
		UCSR0C = _BV(UCSZ1) | _BV(UCSZ0);
		break;

		case USART1:
		/* Set baud rate */
		UBRR1H = ubbr_val >> 8;
		UBRR1L = ubbr_val;
		/* Enable receiver and transmitter */
		UCSR1B = _BV(RXEN) | _BV(TXEN);
		/* Set frame format: N,8,1 */
		UCSR1C = _BV(UCSZ1) | _BV(UCSZ0);
		break;

		default:
		return;
	}
}

void usart_tx(u_char data)
{
	switch (usart_n)
	{
		case USART0:
		while (!(_BV(UDRE) & UCSR0A));
		UDR0 = data;
		break;
		
		case USART1:
		while (!(_BV(UDRE) & UCSR1A));
		UDR1 = data;
		break;
		
		default:
		return;
	}
}

u_char usart_rx()
{
	switch (usart_n)
	{
		case USART0:
		while (!(_BV(RXC) & UCSR0A));
		return UDR0;
		break;
		
		case USART1:
		while (!(_BV(RXC) & UCSR1A));
		return UDR1;
		break;
		
		default:
		return '\0';
	}
}