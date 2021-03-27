/*
 * File:   timmer0.c
 * Author: danny
 *
 * Created on 11 de marzo de 2021, 09:16 PM
 */


#include <xc.h>
#include "timmer0.h"


void timmer0_init(void){
    OPTION_REGbits.T0CS = 0;        //Selecciona fuente interna 
    OPTION_REGbits.T0SE = 1;        //Cuenta en flanco de bajada
    OPTION_REGbits.PSA = 1;         //Asigna el prescaler al TIMER0
    OPTION_REGbits.PS = 0x00;       //Ajusta en 2 el prescalador
    
    INTCONbits.T0IF = 0;            //Limpia la bandera de interrupcion
    INTCONbits.T0IE = 1;            //Activa la interrupcion por TIMER0
    INTCONbits.GIE = 1;             //Activa las interrupciones
    TMR0 = 251;
}