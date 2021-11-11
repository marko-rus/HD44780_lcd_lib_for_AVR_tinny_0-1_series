/*
 * lcd.с
 *
 * Author: marko-rus
 * Библиотека для управления lcd дисплеями на базе контролера HD44780
 */ 

#include "lcd.h"
void sendhalfbyte(unsigned char c)
{
	c<<=4;
	e1; //включаем линию Е
	_delay_us(50);
	LCDPORT.OUT &=0b00001111; //стираем информацию на входах DB4-DB7, остальное не трогаем
	LCDPORT.OUT  |=c;
	e0; //выключаем линию Е
	_delay_us(50);
}
//----------------------------------------
void sendbyte(unsigned char c, unsigned char mode)
{
	if (mode)	rs1;
	else		rs0;
	unsigned char hc=0;
	hc=c>>4;
	sendhalfbyte(hc); sendhalfbyte(c);
}
//----------------------------------------
void sendcharlcd(unsigned char c)
{
	sendbyte(c,1);
}
//----------------------------------------
void setpos(unsigned char x, unsigned y)
{
	char adress;
	adress=(0x40*y+x)|0b10000000;
	sendbyte(adress, 0);
}
//----------------------------------------
void LCD_ini(void)
{
	_delay_ms(15); //Ждем 15 мс (стр 45)
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000, 0); //4бит-режим (DL=0) и 2 линии (N=1)
	_delay_ms(1);
	sendbyte(0b00001100, 0); //включаем изображение на дисплее (D=1), курсоры никакие не включаем (C=0, B=0)
	_delay_ms(1);
	sendbyte(0b00000110, 0); //курсор будет двигаться влево
	_delay_ms(1);
}
//----------------------------------------
void clearlcd(void)
{
	sendbyte(0b00000001, 0);
	_delay_us(1500);
}
//----------------------------------------
void str_lcd (char str1[])
{
	for(int n=0;str1[n]!='\0';n++)
	sendcharlcd(str1[n]);
}
//----------------------------------------
void num_to_lcd (int val)
{
	sendcharlcd((val%10)+'0');
}
//---------------------------------------
void lcd_definechar(const uint8_t *pc, uint8_t char_code, uint8_t chy)
{
	uint8_t a, ia;
	a=(char_code<<3)|0x40;
	for (ia=0; ia<8; ia++){
		sendbyte(a++, 0);
		sendcharlcd(pc[ia+chy]);
	}
}
//---------------------------------------