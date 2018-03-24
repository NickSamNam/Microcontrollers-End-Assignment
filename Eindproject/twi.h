/*
 * twi.h
 *
 * Created: 22-3-2018 14:20:28
 *  Author: snick
 */ 


#ifndef TWI_H_
#define TWI_H_

/* Init TWI for master usage */
void twi_initMaster(void);

/* Start line */
void twi_start(void);

/* Stop line */
void twi_stop(void);

/* Transmit */
void twi_tx(unsigned char data);

#endif /* TWI_H_ */