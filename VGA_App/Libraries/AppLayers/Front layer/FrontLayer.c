/*
 * FrontLayer.c
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */

#include "main.h"



char buffer[200];

struct scriptStructure commandStorage[storageSize];
uint8_t commandStorageCounter = 0;


uint8_t getData() { //need to add error return type

	char *data[argumentBufSize]; //see Frontlayer.h
	uint8_t dataCount;

	UART_read(buffer, 0);

	if(stringSplit(buffer, ",", data, &dataCount) != 1) {
		int i = 0;
		for(i=0;i<dataCount; i++){
			debugPuts(data[i]);
			debugPuts("\r\n");
		}
		fillStruct(data, dataCount);
	}
	else{
		debugPuts("Too many arguments.");
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
		if(i>argumentBufSize-1) {
			*dataCount = argumentBufSize;
		return(1);
		}
		*dataCount = i;
	}
	return(0);
}

uint8_t stringToInt(char* stringValue, uint16_t* intValue, uint16_t minAllowedVal, uint16_t maxAllowedVal){
	char* charbuf[100];
	long int value;

	value = strtol(stringValue, charbuf, 10);

	if(value >= minAllowedVal && value <= maxAllowedVal) {
	*intValue = value;
	return(0);
	}
	else {
	return(1); //error value
	}
}


uint8_t fillStruct(char** data, uint8_t dataCount) {
	struct scriptStructure commandBuffer;
	struct fillStructure fillFlags;

	uint8_t type = getType(data[0], &fillFlags);
	debugPutInt(type);

	if(fillFlags.command != noValue) {
		commandBuffer.command = type;
		if(fillFlags.X != noValue) {
		stringToInt(data[fillFlags.X],&commandBuffer.X, 0, 65535);
		}
		else{
			commandBuffer.X = 0;
		}
		if(fillFlags.Y != noValue){
			stringToInt(data[fillFlags.Y],&commandBuffer.Y, 0, 65535);
		}
		else{
			commandBuffer.Y = 0;
		}
		if(fillFlags._X != noValue){
			stringToInt(data[fillFlags._X],&commandBuffer._X, 0, 65535);
		}
		else{
			commandBuffer._X = 0;
		}
		if(fillFlags._Y != noValue){
			stringToInt(data[fillFlags._Y],&commandBuffer._Y, 0, 65535);
		}
		else{
			commandBuffer._Y = 0;
		}
		if(fillFlags.opt1 != noValue){
			if(commandBuffer.command == tekst)
				getFont(data[fillFlags.opt1], &commandBuffer.opt1);
			else
			stringToInt(data[fillFlags.opt1],&commandBuffer.opt1, 0, 65535);
		}
		else{
			commandBuffer.opt1 = 0;
		}
		if(fillFlags.opt2 != noValue){
			stringToInt(data[fillFlags.opt2],&commandBuffer.opt2, 0, 65535);
		}
		else{
			commandBuffer.opt2 = 0;
		}
		if(fillFlags.color != noValue){
			getColor(data[fillFlags.color], &commandBuffer.color);
		}
		else{
			commandBuffer.color = 0;
		}
		if(fillFlags.tekst != noValue){
			strcpy(commandBuffer.tekst, data[fillFlags.tekst]);
		}


		if(commandStorageCounter < storageSize) {
			memcpy(&commandStorage[commandStorageCounter], &commandBuffer, sizeof commandBuffer);
			commandStorageCounter++;
		}
		else{
			debugPuts("\r\nBuffer full.\r\n");
		}
	}
	printCommandStruct(&commandStorage[commandStorageCounter-1]);

}

void printCommandStruct(struct scriptStructure* commandBuffer){

	debugPuts("\r\n\r\nX:");
	debugPutInt(commandBuffer->X);
	debugPuts("\r\n");
	debugPuts("Y:");
	debugPutInt(commandBuffer->Y);
	debugPuts("\r\n");
	debugPuts("_X:");
	debugPutInt(commandBuffer->_X);
	debugPuts("\r\n");
	debugPuts("_Y:");
	debugPutInt(commandBuffer->_Y);
	debugPuts("\r\n");
	debugPuts("opt1:");
	debugPutInt(commandBuffer->opt1);
	debugPuts("\r\n");
	debugPuts("opt2:");
	debugPutInt(commandBuffer->opt2);
	debugPuts("\r\n");
	debugPuts("color:");
	debugPutInt(commandBuffer->color);
	debugPuts("\r\n");
	debugPuts("tekst:");
	debugPuts(commandBuffer->tekst);
	debugPuts("\r\n\r\n");

}

