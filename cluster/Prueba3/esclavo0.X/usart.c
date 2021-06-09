/*
 * File:   usart.c
 * Author: danny
 *
 * Created on 13 de octubre de 2020, 09:56 AM
 */
#include "configuracion.h"

void usart_init(long BAUD){
    //configuracion de pines
    TRISCbits.TRISC6 = 0;   //Tx
    TRISCbits.TRISC7 = 1;   //Rx
    SPBRG = (unsigned char)(((_XTAL_FREQ/BAUD)/64) - 1);
    TXSTAbits.BRGH = 0;
    TXSTAbits.SYNC = 0;     //Comunicacion asincrona
    RCSTAbits.SPEN = 1;     //Habilitar el modulo UART

//Transmision
    TXSTAbits.TX9 = 0;      //8bits
    TXSTAbits.TXEN = 1;     //Activamos transmision

//Recepcion
    RCSTAbits.RC9 = 0;
    RCSTAbits.CREN = 1;
//Interrupcion
    PIE1bits.RCIE = 1;
    PIR1bits.RCIF = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

}

void usart_Tx(char send){
    TXREG = send;
    while (!TXSTAbits.TRMT);
}


char usart_Rx(){
    return RCREG;
}

void usart_TxStr(char *str){
    while(*str != '\0'){
        usart_Tx(*str);
        str++;
        //__delay_ms(50);
    }
}

void recivedCMD(unsigned char *cmd){
    //Esta porcion de codigo recibe un string de longitud fija
    /*
    int i;
    for(i = 0; i < 15; i++){
        cmd[i] = getche();
    }*/
    //Esta porcion de codigo recibe un string de longitud variable
    unsigned char i = 0;
    unsigned char j = 0;
        do{
        cmd[i] = getche();
        j = cmd[i];
        i++;
        }
        while((j != '\n') && (j != '\r'));
        
    //printf(*cmd);
    
    /*if(PIR1bits.RCIF == 1){
        for(int k = 0; k < sizeof(cmd) - 1; k++){    
            cmd[k] = getche();
            if(cmd[k] == '\n'){
                break;
            }
        }
        printf("%s\n",cmd);            //Optional for debug
        //tokenize(*cmd);
    }*/
}
/*
void putch(unsigned char byte){
    while(!TXIF){
        continue;
    }
    TXREG = byte;
}
unsigned char getche(){
    while(!PIR1bits.RCIF){
        continue;
    }
    return RCREG;
}
*/
