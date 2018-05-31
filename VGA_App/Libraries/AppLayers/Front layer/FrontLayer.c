/**
* @file FrontLayer.c
* @brief
* Handles commands and error's
*
* @author Remy van der Pol
* @author Erwin Blankestein
*
*/

#include "main.h"



char buffer[200];

uint16_t errorBuff[errorBuffSize];
uint8_t errorBuffindex = 0;
uint8_t verboseFlag = 1;

struct scriptStructure commandStorage[storageSize];
uint8_t commandStorageCounter = 0;


/**
*@brief \n
*Stores an error of the enum "errorcodes". It adds it to the buffer errorBuff. The amount of errors is tracked using errorBuffindex.
*Errors will only be stored if verboseFlag = 1.
*@param error		Errorcode of enum "errorcodes" type.
*@return void
*/
void addError(uint16_t error) {
	if(verboseFlag){
		if(errorBuffindex < errorBuffSize){
			errorBuff[errorBuffindex] = error;
			errorBuffindex++;
		}
	}
}


/**
*@brief \n
*Prints all the errors available in errorBuff to the serial port.
*@return void
*/
void printErrors() {
	int i = 0;
		if(!errorBuffindex && verboseFlag)
			UART_puts("OK\r\n\r\n");
		else {
			for(i=0;i<errorBuffindex;i++){

				switch(errorBuff[i]) {

				case tooManyArguments:
					UART_puts("Error: Too many arguments in command.\r\n");
					break;
				case valOutofBounds:
					UART_puts("Error: Numeric value out of bounds.\r\n");
					break;
				case unknownColor:
					UART_puts("Warning: Given color unknown. Black is used.\r\n");
					break;
				case unknownFont:
					UART_puts("Warning: Given font is unknown. Normal font is used.\r\n");
					break;
				case bufferFull:
					UART_puts("Error: Input buffer is full. Type execute to empty buffer.\r\n");
					break;
				case unknownCommand:
					UART_puts("Error: Given command is unknown.\r\n");
					break;
				case verboseOn:
					UART_puts("Info: Verbose is ON!\r\n");
					break;
				case verboseOff:
					UART_puts("Info: Verbose is OFF!\r\n");
					break;
				case outOfRange:
					UART_puts("Warning: Figure is out of the display's range.\r\n");
					break;
				case bitmapIndex:
					UART_puts("Error: Unknown bitmap.\r\n");
					break;
				}
			}

		}

	errorBuffindex=0;
}


/**
*@brief \n
*Reads data from the serial port, and processes the data.							
*@return void
*/
void getData() {

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
		addError(tooManyArguments);
	}
	printErrors();
}

/**
*@brief \n
*Splits a String using a delimiter.
*@param data		Pointer to the String that needs to be seperated.
*@param delimiter	Pointer to the String which holds the delimiter(s) used for splitting the String.
*@param dataOut		Pointer array to store the seperated Strings in.
*@param dataCount	Pointer to an integer to store the amount of Strings in dataOut after the seperation of data.
*@return errorcode	0 if succesfull, 1 if there is more data than the argumentBufSize allows.
*/
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

/**
*@brief \n
*Converts a String holding a numeric value to an integer, respecting the size of the integer.
*@param stringValue		String to convert.
*@param intValue		Integer pointer for storing the result.
*@param minAllowedVal	Minimum allowed value of intValue.
*@param maxAllowedVal	Maximum allowed value of intValue.
*@return errorcode		0 if succesfull, 1 if the numer doesn't respect the minAllowedVal or the maxAllowedVal.
*/
uint8_t stringToInt(char* stringValue, uint16_t* intValue, uint16_t minAllowedVal, uint16_t maxAllowedVal){
	char* charbuf[100];
	long int value;

	value = strtol(stringValue, charbuf, 10);

	if(value >= minAllowedVal && value <= maxAllowedVal) {
	*intValue = value;
	return(0);
	}
	else {
	return(1);
	}
}

