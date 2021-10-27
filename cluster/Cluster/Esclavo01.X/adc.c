#include "config.h"
#include "usart.h"
/*
 * 
 * El ADC 1 lectura en cada uno de los canales ADCH(0 - 2)
 * El ADC 
 */

//Btn1 ----- 10k -------224
//Btn2 ----- 8.7k       252
//Btn3 ----- 5.9k       352

int result[3] = {0};
int datos[3];
char buffer[50];
unsigned char btnFlags = 0x00;
unsigned char outState = 0;
unsigned char outState1 = 0;
char chState = 0;

void adc_init(void){
    ADCON0bits.ADCS = 0x00;     //Fosc /2
    ADCON1bits.VCFG0 = 0;       //Vref+ = VDD 
    ADCON1bits.VCFG1 = 0;       //Vref- = Vss
    ADCON1bits.ADFM = 1;        //Justificacion derecha
    ADCON0bits.CHS = 0;      //Canal 0
    ADCON0bits.ADON = 1;
}

void adc_chanSel(char chan){
    switch(chan){
        case 0:
            ADCON0bits.CHS = 0;
            break;
        case 1:
            ADCON0bits.CHS = 1;
            break;
        case 2:
            ADCON0bits.CHS = 2;
            break;              
    }
    __delay_ms(1);
}

int adc_start(void){
    int lectura = 0;
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_DONE == 1);
    lectura = (ADRESH << 8)+ ADRESL;
    return lectura;
}

unsigned char adc0_read(char i){
    char x0 = 0;
    adc_chanSel(0);
    x0 = adc_start();//Lectura de canales
    sprintf(buffer,"adc: %d\n",x0);
    usart_TxStr(buffer);
    return x0;
}
