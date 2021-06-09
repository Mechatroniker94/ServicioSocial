/*
 * File:   main.c
 * Author: danny
 *
 * Created on 30 de mayo de 2021, 09:03 AM
 */


#include "configuracion.h"

void blink(void);
char chra = 0;
void __interrupt() ISR(void){
    chra = 0;
    INTCONbits.GIE = 0;
    chra = usart_Rx();
    PORTD = chra;
    PIR1bits.RCIF = 0;
    INTCONbits.GIE = 1;
}

char buffer[4];

void main(void) {
    
    ANSELH = 0x00;
    TRISB = 0x00;
    TRISD = 0x00;
    PORTD = 0x00;
    PORTB  = 0x00;
    usart_init(9600);
    while(1){
        blink();
    }
    return;
}

void blink(void){
    PORTBbits.RB0 = 1;
    __delay_ms(100);
    PORTBbits.RB0 = 0;
    __delay_ms(100);
}
