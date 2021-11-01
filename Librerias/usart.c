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
/*
void recivedCMD(unsigned char *cmd){
    //Esta porcion de codigo recibe un string de longitud fija
    int i;
    for(i = 0; i < 15; i++){
        cmd[i] = getche();
    }
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
    
    if(PIR1bits.RCIF == 1){
        for(int k = 0; k < sizeof(cmd) - 1; k++){    
            cmd[k] = getche();
            if(cmd[k] == '\n'){
                break;
            }
        }
        printf("%s\n",cmd);            //Optional for debug
        //tokenize(*cmd);
    }
}

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