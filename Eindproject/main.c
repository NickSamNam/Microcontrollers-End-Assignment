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
#include "HD44780U.h"
#include "font.h"

char* text = "According to all known laws of aviation, there is no way a bee should be able to fly. Its wings are too small to get its fat little body off the ground. The bee, of course, flies anyway because bees don't care what humans think is impossible.\n";
// char* text = "Hello World!\n";
// char* text = "<";

void wait(int ms)
{
	int i;
	for (i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

int main(void) {
	dm_init();
	dm_clear();
	dm_setBrightness(16);
	
	u_char display[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	u_char next_display[8];
	int text_prog = -1;
	int char_prog = 8;
	u_char next_char = '\0';
	/* Main loop */
	for(;;) {
		if (char_prog == 8) {
			text_prog++;
			next_char = text[text_prog];
			if (next_char == '\0') {
				text_prog = 0;
				next_char = text[text_prog];
			}
			memcpy(&next_display, &font[next_char], sizeof font[next_char]);
			char_prog = 0;
		}
		
		for (int i = 0; i < 8; i++) {
			display[i] = (display[i] >> 1) | (next_display[i] << 7);
			next_display[i] = next_display[i] >> 1;
		}
		
		char_prog++;
		
		dm_setAll(display);
		wait(50);
	}
}
