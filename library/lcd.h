/*
 * lcd.h
 *
 * Author: marko-rus
 * Библиотека для управления lcd дисплеями на базе контролера HD44780
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "init.h"
#define LCDPORT PORTA
#define CTRLPORT PORTB
#define rs 1
#define e 0

#define e1		CTRLPORT.OUT |= (1<<e) // установка линии E в 1
#define e0		CTRLPORT.OUT &= ~(1<<e) // установка линии E в 0
#define rs1		CTRLPORT.OUT |= (1<<rs) // установка линии RS в 1 (данные)
#define rs0		CTRLPORT.OUT &= ~(1<<rs) // установка линии RS в 0 (команда)

void setpos(unsigned char x, unsigned y);
void LCD_ini(void);
void clearlcd(void);
void str_lcd (char str1[]);
void num_to_lcd (int val);
void lcd_definechar(const uint8_t *pc, uint8_t char_code, uint8_t chy);
void sendcharlcd(unsigned char c);
void sendbyte(unsigned char c, unsigned char mode);

#endif /* LCD_H_ */