/*
 * HT16K33.c
 *
 * Created: 22-3-2018 14:22:09
 *  Author: snick
 */ 

#include "HT16K33.h"

#include <avr/sfr_defs.h>

#include "twi.h"

#define SL_ADDR 0xE0	// Slave address

void dm_init()
{
	twi_initMaster();	// Init TWI
	
	/* System setup */
	twi_start();
	twi_tx(SL_ADDR);
	twi_tx(0x21);	// Turn on oscillator
	twi_stop();
	
	/* ROW/INT Set */
	twi_start();
	twi_tx(SL_ADDR);
	twi_tx(0xA0);	// All output
	twi_stop();
	
	/* Display setup */
	twi_start();
	twi_tx(SL_ADDR);
	twi_tx(0x81);	// Display on, blinking off
	twi_stop();
}

void dm_setRow(u_char row, u_char dots)
{
	row *= 2;	// Rows are multiples of 2
	
	// First dot is eighth bit
	u_char f = (0x01 & dots) << 7;
	dots >>= 1;
	dots |= f;
	
	twi_start();
	twi_tx(SL_ADDR);
	twi_tx(row);
	twi_tx(dots);
	twi_stop();
}

void dm_setAll(u_char matrix[8]) {
	int i;
	for (i = 0; i < 8; i++) {
		dm_setRow(i, matrix[i]);
	}
}

void dm_clear()
{
	int i;
	for(i = 0; i < 8; i++) {
		dm_setRow(i, 0x00);
	}
}

/* 1-16 */
void dm_setBrightness(u_char bri)
{
	bri = (bri < 1) ? 1 : ((bri > 16) ? 16 : bri);	// Handle out of range values
	twi_start();
	twi_tx(SL_ADDR);
	twi_tx(0xE0 | (bri - 1));
	twi_stop();
}