/**
*@brief \n
*Fills the structure commandStorage with data using the index fillStructure which it gets from getType();
*@param data		Pointer array to the command data.
*@param dataCount	Amount of arguments inside data.
*@return void
*/
void fillStruct(char** data, uint8_t dataCount) {
	struct scriptStructure commandBuffer;
	struct fillStructure fillFlags;

	uint8_t type = getType(data[0], &fillFlags);
	debugPutInt(type);

	if(fillFlags.command != noValue) {
		commandBuffer.command = type;
		if(fillFlags.X != noValue) {
			if(stringToInt(data[fillFlags.X],&commandBuffer.X, 0, 65535))
				addError(valOutofBounds);
		}
		else{
			commandBuffer.X = 0;
		}
		if(fillFlags.Y != noValue){
			if(stringToInt(data[fillFlags.Y],&commandBuffer.Y, 0, 65535))
				addError(valOutofBounds);
		}
		else{
			commandBuffer.Y = 0;
		}
		if(fillFlags._X != noValue){
			if(stringToInt(data[fillFlags._X],&commandBuffer._X, 0, 65535))
				addError(valOutofBounds);
		}
		else{
			commandBuffer._X = 0;
		}
		if(fillFlags._Y != noValue){
			if(stringToInt(data[fillFlags._Y],&commandBuffer._Y, 0, 65535))
				addError(valOutofBounds);
		}
		else{
			commandBuffer._Y = 0;
		}
		if(fillFlags.opt1 != noValue){
			if(commandBuffer.command == tekst){
				if(getFont(data[fillFlags.opt1], &commandBuffer.opt1))
					addError(unknownFont);
			}
			else
				if(stringToInt(data[fillFlags.opt1],&commandBuffer.opt1, 0, 65535))
					addError(valOutofBounds);
		}
		else{
			commandBuffer.opt1 = 0;
		}
		if(fillFlags.opt2 != noValue){
			if(stringToInt(data[fillFlags.opt2],&commandBuffer.opt2, 0, 65535))
				addError(valOutofBounds);
		}
		else{
			commandBuffer.opt2 = 0;
		}
		if(fillFlags.color != noValue){
			if(getColor(data[fillFlags.color], &commandBuffer.color))
				addError(unknownColor);
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
			addError(bufferFull);
		}
	}
	else if (type != execute && type != verbose){
		addError(unknownCommand);
	}
	printCommandStruct(&commandStorage[commandStorageCounter-1]);

}


/**
*@brief \n
*Prints the given structureData. For debugging purposes (only works when DEBUG is defined);
*@param commandBuffer		Pointer to the structureData to print.
*@return void
*/
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


/**
*@brief \n
*Configures an structure to hold the index of the given command. This function also executes the commands "execute" and "verbose".
*@param data		Pointer to the first command.
*@param flags		Pointer to the index fillStructure.
*@return commandcode	Code is of enum type scriptcommands.
*/
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
	else if(!strcmp(data, "verbose")){
		flags->command = noValue;
		flags->X = noValue;
		flags->Y = noValue;
		flags->_X = noValue;
		flags->_Y = noValue;
		flags->opt1 = noValue;
		flags->opt2 = noValue;
		flags->color = noValue;
		flags->tekst = noValue;
		if(verboseFlag) {
			addError(verboseOff);
			verboseFlag = 0;
		}
		else{
			verboseFlag = 1;
			addError(verboseOn);
		}
		commandStorageCounter=0;
		return(verbose);
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



/**
*@brief \n
*Converts given String holding the requested color to an number of enum type colors.
*@param data		Pointer holding the String with the requested color.
*@param colorcode	Pointer to write the colorcode of enum type colors in.
*@return errorcode	Returns 0 if succesfull, 1 if color not defined (colorcode will be Black).
*/
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


/**
*@brief \n
*Converts given String holding the requested font to an number of enum type font.
*@param data		Pointer holding the String with the requested font.
*@param fontCode	Pointer to write the fontCode of enum type font in.
*@return errorcode	Returns 0 if succesfull, 1 if font not defined (fontCode will be normaal).
*/
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
