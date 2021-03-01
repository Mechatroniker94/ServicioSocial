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

void blink(void);

void main(void) {
    TRISD = 0x00;
    usart_init(9600);
        
    while(1){
        for(int i = 0; i < 255;i++){
            blink();
            usart_Tx('H');
        }
        
    }//Fin del while
    return;
}

void blink(void){
    PORTDbits.RD0 = 1;
    __delay_ms(1000);
    PORTDbits.RD0 = 0;
    __delay_ms(1000);
    
}