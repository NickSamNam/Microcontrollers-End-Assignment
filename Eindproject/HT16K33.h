/*
 * HT16K33.h
 *
 * Created: 24-3-2018 15:30:40
 *  Author: snick
 */ 


#ifndef HT16K33_H_
#define HT16K33_H_

typedef unsigned char u_char;

void dm_init(void);
void dm_setRow(u_char row, u_char dots);
void dm_setAll(u_char matrix[8]);
void dm_clear(void);
/* 1-16 */
void dm_setBrightness(u_char bri);


#endif /* HT16K33_H_ */