void adc_init(void);
int adc_readChannel(char port);
void adc_chanSel(char chan);
int adc_start(void);

void keypad_read(void);
char keyid(int adc);
unsigned char adc0_read(char i);
unsigned char adc1_read(void);
unsigned char adc2_read(void);
void outAct(char out);
void outAct1(char lvl1);
void outAct2(char lvl2);

int adc = 0;