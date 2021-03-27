void BMP180_init(void);
long BMP180_readTemperature(void);
long BMP180_readPreassure(void);
void BMP180_startTemperture(void);
void BMP180_startPresure(void);
void BMP180_wait(void);
void i2c_coeficiente(void);

// B5 es entero

long x1,x2,B5,te;
