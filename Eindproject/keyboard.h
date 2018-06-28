/*
* keyboard.h
*
* Created: 28-6-2018 16:54:26
*  Author: snick
*/


#ifndef KEYBOARD_H_
#define KEYBOARD_H_


#define N_KEYS 9

#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_OK 4
#define KEY_SPACE 5
#define KEY_BACKSPACE 6
#define KEY_SET 7
#define KEY_RESET 8

void kb_init(void);
void kb_poll(int *states[N_KEYS]);


#endif /* KEYBOARD_H_ */