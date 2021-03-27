/*
 * File:   main.c
 * Author: danny
 *
 * Created on 28 de febrero de 2021, 07:15 PM
 */


#include <xc.h>
#include <stdio.h>
#include "configuracion.h"
#include "usart.h"
#include "timmer0.h"
#include "oneWire.h"

#define blik PORTDbits.RD7 


void blink(void);

void main(void) {

    TRISD = 0x00;
    usart_init(9600);
    
    while(1){
        DHT11_read();
        __delay_ms(1000);
    }//Fin del while
    return;
}

void blink(void){
    PORTDbits.RD7 = 1;
    __delay_ms(1000);
    PORTDbits.RD7 = 0;
    __delay_ms(1000);
    
}