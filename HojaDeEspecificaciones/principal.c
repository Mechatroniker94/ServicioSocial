#include <htc.h>
#include <stdio.h>
//#include "glcd.h"
#include "lcd.h"

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

#define a1 1.978425E-2
#define a2 -2.001204E-7
#define a3 1.036969E-11
#define a4 -2.549687E-16
#define a5 3.585153E-21
#define a6 -5.344285E-26
#define a7 5.099890E-31

#define c1 50.38118782
#define c2 3.047583693E-2
#define c3 -8.56810657E-5
#define c4 1.322819530E-7
#define c5 -1.7052958E-10
#define c6 2.09480907E-13
#define c7 -1.2538395E-16
#define c8 1.56317257E-20

void delay_ms( unsigned short usvalue );

void main(void){
	float VM,VT_AMB,V,T;
	unsigned int LECTURA_ADC;
	unsigned char CADENA[5];
	ANSEL = 0x60; 		// AN5 Y AN6 HABILITADAS		
	ANSELH = 0x00;
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;		
	TRISD = 0x00;		
	TRISE = 0x03;		// RE0 Y RE1 COMO ENTRADAS
	ADCON1 = 0x00;  	//JUSTIFICACIÓN IZQUIERDA
	lcd_clear();
	lcd_init();

while(1)
		{					//MEDICION DEL VOLTAJE
		ADCON0 = 0xD5;  	//CANAL AN5
		GO_DONE = 1;
		while(GO_DONE);
		LECTURA_ADC = ((ADRESH<<2)|(ADRESL>>6));
		VM = LECTURA_ADC*35.26001955;   //CONVERSION A mV *(36071uV/1023)
							//MEDICION DEL VOLTAJE DEL TERMOPAR A T_AMBIENTE
		ADCON0 = 0xD9;  	//CANAL AN6
		GO_DONE = 1;
		while(GO_DONE);
		LECTURA_ADC = ((ADRESH<<2)|(ADRESL>>6));
		T = 0.5425219941*LECTURA_ADC;   //(555C/1023)*ADC
		VT_AMB = T*(c1+T*(c2+T*(c3+T*(c4+T*(c5+T*(c6+T*(c7+T*c8)))))));
		
		V = VM+VT_AMB;
		T = V*(a1+V*(a2+V*(a3+V*(a4+V*(a5+V*(a6+V*a7))))));

		sprintf(CADENA,"%2.2f",T);		
		lcd_goto(0x00);
		lcd_puts(CADENA);

		delay_ms(500);
		}//FIN while(1)
}
//https:www.onetransistor.eu/2018/03/code-text-mode-st7920-arduino.html


