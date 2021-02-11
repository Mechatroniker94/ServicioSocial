#include "BMP180.h"
#include "configuracion.h"
#include "I2C.h"

int adressR = 0xEF;
int adressW = 0xEE;

int dataEprom[20] = {0};

void BMP180_init(void){
    char lowReg = 0xAA;
    char highReg = 0xBF;
    char datoLeido = 0x00;
    i2c_init();
    i2c_start();
    i2c_write(adressW);
    i2c_write(0xAA);
    i2c_start();
    i2c_write(adressR);
    //for(int i = 0;)
    datoLeido = i2c_read();
    i2c_sendNACK();
    PORTD = datoLeido; 
    //read(registros)
    
    for(int  i = lowReg; lowReg < highReg;i++){
        //Read Data
    }
    //Iniciar el I2C
    
    //Lectura data calibration
    
}

char BMP180_readTemperature(void){
    //Señal de inicio
    i2c_start();
    i2c_write(adressW);         //Byte de control
    i2c_write(0xF4);            //Direccion de memeria
    i2c_write(0x2E);            //Dato
    BMP180_wait();              //Esperar 4.5 ms
    //Leer registro 0xF6
    //Leer registro 0xF7
    i2c_stop();                  //Señal de paro
}

char BMP180_readPreassure(void){
    
    
    
    
}

void BMP180_wait(){
    
    
}

