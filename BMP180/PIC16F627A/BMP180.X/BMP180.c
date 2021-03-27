#include "BMP180.h"
#include <stdio.h>
#include "configuracion.h"
#include "I2C.h"
#include "LCD.h"
int adressR = 0xEF;
int adressW = 0xEE;
long dataEprom[11] = {0};


void BMP180_init(void){
    char lowReg = 0xAA;
    i2c_init();
    i2c_start();            //Señal de inicio
    i2c_write(adressW);     //Comando de escritura
    i2c_write(lowReg);        //Direccion de lectura
    i2c_restart();          //Señal de reinicio
    i2c_write(adressR);     //Comando de lectura
    
    for(int i = 0; i < 11;i++){
        char aux[2];
        for(int j = 0; j < 2;j++){
            aux[j] = i2c_read();
            if(i == 10 && j == 1){
                i2c_sendNACK();
                i2c_stop();
            }
            else{
                i2c_sendACK();
            }
            dataEprom[i] = (aux[0] << 8)|(aux[1]);
        }
    }
}

long BMP180_readTemperature(void){
    int temp[2];
    char buffer[25];
    //Señal de inicio de temperatura
    i2c_start();
    i2c_write(adressW);         //Byte de control
    i2c_write(0xF4);            //Direccion de memeria
    i2c_write(0x2E);            //Dato
    BMP180_wait();              //Esperar 4.5 ms
    i2c_sendNACK();
    i2c_stop();
    //Lectura de los registro 0xF6 y 0xF7
    i2c_start();
    i2c_write(adressW);
    i2c_write(0xF6);
    i2c_restart();
    i2c_write(adressR);
    temp[0]=i2c_read();
    i2c_sendACK();
    temp[1]=i2c_read();
    i2c_sendNACK();
    i2c_stop();
    //Conversion a entero
    long T = (long)(temp[0] * 256) + temp[1];//27898;
    //Calcular la temperatura real

    x1 = ((T - dataEprom[5])* dataEprom[4])/(32768);        //Bien
    x2 = (2048 * dataEprom[9])/(x1 + dataEprom[10]);
    B5 = x1 + x2;
    te =((B5 + 8)/16)/10;
    return te;
}

long BMP180_readPreassure(void){
    long p1 = 0;              //80 - 48 = 32
    int p2 = 0;
    char p3 = 0;
    //Señal de inicio de temperatura
    i2c_start();
    i2c_write(adressW);         //Byte de control
    i2c_write(0xF4);            //Direccion de memeria
    i2c_write(0x34);            //Dato
    BMP180_wait();              //Esperar 4.5 ms
    i2c_sendNACK();
    i2c_stop();
    //Lectura de los registro 0xF6 y 0xF7
    i2c_start();
    i2c_write(adressW);
    i2c_write(0xF6);
    i2c_restart();
    i2c_write(adressR);
    p1 = i2c_read();
    i2c_sendACK();
    p2 = i2c_read();
    i2c_sendACK();
    p3 = i2c_read();
    i2c_sendNACK();
    i2c_stop();                  //Señal de paro
    //Conversion a entero
    long B3, B6,x1,x2,x3, B4, p;
    unsigned long B7;
    //B5 = 2399;
    long pres = p1 * 256 + p2 + p3 / 256;
    B6 = B5 - 4000;                 //correcto
    x1 = (dataEprom[7]*B6*B6) /(long)(4096*2048);
    x2 = dataEprom[1] * B6 / 2048;
    x3 = x1 + x2;
    B3 =(((dataEprom[0]* 4 + x3))+ 2)/4;
    x1 = (dataEprom[2]*B6)/8192;
    x2 = (dataEprom[6]*((B6*B6)/4096))/65536;
    x3 = ((x1 + x2) + 2) / 4;
    printf("x3 = %ld\n",x3);
    B4 = (dataEprom[3] * (unsigned long)(x3 + 32768)) / 32768;
    B7 = ((unsigned long)pres - B3)*(50000);
    if(B7 < 0x80000000){
        p = (long)((B7*2)/B4);
    }
    else{
        p = (long)((B7/B4)*2);
    }

    x1 = (p/256)*(p/256);
    x1 = (x1 * 3038)/65536;
    x2 = (-7357 * p)/ 65536;
    p = p + (x1 + x2 +3791)/16;
    return p;
 /* 
    long pres = ((p1 << 16)|((p2 << 8))|p3) >> (8);
    B6 = B5 - 4000;
    x1 = (dataEprom[7]*(B6 * B6 / 4096))/ 2048;
    x2 = dataEprom[1] * B6 / 2048;
    x3 = x1 + x2;
    B3 =(((dataEprom[0]* 4 + x3))+ 2)/4;
    x1 = (dataEprom[2]*B6)/8192;
    x2 = (dataEprom[4]*(B6 * B6 / 4096))/65536;
    x3 = ((x1 + x2) + 2) / 4;
    B4 = (dataEprom[3] * (unsigned long)(x3 + 32768)) / 32768;
    B7 = ((unsigned long)pres - B3)*(50000);
    if(B7 < 0x80000000){
        p = (B7*2)/B4;
    }
    else{
        p = (B7/B4)*2;
    }
    x1 = (p/256)*(p/256);
    x1 = (x1 * 3038)/65536;
    x2 = (-7357 * p)/ 65536;
    p = p + (x1 + x2 +3791)/16;
    return x2; */
    //return 0;
}

void BMP180_wait(){
    __delay_ms(5);
}

/*void i2c_coeficiente(void){
    char buf[20]; 
    for(int i = 0; i < 11; i++){
        sprintf(buf,"d = %d", dataEprom[i]);
        lcd_string(buf);
        __delay_ms(1000);
        lcd_clear();
    }
}*/
