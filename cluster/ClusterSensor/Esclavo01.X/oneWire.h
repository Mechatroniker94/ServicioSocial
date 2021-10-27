char DHT11_read(void);
void DHT11_start(void);
void slaveRespond(void);
char DHT11_readByte(void);
char *DHT11_readData(char *data);
void drive_OW_low(void);
void drive_OW_high(void);


#define onePin PORTDbits.RD7
char measure[20];