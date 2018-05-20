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
	clearscreen,
	wacht,
	execute
};

enum colors {
	zwart = 0b00000000,
	blauw = 0b00000011,
	lichtblauw = 0x00,
	groen = 0b00011100,
	lichtgroen = 0x00,
	cyaan = 0x1F,
	lichtcyaan = 0x00,
	rood = 0b11100000,
	lichtrood = 0x00,
	magenta = 0xE3,
	lichtmagenta = 0x00,
	bruin = 0x00,
	geel = 0xFC,
	grijs = 0x00,
	wit = 0xFF
};


uint8_t getData(void);
uint8_t stringSplit(char* data, char *delimiter, char **dataOut, uint8_t *dataCount);
uint8_t fillStruct(char** data, uint8_t dataCount);
uint8_t getType(char* data, struct fillStructure* flags);
uint8_t getColor(char* data, uint8_t *colorcode);
uint8_t stringToInt(char* stringValue, uint16_t* intValue, uint16_t minAllowedVal, uint16_t maxAllowedVal);

void printCommandStruct(struct scriptStructure* commandBuffer);

#endif /* APPLAYERS_FRONT_LAYER_FRONTLAYER_H_ */
