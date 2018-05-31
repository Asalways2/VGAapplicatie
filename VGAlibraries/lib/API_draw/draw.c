/**
* @file draw.c
* @brief
* This c file contains all the draw functions for the VGA Screen
*
*
* @author Remy van der Pol
* @author Erwin Blankestein
*
*/


#include "draw.h"

/**
*@brief \n this function fills the whole screen with one color(8bits)
*@param color 8 bit color look at *macros* for premade colors
*
*
*
*/
void UB_VGA_FillScreen(uint8_t color)
{
  uint16_t xp,yp;
  for(yp=0;yp<VGA_DISPLAY_Y;yp++) {
    for(xp=0;xp<VGA_DISPLAY_X;xp++) {
      UB_VGA_SetPixel(xp,yp,color);
    }
  }
}
/**
*
*@brief \n
*<B>PRIVATE FUNCTION</B><br><br>
*this function is called by **Drawline()**.<br>
*Use DrawLine()!
*/
void DrawLinePos(int16_t x,int16_t y,int16_t x1, int16_t y1, uint8_t color, int8_t width)
{
	int16_t dx = x1 - x;
	int16_t dy = y1 - y;
	int16_t xstep = 1;
	int8_t j = 0;
	if(dx < 0)
	{
		xstep = -1;
		dx *=-1;
	}
	int16_t D = 2*dy - dx;

	for(int i = y; i<=y1; i++)
	{


		if(D > 0)
		{
			x += xstep;
			D -= 2*dy;
			//printf("Da %d \n",D);
		}

		for(j = 0; j<=width; j++)
		{
			UB_VGA_SetPixel(x+j,i,color);
		}
		D += 2*dx;
	}
}
/**
*
*@brief \n
*<B>PRIVATE FUNCTION</B><br><br>
*this function is called by **Drawline()**.<br>
*Use DrawLine()!
*/
void DrawLineNeg(int16_t x,int16_t y,int16_t x1, int16_t y1, uint8_t color, int8_t width)
{

	int16_t dx = x1 - x;
	int16_t dy = y1 - y;
	int16_t ystep = 1;
	if(dy < 0)
	{
		ystep = -1;
		dy *=-1;
	}
	int16_t D = 2*dy - dx;

	for(int i = x; i<=x1; i++)
	{

		if(D > 0)
		{
			y += ystep;
			D -= 2*dx;
		}

		for(int j = 0; j<=width; j++)
		{
			UB_VGA_SetPixel(i,y+j,color);
		}
		D += 2*dy;
	}
}
/**
*@brief \n
*
*DrawLine() draws a line between two (x,y)coördinates with a given color and width
*
*@param DrawError is a pointer to a uint16_t. the function wil write a error to this place if a error occurs
*@param x         the x coördinate where the <B>begin</B> of the line wile be written
*@param y         the y coördinate where the <B>begin</B> of the line wile be written
*@param x1        the x coördinate where the <B>end</B> of the line wile be written
*@param y1        the y coördinate where the <B>end</B> of the line wile be written
*@param color     8 bit color look at *macros* for premade colors
*@param width     width of the line in pixels
*
*
*@return void
*/
void DrawLine(uint16_t *DrawError, int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color, int8_t width)
{
	if ( x > VGA_DISPLAY_X || y > VGA_DISPLAY_Y)
	{
		*DrawError = OUTOFRANGE;

	}

	if(abs(y1-y)<abs(x1-x))
	{
		if(x > x1) // lijn van rechts naar links (startpunt rechts van eindpunt)
		{
			for(int i = 0; i<=width; i++)
			{
				DrawLineNeg(x1,y1,x,y,color,width);
			}
		}
		else // lijn van links naar recht (startpunt links van eindpunt)
		{
			DrawLineNeg(x,y,x1,y1,color,width);
		}
	}
	else
	{
		if(y > y1) // startpunt lijn ligt "hoger" dan eindpunt
		{

			DrawLinePos(x1,y1,x,y,color,width);

		}
		else // startpunt lijn ligt "lager" dan eindpunt
		{
			DrawLinePos(x,y,x1,y1,color,width);
		}
	}
}
/**
*@brief \n
*with DrawTriangle() you can draw a triangle between three points with a color
*@param DrawError is a pointer to a uint16_t. the function wil write a error to this place if a error occurs
*@param x         the x coördinate for the first point of the triangle
*@param y         the y coördinate for the first point of the triangle
*@param x1        the x coördinate for the second point of the triangle
*@param y1        the y coördinate for the second point of the triangle
*@param x2        the x coördinate for the third point of the triangle
*@param y2        the y coördinate for the third point of the triangle
*@param color     8 bit color look at *macros* for premade colors
*
*
*@return void
*/
void DrawTriangle(uint16_t *DrawError,int16_t x, int16_t y, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int8_t color) {

	DrawLine(DrawError,x,y,x1,y1,color,1);
	DrawLine(DrawError,x1,y1,x2,y2,color,1);
	DrawLine(DrawError,x2,y2,x,y,color,1);

}
/**
*@brief \n
*with DrawRect() you can draw a rectangle by entering two point diagonal from each other.
*@param DrawError is a pointer to a uint16_t. the function wil write a error to this place if a error occurs
*@param x         the x coördinate for the first point of the rectangle
*@param y         the y coördinate for the first point of the rectangle
*@param x1        the x coördinate for the second point of the rectangle
*@param y1        the y coördinate for the second point of the rectangle
*@param color     8 bit color look at *macros* for premade colors
*
*
*@return void
*/

