/*
 * FrontLayer.c
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */

#include "main.h"

struct scriptStructure {
	uint8_t command;
	uint16_t X;
	uint16_t Y;
	uint16_t _X;
	uint16_t _Y;
	uint16_t opt1;
	uint16_t opt2;
	uint8_t color;
	char tekst[100];
};

char buffer[200];

struct scriptStructure command;


uint8_t getData() {

	char *data[10];
	uint8_t dataCount;

	UART_read(buffer, 0);

	if(stringSplit(buffer, ",", data, &dataCount) != 1) {
		int i = 0;
		for(i=0;i<dataCount; i++){
			UART_puts(data[i]);
			UART_puts("\r\n");
		}
	}
	else{
		UART_puts("Too many arguments.");
	}

}


uint8_t stringSplit(char* data, char *delimiter, char **dataOut, uint8_t *dataCount) {
	char* cPtr;
	int i = 0;
	cPtr = strtok(data, delimiter);
	while(cPtr != NULL){
	dataOut[i] = cPtr;
		i++;
		cPtr = strtok(NULL, delimiter);
		if(i>9) {
			*dataCount = 10;
		return(1);
		}
		*dataCount = i;
	}
	return(0);
}











