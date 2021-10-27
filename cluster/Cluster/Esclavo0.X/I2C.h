void i2c_init(void);
void i2c_start(void);
void i2c_restart(void);
void i2c_stop(void);
unsigned char i2c_read(void);
unsigned char i2c_write(unsigned char dato);
void i2c_idle(void);
void i2c_sendNACK(void);
void i2c_sendACK(void);
void i2c_Slave_Init(short address);

char lectura = 0;