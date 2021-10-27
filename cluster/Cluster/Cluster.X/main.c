/*
 * File:   main.c
 * Author: luis.martinez
 *
 * Created on 24 de agosto de 2021, 08:08 AM
 */

#include "config.h"

//char cmdArray[][12] = {{"M1,P1,r\n"},{"M1,P1,g\n"},{"M1,,P1,b\n"},{"M1,P1,a\n"},{"M1,P2,r\n"},{"M1,P2,g\n"},{"M1,P2,b\n"},{"M1,P2,a\n"}};//,{"M2,P1,r\n"},{"M2,P1,g\n"},{"M2,P1,b\n"},{"M2,P2,a\n"},{"M2,P2,r\n"},{"M2,P2,g\n"},{"M2,P2,b\n"},{"M2,P2,a\n"},{"M3,P1,r\n"},{"M3,P1,g\n"},{"M3,P1,b\n"},{"M3,P1,a\n"},{"M3,P2,r\n"},{"M3,P2,g\n"},{"M3,P2,b\n"},{"M3,P2,a\n"}};

char *ptrCmd = NULL;

void main(void) {
    ANSELH = 0x00;
    TRISB = 0xFF;       //Puerto B como entrada
    usart_init(9600);
    char entrada = 0;
    while(1){
        entrada = PORTB;
        __delay_ms(1000);
        switch(entrada){
        case 0:         //Apagado todo
                //usart_TxStr(cmdArray[0]);
                break;
            case 1:         //uC 0 Led rojo
                usart_TxStr("M1,P1,r\n");
                break;
            case 2:         //uC 0 Led verde
                usart_TxStr("M1,P1,g\n");
                break;
            case 3:         //wC 0 Led azul
                usart_TxStr("M1,P1,b\n");
                break;
            case  4:         //uC 0 A
                usart_TxStr("M1,P1,a\n");
                break;
            case 5:         //uC 1 Led rojo
                usart_TxStr("M1,P2,r\n");
                break;
            case 6:        //uC 2 LEd verde
                usart_TxStr("M1,P2,g\n");
                break;
            case 7:         //uC 2 Led azul
                usart_TxStr("M1,P2,b\n");
                break;
             case 8:         //uC 2 ADC
                usart_TxStr("M1,P2,a\n");
                break;
            case 9:        //uC 3 Led rojo
               usart_TxStr("M2,P1,r\n");
               break;
            case 10:       //uC 3 Led verde
               usart_TxStr("M2,P1,g\n");
               break;
            case 11:        //uC 3 Led azul
               usart_TxStr("M2,P1,b\n");
               break;
            case 12:        //uC 3 ADC
               usart_TxStr("M2,P1,a\n");
               break;
            case 13:        //uC 3 ADC
               usart_TxStr("M2,P2,r\n");
               break;
            case 14:        //uC 3 ADC
               usart_TxStr("M2,P2,g\n");
               break;
            case 15:        //uC 3 ADC
               usart_TxStr("M2,P2,b\n");
               break;
            case 16:        //uC 3 ADC
               usart_TxStr("M2,P2,a\n");
               break;
            case 17:        //uC 3 ADC
               usart_TxStr("M3,P1,r\n");
               break;
            case 18:        //uC 3 ADC
               usart_TxStr("M3,P1,g\n");
               break;
            case 19:        //uC 3 ADC
               usart_TxStr("M3,P1,b\n");
               break;
            case 20:        //uC 3 ADC
               usart_TxStr("M3,P1,a\n");
               break;
            case 21:        //uC 3 ADC
               usart_TxStr("M3,P2,r\n");
               break;
            case 22:        //uC 3 ADC
               usart_TxStr("M3,P2,g\n");
               break;
            case 23:        //uC 3 ADC
               usart_TxStr("M3,P2,b\n");
               break;
            case 24:        //uC 3 ADC
               usart_TxStr("M3,P2,b\n");
               break;
            case 25:        //uC 3 ADC
               usart_TxStr("M3,P2,a\n");
               break;
            default:
               break;
        }
    }//Ciclo invinito
    return;
}
