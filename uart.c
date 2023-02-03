#include "uart.h"
int loops= 0;

/*-------------------------- FUNCTION DEFINITIONS --------------------------*/

/*
  Discription: this function should initialize the uart0 module of tiva c according to
  the input clk and baudrate
  arguments:
  [in] uint32 clk:      the cpu clock in hz
  [in] uint32 baudrate: the baudrate that the uart should operate at
*/
void uart0_init(uint_32 clk, uint_32 baudrate){
  /*enable the clock to UART0*/
  SYSCTL_RCGCUART_R |= (1 << UART0_RCGC_BIT);
  /*enable clock for PORTA*/
  SYSCTL_RCGCGPIO_R |= (1 << GPIO_PORTA_RCGC_BIT);
  /*digital enable for PA0 PA1*/
  GPIO_PORTA_DEN_R |= (1 << 0) | (1 << 1);
  /*setting the GPIO AFSEL for porta*/
  GPIO_PORTA_AFSEL_R |= (1 << 0) | (1 << 1);
  GPIO_PORTA_PCTL_R  |= (1 <<0) | (1 << 4);
  /*Disable the UART*/
  UART0_CTL_R &= ~(1 << 0);
  /*BRD = BRDI + BRDF = UARTSysClk / (16 * Baud Rate)*/
   float_32 BRD = clk / (16.0 * baudrate);
   uint_16 BRDF = (int)((BRD - (int)BRD) * 64 + 0.5);
  /*write integer portion to UARTIBRD*/
  UART0_IBRD_R = (int) BRD; /*value should be 104 for 9600 baud*/
  /*write the fraction portion to UARTFBRD*/
  UART0_FBRD_R = BRDF; /*value should be 11*/
  /*configure the serial parameters in UARTLCRH*/
  /*
      word length = 8bit
      no parity
      1 stop bit
  */
  UART0_LCRH_R |= (1 << 6) | (1 << 5);
  UART0_LCRH_R &= ~(1 << 7) & ~(1 << 4) & ~(1<< 3);
  /*configure the uart clock source to the system clock*/
  UART0_CC_R = 0;
  /*enable UART*/
  UART0_CTL_R |= (1 << 0) | (1 << 8) | (1<<9);
	/*enable the intterupt for UART0*/
	NVIC_PRI1_R = (6 << 13) | (NVIC_PRI1_R & 0xFFFF1FFF);
	NVIC_EN0_R |= (1 << 5);
	UART0_ICR_R &= ~(1 << 4);
	UART0_IM_R |= (1 << 4);
}

/*
  Discription: sends a character(byte) through uart
  arguments:
  [in] uint8 ch:      the character to be sent by uart
*/
void uart0_putchar(uint_8 ch){
  /*wait until the transmitter has no data to transmit*/
  while(!(UART0_FR_R & (1 << 7)));
  /*insert data into the data register*/
  UART0_DR_R = (UART0_DR_R & 0xFFFFFF00) | (ch & 0x000000FF);
}
char readChar(void) {
	char c;
	while((UART0_FR_R & (1<<4)) != 0);
	c = UART0_DR_R;
	return c;
}

int printIntHelper(int i){
    int digits = 0;
    if(i > 9){
        digits = printIntHelper(i / 10);
    }
    uart0_putchar('0' + (i % 10));
    digits += 1;
    return digits;
}

int printInt(int i){
    if(i < 0){
        uart0_putchar('-');
        i *= -1;
    }
    int result = printIntHelper(i);
    return result;
}
void printChar( char c) {
while((UART0_FR_R & ( 1<<5)) !=0);
	UART0_DR_R = c;
}

/*
  Discription: sends a string through uart
  arguments:
  [in] const uint8 *str: a pointer to the string array you want to send through uart
*/
void print(const char *str){
  while(*str != '\0'){
    if(*str == '\n'){
      uart0_putchar('\r');
    }
    uart0_putchar(*str);
    str++;
  }
}

char* itoa(unsigned long long val, int base){
    loops=0;
    static char buf[32] = {0};
    int i = 31;
    for(; val && i ; --i, val /= base)
    {
        buf[i] = "0123456789abcdef"[val % base];
        loops++;
    }
    return &buf[i+1];
}  
int print_idec(int n)
{
  char* str=itoa(n,10);
  print(str);
  return loops;
}



void clear(){
	print("\033c"); // Escape sequence 
}





