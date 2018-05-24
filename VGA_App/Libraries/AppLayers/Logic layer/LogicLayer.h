/*
 * LogicLayer.h
 *
 *  Created on: 3 mei 2018
 *      Author: Remyv
 */

#ifndef APPLAYERS_LOGIC_LAYER_LOGICLAYER_H_
#define APPLAYERS_LOGIC_LAYER_LOGICLAYER_H_


void executeScript(struct scriptStructure* storage, uint8_t dataSize);

extern void addError(uint16_t error);

extern void UB_VGA_FillScreen(uint8_t color);
extern void DrawLine(uint16_t *DrawError, int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color, int8_t width);
extern void DrawLineNeg(int16_t x,int16_t y,int16_t x1, int16_t y1, uint8_t color, int8_t width);
extern void DrawLinePos(int16_t x,int16_t y,int16_t x1, int16_t y1, uint8_t color, int8_t width);
extern void DrawRect(uint16_t *DrawError, int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color);
extern void DrawTriangle(uint16_t *DrawError, int16_t x, int16_t y, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int8_t color);
extern void DrawEllips(uint16_t *DrawError, int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color);
extern void Drawbitmap(uint16_t *DrawError, int16_t x,int16_t y,int16_t sel);
extern void Drawtext(uint16_t *DrawError, char* tekst, int16_t x,int16_t y, uint8_t color, uint8_t style);
extern uint8_t drawchar(uint16_t *DrawError, char symbol, int16_t x,int16_t y, uint8_t color, uint8_t style);

#endif /* APPLAYERS_LOGIC_LAYER_LOGICLAYER_H_ */
