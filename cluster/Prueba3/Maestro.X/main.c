/*
 * File:   main.c
 * Author: danny
 *
 * Created on 5 de mayo de 2021, 08:26 PM
 * 
 * Este programa es el primero del cluste, consiste en conectar 2 microcontroladores por protocolo I2C 
 */

#include "configuracion.h"

char revD = 0x00;
char buffer[20];
void blink(char data);

void main(void) {
    TRISB = 0x00;
    PORTB = 0x00;
    TRISD = 0x00;
    PORTD = 0x00;
    //Configuracion del maestro
    i2c_init();
    usart_init(9600);
    __delay_ms(1500);
    while(1){
        for(int i = 0; i < 255;i++){
        blink(i);
        //Manda llamar al esclavo
        }
    }
    return;
}

void blink(char data){
    //PORTBbits.RB0 = 1;
    __delay_ms(500);
    //PORTDbits.RD0 = 0;
    __delay_ms(500);
    //Escribir en el Esclavo
    i2c_start();
    i2c_write(0x30);
    i2c_write(data);
    i2c_stop();
    //
    i2c_start();
    i2c_write(0x31);     //7 bit address + Read
    revD = i2c_read(); //Read + Acknowledge
    i2c_stop();
    usart_Tx(revD);
}