uint8_t getType(char* data, struct fillStructure* flags){

	if(!strcmp(data, "lijn")) {
		flags->command = 0;
		flags->X = 1;
		flags->Y = 2;
		flags->_X = 3;
		flags->_Y = 4;
		flags->opt1 = 5;
		flags->opt2 = noValue;
		flags->color = 6;
		flags->tekst = noValue;
		return(lijn);
	}
	else if(!strcmp(data, "ellips")){
		flags->command = 0;
		flags->X = 1;
		flags->Y = 2;
		flags->_X = 3;
		flags->_Y = 4;
		flags->opt1 = noValue;
		flags->opt2 = noValue;
		flags->color = 5;
		flags->tekst = noValue;
		return(ellips);
	}
	else if(!strcmp(data, "rechthoek")){
		flags->command = 0;
		flags->X = 1;
		flags->Y = 2;
		flags->_X = 3;
		flags->_Y = 4;
		flags->opt1 = noValue;
		flags->opt2 = noValue;
		flags->color = 5;
		flags->tekst = noValue;
		return(rechthoek);
	}
	else if(!strcmp(data, "driehoek")){
		flags->command = 0;
		flags->X = 1;
		flags->Y = 2;
		flags->_X = 3;
		flags->_Y = 4;
		flags->opt1 = 5;
		flags->opt2 = 6;
		flags->color = 7;
		flags->tekst = noValue;
		return(driehoek);
	}
	else if(!strcmp(data, "bitmap")){
		flags->command = 0;
		flags->X = 2;
		flags->Y = 3;
		flags->_X = noValue;
		flags->_Y = noValue;
		flags->opt1 = 1;
		flags->opt2 = noValue;
		flags->color = noValue;
		flags->tekst = noValue;
		return(bitmap);
	}
	else if(!strcmp(data, "tekst")){
		flags->command = 0;
		flags->X = 1;
		flags->Y = 2;
		flags->_X = noValue;
		flags->_Y = noValue;
		flags->opt1 = 5;
		flags->opt2 = noValue;
		flags->color = 4;
		flags->tekst = 3;
		return(tekst);
	}
	else if(!strcmp(data, "clearscherm")){
		flags->command = 0;
		flags->X = noValue;
		flags->Y = noValue;
		flags->_X = noValue;
		flags->_Y = noValue;
		flags->opt1 = noValue;
		flags->opt2 = noValue;
		flags->color = 1;
		flags->tekst = noValue;
		return(clearscherm);
	}
	else if(!strcmp(data, "wacht")){
		flags->command = 0;
		flags->X = noValue;
		flags->Y = noValue;
		flags->_X = noValue;
		flags->_Y = noValue;
		flags->opt1 = 1;
		flags->opt2 = noValue;
		flags->color = noValue;
		flags->tekst = noValue;
		return(wacht);
	}
	else if(!strcmp(data, "execute")){
		flags->command = noValue;
		flags->X = noValue;
		flags->Y = noValue;
		flags->_X = noValue;
		flags->_Y = noValue;
		flags->opt1 = noValue;
		flags->opt2 = noValue;
		flags->color = noValue;
		flags->tekst = noValue;
		executeScript(commandStorage, commandStorageCounter);
		commandStorageCounter=0;
		return(execute);
	}
	else{
		flags->command = noValue;
		flags->X = noValue;
		flags->Y = noValue;
		flags->_X = noValue;
		flags->_Y = noValue;
		flags->opt1 = noValue;
		flags->opt2 = noValue;
		flags->color = noValue;
		flags->tekst = noValue;
		return(noValue); //change to corresponding error code
	}
}

uint8_t getColor(char* data, uint8_t *colorcode){
	if(!strcmp(data, "zwart")) {
		*colorcode = zwart;
		}
	else if(!strcmp(data, "blauw")){
		*colorcode = blauw;
		}
	else if(!strcmp(data, "lichtblauw")){
		*colorcode = lichtblauw;
		}
	else if(!strcmp(data, "groen")){
		*colorcode = groen;
		}
	else if(!strcmp(data, "lichtgroen")){
		*colorcode = lichtgroen;
		}
	else if(!strcmp(data, "cyaan")){
		*colorcode = cyaan;
		}
	else if(!strcmp(data, "lichtcyaan")){
		*colorcode = lichtcyaan;
		}
	else if(!strcmp(data, "rood")){
		*colorcode = rood;
		}
	else if(!strcmp(data, "lichtrood")){
		*colorcode = lichtrood;
		}
	else if(!strcmp(data, "magenta")){
		*colorcode = magenta;
		}
	else if(!strcmp(data, "lichtmagenta")){
		*colorcode = lichtmagenta;
		}
	else if(!strcmp(data, "bruin")){
		*colorcode = bruin;
		}
	else if(!strcmp(data, "geel")){
		*colorcode = geel;
		}
	else if(!strcmp(data, "grijs")){
		*colorcode = grijs;
		}
	else if(!strcmp(data, "wit")){
		*colorcode = wit;
		}
	else{
		*colorcode = zwart;
		return(1); //errorcode
		}
	return(0);
}

uint8_t getFont(char* data, uint16_t *fontCode) {
	if(!strcmp(data, "norm")) {
		*fontCode = normaal;
		}
	else if(!strcmp(data, "vet")){
		*fontCode = vet;
		}
	else if(!strcmp(data, "cursief")){
		*fontCode = cursief;
		}
	else{
		*fontCode = normaal;
	return(1); //errorcode
	}
	return(0);
}



