/*
 * LogicLayer.c
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */


#include "main.h"


void executeScript(struct scriptStructure* storage, uint8_t dataSize) {
int i = 0;

	for (i=0;i<dataSize;i++){
		switch(storage->command) {

		case lijn:
			DrawLine(storage->X, storage->Y, storage->_X, storage->_Y,
					storage->color, storage->opt1);
			break;
		default:

			break;
		}
		storage++;
	}
}
