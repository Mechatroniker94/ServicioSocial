#include "configuracion.h"

/*Registros importantes: 
 SSPSTAT
 SSPCON        COnfiguracion mode
 SSPCON2        Registro para generar señales
 SSPADD         Registro para modificar velocidad transmision
 SSPBUF
    */
void i2c_init(void){
    //1.- Configurar el modulo MSSP como maestro
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    SSPADD = 0x09;
    SSPSTAT = 0x80;
    SSPCON2 = 0x00;
    SSPCON = 0x28;
}//Fin de la funcion i2c_init

void i2c_start(void){
    //Condicion de inicio
    i2c_idle();
    SSPCON2bits.SEN = 1;
    while(SSPCON2bits.SEN == 1);
    while(SSPIF == 0);
    SSPIF = 0;                                                                                         
}//fin de la funcion i2c_start

void i2c_restart(void){
    i2c_idle();
    SSPCON2bits.RSEN = 1;
    while(SSPCON2bits.RSEN == 1);
    while(SSPIF == 0);
    SSPIF = 0;   
}//fin de la funcion i2c_restart

void i2c_stop(void){
    SSPCON2bits.PEN = 1;
    while(SSPCON2bits.PEN);
    while(SSPIF == 0);
    SSPIF = 0;
}//fin de la funcion i2c_stop

unsigned char i2c_read(void){
    i2c_idle();
    SSPCON2bits.RCEN = 1;
    while(SSPCON2bits.RCEN == 1);
    while(SSPSTATbits.BF == 0);
    return SSPBUF;
}

unsigned char i2c_write(unsigned char dato){
    i2c_idle();
    SSPBUF = dato;
    while(SSPSTAT & 0x05);
    /*
    if(SSPCON2bits.ACKSTAT == 1){
        SSPCON2bits.PEN = 1;
        return 0;
    }
    else{
        while(PIR1bits.SSPIF == 0);
        PIR1bits.SSPIF = 0;
        return 1;
    }
     * */
    return 0;
}

void i2c_sendNACK(){
    SSPCON2bits.ACKDT = 1;
    SSPCON2bits.ACKEN = 1;
    while(SSPCON2bits.ACKEN == 1);
}

void i2c_sendACK(){
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    while(SSPCON2bits.ACKEN == 1);
}
void i2c_idle(){
    while((SSPCON2 & 0x1F)|| (SSPSTAT & 0x04));
}


//SLAVE
void i2c_Slave_Init(short address) 
{
  SSPSTAT = 0x80;    
  SSPADD = 0x01; //Setting address
  SSPCONbits.SSPM = 0x06;    //As a slave device
  SSPCONbits.CKP = 1;
  SSPCONbits.SSPEN = 1;
  SSPCON2bits.SEN = 1;
  TRISBbits.TRISB0 = 1;
  TRISBbits.TRISB1 = 1;
  INTCONbits.GIE = 1;
  INTCONbits.PEIE = 1;
  PIR1bits.SSPIF = 0;
  PIE1bits.SSPIE = 1;
  
  SSPCON2 = 0x01;
  TRISC3 = 1;       //Setting as input as given in datasheet
  TRISC4 = 1;       //Setting as input as given in datasheet
  //GIE = 1;          //Global interrupt enable
  //PEIE = 1;         //Peripheral interrupt enable
  //SSPIF = 0;        //Clear interrupt flag
  //SSPIE = 1;        //Synchronous serial port interrupt enable
}