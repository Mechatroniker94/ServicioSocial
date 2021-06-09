/*
 * File:   main.c
 * Author: danny
 *
 * Created on 22 de mayo de 2021, 09:40 PM
 */


#include "configuracion.h"
void enviarDato(char entero);
void blink(void);
char chra = 0;
void __interrupt() ISR(void){
    INTCONbits.GIE = 0;
    chra = usart_Rx();
    if(chra == 'a'){
        enviarDato(PORTB);
    }
    PIR1bits.RCIF = 0;
    INTCONbits.GIE = 1;
}

char buffer[4];

void main(void) {
    
    ANSELH = 0x00;
    TRISB = 0xFF;
    TRISD = 0x00;
    PORTD = 0x00;
    usart_init(9600);
    usart_Tx('z');
    while(1){
        blink();
    }
    return;
}


void enviarDato(char entero){
    sprintf(buffer, "%d\n", entero);
    usart_TxStr(buffer);
}


void blink(void){
    PORTDbits.RD0 = 1;
    __delay_ms(100);
    PORTDbits.RD0 = 0;
    __delay_ms(100);
}