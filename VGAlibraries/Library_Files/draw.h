//@file
//@brief This file is marvelous.

#include "api_io.h"

#include "stdlib.h"
#include <math.h>
#include "bitmap.h"
#include "FontRegular.h"
#include "FontItalic.h"
#include "FontBold.h"

uint16_t DrawError = 0;

enum DrawErrors {
	OUTOFRANGE = 100,
	BITMAPINDEX
};
void UB_VGA_FillScreen(uint8_t color);
void DrawLine(uint16_t *DrawError, int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color, int8_t width);
void DrawLineNeg(int16_t x,int16_t y,int16_t x1, int16_t y1, uint8_t color, int8_t width);
void DrawLinePos(int16_t x,int16_t y,int16_t x1, int16_t y1, uint8_t color, int8_t width);
void DrawRect(uint16_t *DrawError,int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color);
void DrawTriangle(uint16_t *DrawError,int16_t x, int16_t y, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int8_t color);
void DrawEllips(uint16_t *DrawError,int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color);
void Drawbitmap(uint16_t *DrawError,int16_t x,int16_t y,int16_t sel);
void Drawtext(uint16_t *DrawError,char* tekst, int16_t x,int16_t y, uint8_t color, uint8_t style);
uint8_t drawchar(uint16_t *DrawError,char symbol, int16_t x,int16_t y, uint8_t color, uint8_t style);
