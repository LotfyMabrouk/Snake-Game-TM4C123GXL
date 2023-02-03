
#ifndef UART_H
#define UART_H
/*--------------------------------- INCLUDES---------------------------------*/
#include "std_types.h"
#include "tm4c123gh6pm_registers.h"
/*--------------------- Definitions and configurations ----------------------*/
#define UART0_RCGC_BIT                  (0)
#define GPIO_PORTA_RCGC_BIT             (0)

/*--------------------- Extern Module shared global variables ---------------*/
/*---------------------------------- ENUMS ----------------------------------*/
/*-------------------------- Structures and unions --------------------------*/
/*--------------------------- FUNCTION-LIKE MACROS --------------------------*/
/*-------------------------- FUNCTION PROTOTYPES----------------------------*/
void uart0_init(uint_32 clk, uint_32 baudrate);
void uart0_putchar(uint_8 c);
void print(const char *str);
int print_idec_helper(int n);
int print_idec(int n);
void clear();
uint_32 print_ihex(uint_32 n);
uint_32 print_ibin(uint_32 n);

#endif 
