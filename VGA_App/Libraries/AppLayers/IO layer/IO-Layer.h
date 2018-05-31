/**
* @file IO-Layer.h
* @brief
* contains the prototypes and Includes for IO-Layer.c
*
*
* @author Remy van der Pol
* @author Erwin Blankestein
*
*/

#ifndef APPLAYERS_IO_LAYER_IO_LAYER_H_
#define APPLAYERS_IO_LAYER_IO_LAYER_H_

uint32_t G_CLK;
uint32_t D_uS; // Global variable (us)
uint32_t D_mS; // Global variable (ms)
uint32_t D_S; // Global variable (s)

#define CR 13 // carriage return char
#define LF 10 // linefeed char

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>

// System library's
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"


#include "API_io.h"


void UART_init(void);
void UART_putchar(char c);
void UART_puts(char *s);
void UART_putnum(unsigned int num, unsigned char deel);
void UART_putint(unsigned int num);
char UART_readChar(void);
void UART_read(char *s, int echo);
uint8_t UART_dataAvailable(void);
void VGA_init(void);

void DELAY_init(void);
void DELAY_us(unsigned int x);
void DELAY_ms(unsigned int x);
void DELAY_s(unsigned int x);



#endif /* APPLAYERS_IO_LAYER_IO_LAYER_H_ */
