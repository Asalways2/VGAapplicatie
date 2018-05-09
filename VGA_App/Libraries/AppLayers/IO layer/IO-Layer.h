/*
 * IO-Layer.h
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */

#ifndef APPLAYERS_IO_LAYER_IO_LAYER_H_
#define APPLAYERS_IO_LAYER_IO_LAYER_H_

#define CR 13 // carriage return char
#define LF 10 // linefeed char

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>

// System library's
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

void UART_init(void);
void UART_putchar(char c);
void UART_puts(char *s);
void UART_putnum(unsigned int num, unsigned char deel);
void UART_putint(unsigned int num);
char UART_readChar(void);
void UART_read(char *s, int echo);

#endif /* APPLAYERS_IO_LAYER_IO_LAYER_H_ */
