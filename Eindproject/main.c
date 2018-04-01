/*
* Eindproject.c
*
* Created: 21-3-2018 16:37:17
* Author : snick
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "HT16k33.h"
#include "ESP8266.h"
#include "HD44780U.h"

void wait(int ms)
{
	int i;
	for (i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

void testDM(void)
{
	dm_init();
	dm_clear();
	dm_setBrightness(16);
	
	int l = 0;
	
	/* Main loop */
	while (1) {
		u_char x, y;
		for (x = 0; x < 8; x++) {
			for (y = 0; y < 8; y++) {
				if(0 == x % 2 - l) {
					dm_setRow(x, 0x01 << y);
					dm_setRow(7-x, 0x80 >> y);
				}
				else {
					dm_setRow(x, 0x80 >> y);
					dm_setRow(7-x, 0x01 << y);
				}
				wait(100);
			}
			dm_setRow(x, 0x00);
			dm_setRow(7-x, 0x00);
		}
		l = (0 == l) ? 1 : 0;
	}
}

void testESP(void)
{
	LCD_set_cursor(0);
	LCD_display_text("INIT...         ");
	if (esp_init())
	{
		LCD_set_cursor(40);
		LCD_display_text("OK              ");
	}
	else
	{
		LCD_set_cursor(40);
		LCD_display_text("FAILED          ");
		return;
	}
	wait(1000);
	LCD_set_cursor(0);
	LCD_display_text("SETTING UP AP...");
	LCD_set_cursor(40);
	LCD_display_text("                ");
	if (esp_setupAP("ESP8266", "qwerty", 14, ESP_ECN_WPA2_PSK, 1, 0))
	{
		LCD_set_cursor(40);
		LCD_display_text("OK              ");
	}
	else
	{
		LCD_set_cursor(40);
		LCD_display_text("FAILED          ");
	}
}

int main(void)
{
	#if 0
	LCD_init();
	LCD_set_cursor(0);
	LCD_display_text("TESTING...      ");
	wait(1000);
	testESP();
	#endif
	testDM();
	
	/* Main loop */
	while (1) {
	}
}
