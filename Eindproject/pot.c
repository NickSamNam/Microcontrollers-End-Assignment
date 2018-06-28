/*
 * pot.c
 *
 * Created: 28-6-2018 14:32:04
 *  Author: snick
 */

#include <avr/io.h>

#define Vref 5120

typedef unsigned long int u_int32;

void pot_init() {
	// Init IO
	DDRF &= ~0x02; // PF1(ADC1) Read
	
	// Init ADC
	ADMUX = 0x01; // ADC1, Vref off, right adjust result
	ADCSRA = 0xE6; // Enable ADC, start conversion, free running, interrupt disabled, prescaler 64
}

float pot_val() {
	u_int32 result = ADC;
	return result / 1023.0f;
}
