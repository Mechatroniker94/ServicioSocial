/*
 * File:   main.c
 * Author: luis.martinez
 *
 * Created on 24 de agosto de 2021, 09:44 AM
 */

#include "config.h"

char data[10] = "";
char z;

void __interrupt() myISR(void){
    INTCONbits.GIE = 0;
    if(SSPIF == 1){
    SSPCONbits.CKP = 0;
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
          z = SSPBUF; // Read the previous value to clear the buffer
          SSPCONbits.SSPOV = 0; // Clear the overflow flag
          SSPCONbits.WCOL = 0;  // Clear the collision bit
          SSPCONbits.CKP = 1;
          
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW){//escribir en el esclavo
          z = SSPBUF;
          while(!BF);
          //PORTD = z;
          switch(SSPBUF){
              case 61:
                  
                  break;
              case 'b':
                  PORTDbits.RD0 = 0;
                  PORTDbits.RD1 = 0;
                  PORTDbits.RD2 = 1;
                  break;
              case 'g':
                  PORTDbits.RD0 = 0;
                  PORTDbits.RD1 = 1;
                  PORTDbits.RD2 = 0;
                  break;
              case 'r':
                  PORTDbits.RD0 = 1;
                  PORTDbits.RD1 = 0;
                  PORTDbits.RD2 = 0;
                  break;
              default:
                  PORTDbits.RD0 = 0;
                  PORTDbits.RD1 = 0;
                  PORTDbits.RD2 = 0;
                  break;        
          }
          SSPCONbits.CKP = 1;
        }
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){   //Leer en el esclavo
            adc = adc_start();
            BF = 0;                       //Envia el BYTE menos significativo
            SSPBUF = (adc & 0xFF);
            SSPCONbits.CKP = 1;
            while(SSPSTATbits.BF);
            BF = 0;                       //Envia el Byte mas significativo
            SSPBUF = (adc >> 8) & 0xFF;
            SSPCONbits.CKP = 1;
            while(SSPSTATbits.BF);
        }
      }
    PIR1bits.SSPIF = 0;
    INTCONbits.GIE = 1;
}

void main(void) {
    TRISA =0x01;
    TRISD = 0x00;
    PORTD = 0x00;
    TRISB = 0x00;
    PORTB = 0x00;
    i2c_Slave_Init(0x32);
    adc_init();
    //usart_init(9600);
    
    while(1){
        PORTBbits.RB0 = 1;
        __delay_ms(1000);
        
        PORTBbits.RB0 = 0;
        __delay_ms(1000);
    }
    return;
}
