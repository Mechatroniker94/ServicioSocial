/*
 * File:   oneWire.c
 * Author: danny
 *
 * Created on 8 de marzo de 2021, 09:11 PM
 */


#include <xc.h>
#include "oneWire.h"
#include "configuracion.h"
#include "usart.h"
#include <stdio.h>

char buffer[40];

void DHT11_start(){
    drive_OW_high();
    PORTDbits.RD0 = 0;
    __delay_ms(18);     //Pulso bajo de 18ms
    PORTDbits.RD0 = 1;
    //__delay_us(40);     //pulso alto de 40us
    drive_OW_low();

}
char DHT11_read(void){
    char info[5];
    char temp, hum;
    DHT11_start();
    slaveRespond();
    hum = DHT11_readByte();   //Humedad entero
    info[1] = DHT11_readByte();   //Humedad decimal
    temp = DHT11_readByte();   //Temp entero
    info[3] = DHT11_readByte();   //Temp decimal
    info[4] = DHT11_readByte();   //Paridad
    sprintf(measure, "T: %d, H:%d\n",hum,temp);
    usart_TxStr(measure);
    return 0;   
}

void slaveRespond(void){
    while(onePin);
    while(!onePin);
    while(onePin);
}

char DHT11_readByte(void){
    char dataByte;
    for(int i = 0; i < 8;i++){        
        while(!onePin);
        __delay_us(50);         
        if(onePin){  
           dataByte = ((dataByte << 1) | 1); 
        }
        else{
           dataByte = (dataByte << 1);  
        }
      while(onePin);
   }
    return dataByte;
}

void drive_OW_low(void){
    //Configura el pin como salida y pone el pin en bajo
    TRISDbits.TRISD0 = 1;
    onePin = 0;
}

void drive_OW_high(void){
    TRISDbits.TRISD0 = 0;
    onePin = 1;
}





 



