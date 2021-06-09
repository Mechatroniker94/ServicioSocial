/*
 * File:   main.c
 * Author: danny
 *
 * Created on 22 de abril de 2021, 10:14 PM
 */
#include "configuracion.h"

char z;
char j = 0;
void __interrupt() respuesta(void){
    PORTBbits.RB1 = 1;
    j = j + 1;
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
          PORTBbits.RB1 = 1;
          //z = SSPBUF;
          BF = 0;
          SSPBUF = PORTB;
          SSPCONbits.CKP = 1;
          while(SSPSTATbits.BF);
        }

        SSPIF = 0;
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
      } 
}

void main(void) {
    ANSEL = 0x00;
    ANSELH = 0x00;
    TRISB = 0xFF;
    //PORTB = 0x00;
    TRISD = 0x00;
    PORTD = 0x00;
    usart_init(9600);
    adc_init();
    i2c_Slave_Init(0x30);
    char buf[25];
    int muestra = 0;
    while(1)
    {
        /*
        for(j ; j < 255;j++){
            
        }
        if(j > 255){
            j = 0;
        }*/
        /*PORTDbits.RD0 = 1;
        muestra = 0;
        sprintf(buf,"ADC = %d", muestra);
        usart_TxStr(buf);
        __delay_ms(1000);*/
    }//Fin de la funcion principal    
    return;
}
