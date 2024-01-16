/* 
 * File:   Main.h
 * Author: icon
 *
 * Created on December 8, 2021, 1:06 AM
 */

#ifndef MAIN_H
#define	MAIN_H
#define COOKING_MODE_DISPLAY     0x01
#define MICRO_MODE               0x02
#define TIME_DISPLAY             0x03
#define  RESET_NOTHING           0x0F
#define  MICRO_MODE_RESET        0x10

#define FAN                      RC2
#define FAN_DDR                  TRISC2

void power_on_screen(void);
void cooking_mode_display(void);
void set_time(unsigned char key);


void clear_clcd(void);
#endif	/* MAIN_H */

