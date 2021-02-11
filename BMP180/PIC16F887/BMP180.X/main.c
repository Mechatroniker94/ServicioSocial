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
    char dato = 0x00;
    char buffer[20];
    TRISD = 0x00;
    TRISB = 0x00;
    ANSELH = 0x00;
    lcd_init();
    /*i2c_init();
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
    i2c_write(101);
    i2c_restart();
    i2c_write(0xA1);
    dato = i2c_read();
    i2c_sendNACK();
    i2c_stop();
    */
    sprintf(buffer,"dato = %d",dato);
    lcd_string(buffer);
    /*BMP180_init();*/
    while(1){
        
    }
}
