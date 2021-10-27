#include <xc.h>
#include "config.h"

void usart_init(long BAUD){
    //BAUD RATE
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 0;
    SPBRG = (unsigned char)(((_XTAL_FREQ/BAUD)/64) - 1);
    //ANSEL BITS
    //ANSELBbits.ANSB1 = 0;
    //ANSELBbits.ANSB2 = 0;
    //ENABLE SERIAL PORT
    RCSTAbits.SPEN = 1;
    TXSTAbits.SYNC = 0;     //Comunicacion asincrona
    TXSTAbits.TX9 = 0;      //8bits
    TXSTAbits.TXEN = 1;     //Activamos transmision
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;

}//Inicia comunicacion


void usart_Tx(char send){
    TXREG = send;
    while (!TXSTAbits.TRMT);
}//Enviar caracter

char usart_Rx(){
    return RCREG;
}//Recibir caracter

void usart_TxStr(char *str){
    while(*str != '\0'){
        usart_Tx(*str);
        str++;
        //__delay_ms(10);
    }
}//Envia cadena

void usart_Interrupt(void){
    PIR1bits.RCIF = 0;      //Limpia la bandera
    PIE1bits.RCIE = 1;      //Activa las interrupciones por la UART
    INTCONbits.PEIE = 1;    //Activa las interrupcion de perifericos
    INTCONbits.GIE = 1;
}

void recivedCMD(char *cmd){
    unsigned char i = 0;
    unsigned char j = 0;
        do{
        cmd[i] = get1();
        j = cmd[i];
        i++;
        }
        while((j != '\n') && (j != '\r'));
    //usart_TxStr(cmd);                       //hasta aqui recibe bien datos.
}
    

unsigned char get1(){
    while(!PIR1bits.RCIF){
        continue;
    }
    return RCREG;
}

void token(char *cmd){
    char *tok = NULL;
    int i = 0;
    tok = strtok(cmd, ",");
    while( tok != NULL ) {
        dir[i] = tok;
        tok = strtok(NULL, ",");
        i++;
   }
}
