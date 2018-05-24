/*
 * LogicLayer.c
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */


#include "main.h"

uint8_t backgroundColor = zwart;

void executeScript(struct scriptStructure* storage, uint8_t dataSize) {
int i = 0;
uint16_t errorValue = 0;

	for (i=0;i<dataSize;i++){
		switch(storage->command) {

		case lijn:
			DrawLine(&errorValue, storage->X, storage->Y, storage->_X, storage->_Y,
					storage->color, storage->opt1);
			break;
		case ellips:
			DrawEllips(&errorValue, storage->X, storage->Y, storage->_X, storage->_Y,
					storage->color);
			break;
		case rechthoek:
			DrawRect(&errorValue, storage->X, storage->Y, storage->_X, storage->_Y,
					storage->color);
			break;
		case driehoek:
			DrawTriangle(&errorValue, storage->X, storage->Y, storage->_X, storage->_Y,
					storage->opt1, storage->opt2, storage->color);
			break;
		case tekst:
			Drawtext(&errorValue, storage->tekst, storage->X, storage->Y, storage->color, storage->opt1);
			break;
		case bitmap:
			Drawbitmap(&errorValue, storage->X, storage->Y, storage->opt1);
			break;
		case clearscherm:
			UB_VGA_FillScreen(storage->color);
			backgroundColor = storage->color;
			break;
		case wacht:
			DELAY_ms(storage->opt1);
			break;
		default:

			break;
		}

		if(errorValue) {
			addError(errorValue);
		}

		storage++;
	}
}