void DrawRect(uint16_t *DrawError,int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color)
{
	int yp,xp;

	  for(yp=x;yp<y1;yp++) {
	    for(xp=y;xp<x1;xp++) {
	    	if(xp < VGA_DISPLAY_X && yp < VGA_DISPLAY_Y){
	    		UB_VGA_SetPixel(xp,yp,color);
	    	}
	    	else{
	    		*DrawError = OUTOFRANGE;
	    	}
	    }
	}
}
/**
*@brief \n
*with DrawEllips() you can draw a ellips by entering two x coördinates and two y coördinates the box that you have defined with these coördinates will be filled with a ellips
*@param DrawError is a pointer to a uint16_t. the function wil write a error to this place if a error occurs
*@param x         the x line for the <B>upper</B> boundary of the ellips
*@param y         the y line for the <B>left</B>boundary of the ellips
*@param x1        the x line for the <B>lower</B> boundary of the ellips
*@param y1        the y line for the <B>Right</B> boundary of the ellips
*@param color     8 bit color look at *macros* for premade colors
*
*@return void
*/
void DrawEllips(uint16_t *DrawError,int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color) {

	int yp,xp;

	for(yp=-y1; yp<=y1; yp++) {
	    for(xp=-x1; xp<=x1; xp++) {
	        if(xp*xp*y1*y1+yp*yp*x1*x1 <= y1*y1*x1*x1) {
	        	if(xp+x < VGA_DISPLAY_X && yp+y < VGA_DISPLAY_Y) {
	        		UB_VGA_SetPixel(xp+x, yp+y, color);
	        	}
	        	else {
	        		*DrawError = OUTOFRANGE;
	        	}
	        }
	    }
	}


}

/**
*@brief \n
*with drawchar() you can draw a character on the screen, amazing is it not?
*@param DrawError is a pointer to a uint16_t. the function wil write a error to this place if a error occurs
*@param symbol    the symbol is a char which will be written on te screen
*@param x         the x coördinate for the first point of the character
*@param y         the y coördinate for the first point of the character
*@param color     8 bit color look at *macros* for premade colors
*@param style     the style of the text 0 for Normal 1 for bold 2 for cursive

*
*@return void
*/

uint8_t drawchar(uint16_t *DrawError,char symbol, int16_t x,int16_t y, uint8_t color, uint8_t style)
{
	int i = 0;
	int k = 0;
	uint8_t charpixelheight	= 15;

	uint16_t (*fontInfo)[3];
	static const uint8_t (*pixel);

	if(style == 0) {
		fontInfo = regularFontInfo;
		pixel = regularFontPixel;
	}
	else if(style == 1) {
		fontInfo = italicFontInfo;
		pixel = italicFontPixel;
	}
	else if(style == 2) {
		fontInfo = boldFontInfo;
		pixel = boldFontPixel;
	}
	else{
		fontInfo = regularFontInfo;
		pixel = regularFontPixel;
	}


	while(symbol != fontInfo[i][0] && i < fontSize) {
		i++;
	}

	 uint16_t xp,yp;
	 uint8_t wCount = 0;

	 for(yp=y;yp<(charpixelheight+y);yp++) {
	    for(xp=x;xp<(fontInfo[i][2]+x);xp++) {
	    	if(wCount == 7) {k++; wCount = 0;}
		    if(pixel[k+fontInfo[i][1]] & (0b10000000 >> wCount)) {
		    	if(xp < VGA_DISPLAY_X && yp < VGA_DISPLAY_Y){
		    		UB_VGA_SetPixel(xp,yp,color);
		    	}
		    	else{
		    		*DrawError = OUTOFRANGE;
		    	}
		    }
		    wCount++;
	    }
	    wCount=0;
	    k++;
	 }
	 return(fontInfo[i][2]);
}


void Drawtext(uint16_t *DrawError,char* tekst, int16_t x,int16_t y, uint8_t color, uint8_t style) {
int spacing = 0;
int line = 0;

	while(*tekst != '\0') {
		spacing += drawchar(DrawError, *tekst, x+spacing, y+line, color, style) + 1;
		tekst++;
		if(x+spacing > VGA_DISPLAY_X-15){
			line+=15;
			spacing=0;
		}
	}

}

void Drawbitmap(uint16_t *DrawError,int16_t x,int16_t y,int16_t sel)
{
	if(sel > 2)
		*DrawError = BITMAPINDEX;
	else
	{
	int yp,xp;
	int k = 0;
	  for(yp=y;yp<(50+y);yp++) {
	    for(xp=x;xp<(50+x);xp++) {
	    	k++;
	    	if ( xp > VGA_DISPLAY_X || yp > VGA_DISPLAY_Y)
	    	{
	    		*DrawError = OUTOFRANGE;
	    	}
	    	else
	    	UB_VGA_SetPixel(xp,yp,bitmaps[sel][k]);
	    }
	  }
	}
}
