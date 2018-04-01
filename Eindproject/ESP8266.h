/*
 * ESP8266.h
 *
 * Created: 30-3-2018 15:47:46
 *  Author: snick
 */ 


#ifndef ESP8266_H_
#define ESP8266_H_


#define ESP_ECN_OPEN 0
#define ESP_ECN_WPA_PSK 2
#define ESP_ECN_WPA2_PSK 3
#define ESP_ECN_WPA_WPA2_PSK 4

typedef unsigned char u_char;

int esp_init(void);
int esp_setupAP(char* ssid, char* pwd, u_char chl, u_char ecn, u_char max_conn, u_char ssid_hidden);


#endif /* ESP8266_H_ */