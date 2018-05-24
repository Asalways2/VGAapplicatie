/*
 * FrontLayer.h
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */

#ifndef APPLAYERS_FRONT_LAYER_FRONTLAYER_H_
#define APPLAYERS_FRONT_LAYER_FRONTLAYER_H_

#include <string.h>
#include <stdlib.h>

#define seperator ','
#define argumentBufSize 10
#define noValue 255
#define storageSize 50

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

struct fillStructure {
	uint8_t command;
	uint8_t X;
	uint8_t Y;
	uint8_t _X;
	uint8_t _Y;
	uint8_t opt1;
	uint8_t opt2;
	uint8_t color;
	uint8_t tekst;
};

enum scriptcommands {
	lijn,
	ellips,
	rechthoek,
	driehoek,
	tekst,
	bitmap,
	clearscherm,
	wacht,
	execute
};

enum colors {
	zwart 			= 0b00000000,
	blauw 			= 0b00000011,
	lichtblauw 		= 0b01101111,
	groen 			= 0b00011100,
	lichtgroen 		= 0b01111101,
	cyaan 			= 0b00011111,
	lichtcyaan	 	= 0b01111111,
	rood 			= 0b11100000,
	lichtrood	 	= 0b11101101,
	magenta 		= 0b11100011,
	lichtmagenta 	= 0b11101111,
	bruin 			= 0b01000100,
	geel 			= 0b11111100,
	grijs 			= 0b01101110,
	wit 			= 0xFF
};

enum font {
	normaal,
	cursief,
	vet

};


uint8_t getData(void);
uint8_t stringSplit(char* data, char *delimiter, char **dataOut, uint8_t *dataCount);
uint8_t fillStruct(char** data, uint8_t dataCount);
uint8_t getType(char* data, struct fillStructure* flags);
uint8_t getColor(char* data, uint8_t *colorcode);
uint8_t stringToInt(char* stringValue, uint16_t* intValue, uint16_t minAllowedVal, uint16_t maxAllowedVal);
uint8_t getFont(char* data, uint16_t *fontCode);

void printCommandStruct(struct scriptStructure* commandBuffer);

#endif /* APPLAYERS_FRONT_LAYER_FRONTLAYER_H_ */
