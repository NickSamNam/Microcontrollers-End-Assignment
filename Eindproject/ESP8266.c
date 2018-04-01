/*
* ESP8266.c
*
* Created: 30-3-2018 15:35:05
*  Author: snick
*/

#include "ESP8266.h"

#include <avr/sfr_defs.h>
#include <stdio.h>
#include <string.h>

#include "usart.h"

#define BAUDRATE 115200

#define MAX_COMMAND_SIZE 128
#define MAX_RESPONSE_SIZE 128

void sendCMD(char *data);
void receiveResponse(char *buffer);
int isOK();

int esp_init()
{
	usart_select(USART1);
	usart_init(BAUDRATE);
	sendCMD("AT");
	return isOK();
}

int esp_setupAP(char* ssid, char* pwd, u_char chl, u_char ecn, u_char max_conn, u_char ssid_hidden)
{
	sendCMD("AT+CWMODE_CUR=2");
	char cmd_ap[MAX_COMMAND_SIZE]; // Maximum number of characters of this command
	sprintf(cmd_ap, "AT+CWSAP_CUR=\"%s\",\"%s\",%c,%c,%c,%c", ssid, pwd, chl, ecn, max_conn, ssid_hidden);
	sendCMD(cmd_ap);
	return isOK();
}

void sendCMD(char *cmd)
{
	usart_select(USART1);
	int i;
	for (i = 0; cmd[i] != '\0'; i++)
	{
		usart_tx(cmd[i]);
	}
	usart_tx('\r');
	usart_tx('\n');
}

void receiveResponse(char *buffer)
{
	memset(buffer, 0, MAX_RESPONSE_SIZE);
	usart_select(USART1);
	int i;
	for (i = 0; i < MAX_RESPONSE_SIZE; i++)
	{
		u_char data = usart_rx();
		if (data == '\r')
		{
			break;
		}
		buffer[i] = data;
	}
}

int isOK()
{
	char response[MAX_RESPONSE_SIZE];
	receiveResponse(response);
	return strcmp(response, "OK") ? 0 : 1;
}