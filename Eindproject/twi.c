/*
 * twi.c
 *
 * Created: 22-3-2018 10:36:35
 *  Author: snick
 */ 

#include "twi.h"

#include <avr/io.h>
#include <avr/sfr_defs.h>

void twi_initMaster()
{
	/* 8000000/(16+2*38*4^1) = 25000 = 400000 / 16 */
	TWBR = 38;	// Set bit rate;
	TWSR = 0x00;	// Set bit rate prescaler
}

void twi_start()
{
	TWCR = _BV(TWSTA) | _BV(TWINT) | _BV(TWEN);
	while (0x00 == (TWCR & _BV(TWINT)));
}

void twi_stop()
{
	TWCR = _BV(TWSTO) | _BV(TWINT) | _BV(TWEN);
}

void twi_tx(unsigned char data)
{
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN);
	while (0x00 == (TWCR & _BV(TWINT)));
}