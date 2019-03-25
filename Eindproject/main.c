/*
* Eindproject.c
*
* Created: 21-3-2018 16:37:17
* Author : snick
*/

#define F_CPU 8000000

#define DISPLAY_TIME 25
#define KEYBOARD_TIME 200

#define FIRST_CHAR '!'
#define FINAL_CHAR '~'
#define MAX_N_CHAR 16

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "HT16k33.h"
#include "HD44780U.h"
#include "font.h"
#include "pot.h"
#include "keyboard.h"

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
	pot_init();
	kb_init();
	LCD_init();
	
	char* text[MAX_N_CHAR + 1] = {'\0'};
	
	/* Display */
	int display_timer = DISPLAY_TIME;
	u_char display[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	u_char next_display[8];
	int text_prog = 0;
	int char_prog = 0;
	u_char next_char = '\0';
	
	/* Edit */
	int keyboard_timer = 0;
	char* edit_text[MAX_N_CHAR + 1] = {'\0'};
	int entry_pos = 0;
	u_char selected_char = '\0';
	
	/* Main loop */
	for(;;) {
		/* Display */
		if (display_timer >= DISPLAY_TIME * (1 / pot_val()))
		{
			display_timer = 0;
			if (char_prog == 0) {
				next_char = text[text_prog];
				text_prog++;
				if (text[text_prog] == '\0') {
					text_prog = 0;
				}
				memcpy(&next_display, &font[next_char], sizeof font[next_char]);
			}
			
			for (int i = 0; i < 8; i++) {
				display[i] = (display[i] >> 1) | (next_display[i] << 7);
				next_display[i] = next_display[i] >> 1;
			}
			
			char_prog = (char_prog + 1) % 8;
			dm_setAll(display);
		}
		
		/* Edit */
		if (keyboard_timer >= KEYBOARD_TIME) {
			keyboard_timer = 0;
			int *states[N_KEYS];
			kb_poll(&states);
				
			if (states[KEY_UP] && !states[KEY_DOWN]) {
				if (selected_char >= FINAL_CHAR || selected_char == '\0') selected_char = FIRST_CHAR;
				else if (selected_char < FINAL_CHAR) selected_char++;
				LCD_set_char(selected_char);
				LCD_set_cursor(entry_pos);
			}
			else if (states[KEY_DOWN] && !states[KEY_UP]) {
				if (selected_char <= FIRST_CHAR || selected_char == '\0') selected_char = FINAL_CHAR;
				else if (selected_char > FIRST_CHAR) selected_char--;
				LCD_set_char(selected_char);
				LCD_set_cursor(entry_pos);
			}
			
			if (states[KEY_OK]) {
				if (selected_char >= FIRST_CHAR && selected_char <= FINAL_CHAR)
				{
					if (edit_text[entry_pos] == '\0') edit_text[entry_pos + 1] = '\0';
					edit_text[entry_pos] = selected_char;
					if (entry_pos < MAX_N_CHAR) {
						entry_pos++;
						selected_char = edit_text[entry_pos];
						LCD_set_cursor(entry_pos);
					}
				}
			}
			
			if (states[KEY_SPACE]) {
				if (edit_text[entry_pos] == '\0') edit_text[entry_pos + 1] = '\0';
				edit_text[entry_pos] = ' ';
				LCD_set_char(edit_text[entry_pos]);
				if (entry_pos < MAX_N_CHAR) {
					entry_pos++;
					selected_char = edit_text[entry_pos];
					LCD_set_cursor(entry_pos);
				}
			}
			
			if (states[KEY_BACKSPACE]) {
				edit_text[entry_pos] = '\0';
				LCD_set_char(' ');
				if (entry_pos > 0) entry_pos--;
				selected_char = edit_text[entry_pos];
				LCD_set_cursor(entry_pos);
			}
			
			if (states[KEY_SET]) {
				memcpy(text, edit_text, sizeof text);
			}
			
			if (states[KEY_RESET]) {
				LCD_clear();
				entry_pos = 0;
				edit_text[0] = '\0';
				selected_char = edit_text[entry_pos];
			}
		}
		
		/* Timing */
		wait(1);
		display_timer++;
		keyboard_timer++;
	}
}
