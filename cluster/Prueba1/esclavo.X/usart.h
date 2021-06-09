void usart_init(long BAUD);
void usart_Tx(char send);
char usart_Rx(void);
void usart_TxStr(char *str);
void recivedCMD(unsigned char *cmd);
//void putch(unsigned char byte);
//unsigned char getche();
