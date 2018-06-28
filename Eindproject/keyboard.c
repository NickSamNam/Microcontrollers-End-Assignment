/*
* keyboard.c
*
* Created: 28-6-2018 16:34:50
*  Author: snick
*/

#include "keyboard.h"
#include <avr/io.h>

void kb_init() {
	DDRD &= 0x1F;
	DDRE &= 0x1F;
	DDRF &= 0x1F;
}

void kb_poll(int *states[N_KEYS]) {
	states[KEY_UP]			= ((PINF & (1 << PINF6)) != 0);
	states[KEY_DOWN]		= ((PIND & (1 << PIND6)) != 0);
	states[KEY_LEFT]		= ((PINE & (1 << PINE7)) != 0);
	states[KEY_RIGHT]		= ((PINE & (1 << PINE5)) != 0);
	states[KEY_OK]			= ((PINE & (1 << PINE6)) != 0);
	states[KEY_SPACE]		= ((PINF & (1 << PINF5)) != 0);
	states[KEY_BACKSPACE]	= ((PINF & (1 << PINF7)) != 0);
	states[KEY_SET]			= ((PIND & (1 << PIND5)) != 0);
	states[KEY_RESET]		= ((PIND & (1 << PIND7)) != 0);
}
