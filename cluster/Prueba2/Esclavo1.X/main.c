/*
 * File:   main.c
 * Author: danny
 *
 * Created on 22 de mayo de 2021, 10:31 PM
 */


#include "configuracion.h"


void blink(void);
char z;
char sla0 = 0;
void __interrupt() respuesta(void){
    INTCONbits.GIE = 0;
    PORTBbits.RB1 = 1;
    //j = j + 1;
    if(PIR1bits.RCIF == 1){
        PORTD = usart_Rx();
        PIR1bits.RCIF = 0;
    }
    
    if(SSPIF == 1){
    SSPCONbits.CKP = 0;
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
          z = SSPBUF; // Read the previous value to clear the buffer
          SSPCONbits.SSPOV = 0; // Clear the overflow flag
          SSPCONbits.WCOL = 0;  // Clear the collision bit
          SSPCONbits.CKP = 1; 
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW){//escribir en el esclavo
          PORTBbits.RB0 = 1;
          z = SSPBUF;
          while(!BF);
          PORTD = SSPBUF;
          SSPCONbits.CKP = 1;
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){   //Leer en el esclavo
            usart_Tx('a');
            PORTBbits.RB1 = 1;
            z = SSPBUF;
            BF = 0;
            SSPBUF = sla0;
            SSPCONbits.CKP = 1;
            while(SSPSTATbits.BF);
            
        }
    PIR1bits.SSPIF = 0;
    }
    
    INTCONbits.GIE = 1;
}


void main(void) {
    TRISD = 0x00;
    PORTD = 0x00;
    i2c_Slave_Init(0x30);
    usart_init(9600);
    //usart_Tx('a');
    while(1){
            //sla0 = usart_Rx();
        //usart_Tx('b');
        
    }//Fin del ciclo infinito
    return;
}

void blink(void){
    PORTDbits.RD0 = 1;
    __delay_ms(100);
    PORTDbits.RD0 = 0;
    __delay_ms(100);
}