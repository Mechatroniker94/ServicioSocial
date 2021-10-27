
void usart_init(long BAUD);
void usart_Tx(char send);
char usart_Rx(void);
void usart_TxStr(char *str);
void recivedCMD(char *cmd);

void usart_Interrupt(void);
void token (char *cmd);
void put(unsigned char byte);
unsigned char get1();

char *dir[3];
