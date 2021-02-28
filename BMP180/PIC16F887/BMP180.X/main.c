/*
 * File:   main.c
 * Author: Daniel Martinez
 * Description: This code implement BMP180 sensor in the PIC16F877
 * Created on 2 de febrero de 2021, 09:34 PM
 */

#include <xc.h>
#include <stdio.h>
#include "I2C.h"
#include "configuracion.h"
#include "BMP180.h"
#include "lcd.h"

void main(void) {
    char buffer[25];
    TRISD = 0x00;
    TRISB = 0x00;
    ANSELH = 0x00;
    lcd_init();
    lcd_clear();
/*
    i2c_init();
    i2c_start();
    i2c_write(0xA0);
    i2c_write(0x00);
    i2c_write(100);
    i2c_write(50);
    i2c_write(150);
    i2c_write(10);
    i2c_stop();
    //Lectura
    i2c_start();
    i2c_write(0xA0);
    i2c_write(0x00);
    i2c_write(100);
    i2c_restart();
    i2c_write(0xA1);
    dato = i2c_read();
    i2c_sendACK();
    dato2 = i2c_read();
    i2c_sendACK();
    dato3 = i2c_read();
    i2c_sendNACK();
    i2c_stop();
    sprintf(buffer,"%d , %d, %d",dato, dato2, dato3);
    lcd_string(buffer);*/
    BMP180_init();
    long temperatura = 0;
    long press = 0;
    while(1){
        
        temperatura = BMP180_readTemperature();
        sprintf(buffer,"T = %ld", temperatura); // 7%
        lcd_string(buffer);
        press = BMP180_readPreassure();
        sprintf(buffer,"P = %ld", press); // 7%
        lcd_string(buffer);
        __delay_ms(1000);
        lcd_clear();
        
        //i2c_coeficiente();
     
    }
}
