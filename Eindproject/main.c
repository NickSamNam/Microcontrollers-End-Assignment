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

void wait(int ms)
{
	int i;
	for (i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

void test(void)
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

int main(void)
{
	test();
	
	/* Main loop */
	while (1) {
	}
}
