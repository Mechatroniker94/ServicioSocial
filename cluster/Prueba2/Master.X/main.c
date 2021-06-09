/*
 * File:   main.c
 * Author: danny
 *
 * Created on 22 de mayo de 2021, 09:17 PM
 * Programa para configurar el microcontrolador como maestro 
 */

#include "configuracion.h"

void readV(void);

void main(void) {
    ANSELH = 0x00;
    TRISB = 0x00;
    PORTB = 0x00;
    i2c_init();
    
    while(1){
        readV();
        __delay_ms(2000);
    }//Fin del while
    
    
    return;
}

void readV(void){
    //i2c_start();
    //i2c_write(0x30);
    //i2c_write(0x00);
    //i2c_stop();
    //
    i2c_start();
    i2c_write(0x31);     //7 bit address + Read
    PORTB = i2c_read(); //Read + Acknowledge
    i2c_stop();
    
}
