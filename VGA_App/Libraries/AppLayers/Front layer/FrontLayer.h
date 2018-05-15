/*
 * FrontLayer.h
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */

#ifndef APPLAYERS_FRONT_LAYER_FRONTLAYER_H_
#define APPLAYERS_FRONT_LAYER_FRONTLAYER_H_

#include <string.h>

#define seperator ','

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


uint8_t getData(void);
uint8_t stringSplit(char* data, char *delimiter, char **dataOut, uint8_t *dataCount);


#endif /* APPLAYERS_FRONT_LAYER_FRONTLAYER_H_ */
