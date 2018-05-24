/*
 * main.h
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */

#ifndef MAIN_H_
#define MAIN_H_

//#define DEBUG

//System library's
#include "stm32f4xx.h"

// Layer library's
#include "FrontLayer.h"
#include "LogicLayer.h"
#include "IO-Layer.h"


void debugPuts(char* message);
void debugPutInt(int number);
void checkColors();

extern void UARTinit(void);


#define WAIT_FOREVER 0
#define TRUE		 1
#define FALSE		 0


#endif /* MAIN_H_ */
