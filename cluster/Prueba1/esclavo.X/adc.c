#include "configuracion.h"
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
/*
void keypad_read(void){    
    int adc = 0;
    adc = adc0_read(0);
    adc = adc1_read();
    adc = adc2_read();
}

char keyid(int a){
    char desvi = 15;
    char tecla = 0;
    if((a <= 224 + desvi) && (a >= 224 - desvi)){     //boton 1
        usart_TxStr("B1\n");
        tecla = 1;
        //void espera();
    }
    else if((a <= 252 + desvi) && (a >= 252 - desvi)){    //boton 2
        usart_TxStr("B2\n");
        tecla = 2;
    }
    else if((a <= 360 + desvi) && (a >= 360 - desvi)){    //boton 3
        usart_TxStr("B3\n");
        tecla = 3;
    }
    else if((a <= 513 + desvi) && (a >= 513 - desvi)){    //boton 4
        usart_TxStr("B4 \n");
        tecla = 4;
    }
    else{
        //printf("No se presiono boton\n");
        espera();
    }
    __delay_ms(50);
    return tecla;
}

unsigned char adc0_read(char i){
    char x0 = 0;
    adc_chanSel(0);
    result[0] = adc_start();//Lectura de canales
    __delay_ms(2);
    x0 = keyid(result[0]);
    outAct(x0);
    sprintf(buffer, "a0 = %d\n",x0);
    usart_TxStr(buffer);
    return x0;
}

unsigned char adc1_read(void){
    char x1 = 0;
    adc_chanSel(1);
    result[1] = adc_start();//Lectura de canales
    __delay_ms(2);
    x1 = keyid(result[1]);
    sprintf(buffer, "a1 = %d\n",x1);
    usart_TxStr(buffer);
    outAct1(x1);
    return x1;
}

unsigned char adc2_read(void){
    char x2 = 0;
    adc_chanSel(2);
    result[2] = adc_start();//Lectura de canales
    __delay_ms(2);
    x2 = keyid(result[2]);
    sprintf(buffer, "a2 = %d\n",x2);
    usart_TxStr(buffer);
    outAct2(x2);
    return x2;
}

void outAct(char lvl){
    switch(outState){
        
        case 0:                 //Estado bajo
            if(lvl == 1){
                outState = 1;
            }
            else if(lvl == 2){
                outState = 4;
            }
            else if(lvl == 3){
                outState = 7;
            }
            else if(lvl == 4){
                outState = 1;
            }
            else{
                outState = 0;
            }
            break;
        // BOTON 1 -------  Lampara
        case 1:                 //Transicion - subida
            lamp();
            outState = 2;
            break;
        case 2:                 //Enclave
            if(lvl == 0){
                outState = 3;
            }
            break;
        case 3:                 //Transicion - bajada
            outState = 0;
            break;
        // BOTON 2 -------  Contactos AC
        case 4:                 //Transicion - subida
            aCconector();
            outState = 5;
            break;
        case 5:                 //Enclave
            if(lvl == 0){
                outState = 6;
            }
            break;
        case 6:                 //Transicion - bajada
            outState = 0;
            break;
        //BOTON 3 --------- Sllon arriba
        case 7:                 //Transicion - subida
            columnUp();
            //__delay_ms(1000);
            outState = 8;
            break;
        case 8:                 //Enclave
            if(lvl == 0){
                outState = 9;
            }
            break;
        case 9:                 //Transicion - bajada
            Up_C = 0;
            outState = 0;
            break;
        default:
            break;    
    }
}

void outAct1(char lvl1){
    switch(outState1){
        case 0:                 //Estado bajo
            if(lvl1 == 1){
                outState1 = 1;
            }
            else if(lvl1 == 2){
                outState1 = 4;
            }
            else if(lvl1 == 3){
                outState1 = 7;
            }
            else if(lvl1 == 4){
                outState1 = 1;
            }
            else{
                outState1 = 0;
            }
            break;
        // BOTON 1 -------  columna abajo
        case 1:                 //Transicion - subida
            columnDw();
            outState1 = 2;
            break;
        case 2:                 //Enclave
            if(lvl1 == 0){
                outState1 = 3;
            }
            break;
        case 3:                 //Transicion - bajada
            Down_C = 0;
            outState1 = 0;
            break;
        // BOTON 2 -------  Sillon arriba
        case 4:                 //Transicion - subida
            chairUp();
            outState1 = 5;
            break;
        case 5:                 //Enclave
            if(lvl1 == 0){
                outState1 = 6;
            }
            break;
        case 6:                 //Transicion - bajada
            outState1 = 0;
            break;
        //BOTON 3 --------- Sllon abajo
        case 7:                 //Transicion - subida
            chairDw();
            outState1 = 8;
            break;
        case 8:                 //Enclave
            if(lvl1 == 0){
                outState1 = 9;
            }
            break;
        case 9:                 //Transicion - bajada
            outState1 = 0;
            break;
        default:
            break;   
    }
}

void outAct2(char lvl2){
    
}
 */