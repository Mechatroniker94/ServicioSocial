/*
 * File:   main.c
 * Author: luis.martinez
 *
 * Created on 24 de agosto de 2021, 09:44 AM
 */


#include <xc.h>
#include "config.h"

char data[10] = "";

void __interrupt() myISR(void){
    INTCONbits.GIE = 0;
    //usart_Tx('a');
    recivedCMD(data);
    token(data);
    if(strcmp(dir[0],"M2") == 0){
        if(strcmp(dir[1],"P1") == 0){
            if(*dir[2] == 'a'){
                i2c_start();
                i2c_write(0x31);
                lectura = i2c_read();
                i2c_stop();
                sprintf(data,"%d\n",lectura);
                usart_TxStr(data);
            }
            else{
                i2c_start();
                i2c_write(0x30);
                i2c_write(*dir[2]);
                 i2c_stop();
            }
        }
        else if(strcmp(dir[1],"P2") == 0){
            if(*dir[2] == 'a'){
                i2c_start();
                i2c_write(0x33);
                lectura = i2c_read();
                i2c_stop();
                sprintf(data,"%d\n",lectura);
                usart_TxStr(data);
            }
            else{
                i2c_start();
                i2c_write(0x32);
                i2c_write(*dir[2]);
                i2c_stop();
            }
        } 
    }
    PIR1bits.RCIF = 0;
    INTCONbits.GIE = 1;
}

void main(void) {
    TRISD = 0x00;
    PORTD = 0x00;
    TRISB = 0x00;
    PORTB = 0x00;
    usart_init(9600);
    usart_Interrupt();
    i2c_init();
    
    while(1){
        PORTBbits.RB0 = 1;
        __delay_ms(1000);
        
        PORTBbits.RB0 = 0;
        __delay_ms(1000);
    }
    return;
}
