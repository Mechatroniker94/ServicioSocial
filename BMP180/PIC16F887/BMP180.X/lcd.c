/*
 * File:   lcd.c
 * Author: danny
 *
 * Created on 12 de octubre de 2020, 04:21 PM
 */


#include <xc.h>
#include "LCD.h"
#define _XTAL_FREQ 4000000


#define RS PORTBbits.RB0
#define RW PORTBbits.RB1
#define EN PORTBbits.RB2

#define DATA PORTD


void lcd_init(void){
    RW = 0;
    RS = 0;
    EN = 0;
    lcd_cmd(0x38);
    lcd_cmd(0x0F);
}//Fin lcdInit

void lcd_clear(void){
    lcd_cmd(0x01);
    lcd_cmd(0x02);
}//Fin lcdClear


void lcd_cmd(unsigned char c){
    RS = 0;
    DATA = c;
    EN = 1;
    __delay_ms(3);
    EN = 0;
    __delay_ms(3);
}//lcd_cmd

void lcd_write(unsigned char c){
    RS = 1;
    DATA = c;
    EN = 1;
    __delay_ms(1);
    EN = 0;
}//Fin de lcd_write

void lcd_string(unsigned char *c){
    while(*c){
        lcd_write(*c);
        *c++;
    }//fin del while
}//Fin de lcd_string