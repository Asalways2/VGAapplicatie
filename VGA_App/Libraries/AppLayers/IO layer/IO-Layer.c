/*
 * IO-Layer.c
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */

#include "main.h"

char string[100];
int charcounter = 0;


void VGA_init() {
	UB_VGA_Screen_Init();
}


void UARTinit(void)
{

  /* --------------------------- System Clocks Configuration -----------------*/
  /* USART2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  /* GPIOA clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  /*-------------------------- GPIO Configuration ----------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect USART pins to AF */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);   // USART2_TX
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);  // USART2_RX

  USART_InitTypeDef USART_InitStructure;

/* USARTx configuration ------------------------------------------------------*/
/* USARTx configured as follow:
      - BaudRate = 115200 baud
      - Word Length = 8 Bits
      - One Stop Bit
      - No parity
      - Hardware flow control disabled (RTS and CTS signals)
      - Receive and transmit enabled
*/
USART_InitStructure.USART_BaudRate = 115200;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

USART_Init(USART2, &USART_InitStructure);
USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

USART_Cmd(USART2, ENABLE);

}

void UART_putchar(char c)
{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
		USART_SendData(USART2, c);

}

void UART_puts(char *s)
{
	volatile unsigned int i;
	for (i=0; s[i]; i++)
	{
		UART_putchar(s[i]);
		//while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
		//USART_SendData(USART2, s[i]);
	}
}


// Stuurt meegegeven getal uit op de UART

void UART_putint(unsigned int num)
{
    UART_putnum(num, 10);
}

// Stuurt meegegeven getal uit op de UART in het aangegeven getallenstelsel
void UART_putnum(unsigned int num, unsigned char deel)
{
    static unsigned char chars[16] = "0123456789ABCDEF";
    unsigned int rest;
    signed char c[16];
    signed int i=15;

    // Zet de integer om naar een string
    if(num==0)
    {
        c[i]='0';
        i--;
    }
    else
    {
        while(num>0)
        {
            rest=num%deel;
            num/=deel;
            c[i]=chars[rest];
            i--;

            if(i==0) // it ends here
                num=0;
        }
    }
    // Stuur de string uit
    while(i<15)
    {
        i++;
        // Wacht tot de buffer leeg is
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
        USART_SendData(USART2, c[i]);
    }
}

// Ontvang een karakter via de UART
// niet echt nodig als routine maar als wrapper voor compatabiliteit. Let op geen -1 als er geen char is ontvangen!

char UART_readChar(void)
{
    char uart_char = -1;
    if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)== SET)  // check for data available
    	 uart_char= USART2->DR & 0xFF; // and read the data from peripheral
    return uart_char;
}


// void UART_gets
// args: char *readbuffer
//       int   echo, when TRUE, send read-char to UART
// remark: ARM sends -1 if buffer is empty
//         LF is cleared if set in terminal-program
void UART_read(char *s, int echo)
{
	while (TRUE)
	{
	 	*s = UART_readChar();

	 	if (*s==-1)             // check for data available
	 		continue;

	 	if (*s==0xff || *s==LF) // if no data or LF, continue
			continue;

		if (echo)              // if output-flag set
			UART_putchar(*s);  // to read what u entered

		if (*s==CR)            // if enter pressed
		{
			*s = '\0';         // ignore char and close string
		    return;            // buf ready, exit loop
		}
		s++;
	}
}

uint8_t UART_dataAvailable() {
	return(USART_GetFlagStatus(USART2, USART_FLAG_RXNE)); // check for data available
}


void DELAY_init(void)
{
	RCC_ClocksTypeDef Clocks;
	RCC_GetClocksFreq(&Clocks);
	G_CLK = Clocks.SYSCLK_Frequency;	// Read the systemclock
	D_S  = (G_CLK*1.25)/9/2;	// Number of instructions in one second
	D_mS = (G_CLK*1.25)/9000/2; // Number of instructions in one millisecond
	D_uS = (G_CLK*1.25)/9000000/2; // Number of instructions in one microsecond, largest rounding error
}

void DELAY_us(volatile unsigned int time)
{
    volatile unsigned int i;

    while(time>0)		// Run x times 1 microsecond
    {
        for(i=0;i<D_uS;i++);
        time--;
    }
}

void DELAY_ms(volatile unsigned int time)
{
    volatile unsigned int i;

    while(time>0)		// Run x times 1 millisecond
    {
        for(i=0;i<D_mS;i++);
        time--;
    }
}

void DELAY_s(volatile unsigned int time)
{
    volatile unsigned int i;

    while(time>0)		// Run x times 1 second
    {
        for(i=0;i<D_S;i++);
        time--;
    }
}
