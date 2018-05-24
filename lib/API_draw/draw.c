#include "draw.h"
//--------------------------------------------------------------
// Füllt den Screen mit einer Farbe
//--------------------------------------------------------------
void UB_VGA_FillScreen(uint8_t color)
{
  uint16_t xp,yp;

  for(yp=0;yp<VGA_DISPLAY_Y;yp++) {
    for(xp=0;xp<VGA_DISPLAY_X;xp++) {
      UB_VGA_SetPixel(xp,yp,color);
    }
  }
}

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

void DrawLine(int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color, int8_t width)
{
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

void DrawTriangle(int16_t x, int16_t y, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int8_t color) {

	DrawLine(x,y,x1,y1,color,1);
	DrawLine(x1,y1,x2,y2,color,1);
	DrawLine(x2,y2,x,y,color,1);

}


void DrawRect(int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color)
{
	int yp,xp;

	  for(yp=x;yp<y1;yp++) {
	    for(xp=y;xp<x1;xp++) {
	      UB_VGA_SetPixel(xp,yp,color);
	    }
	}
}

void DrawEllips(int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color) {
	//int r2 = (pow(X-x, 2)/x1) + (pow(Y-y, 2)/y2);

	int yp,xp;

	for(yp=-y1; yp<=y1; yp++) {
	    for(xp=-x1; xp<=x1; xp++) {
	        if(xp*xp*y1*y1+yp*yp*x1*x1 <= y1*y1*x1*x1)
	        	UB_VGA_SetPixel(xp+x, yp+y, color);
	    }
	}


}

/*
uint8_t drawchar(char symbol, int16_t x,int16_t y, uint8_t color, uint8_t backgroundcolor)
{
	int i = 0;
	int k = 0;
	int charIndex = 0;
	int charColor = 0;
	uint8_t charpixelheight		= 15;
	uint8_t widthpixelarr[7]	= {4,6,6,8,7,6,6};
	char 	fontpixelchars[7]	= {'1','2','3','4','5','6','7'};

	while(symbol != fontpixelchars[i]) {
		charIndex += (charpixelheight*widthpixelarr[i]);
		i++;
	}

	 uint16_t xp,yp;

	  for(yp=y;yp<(charpixelheight+y);yp++) {
	    for(xp=x;xp<(widthpixelarr[i]+x);xp++) {
	      k++;
	      if(pixel[k+charIndex] != 0x00)
	      {
	    	  charColor = color;
	      }
	      else
	      {
	    	  charColor = 0x00;
	      }
	      UB_VGA_SetPixel(xp,yp,charColor);
	    }
	  }
	  return(widthpixelarr[i]);
}

*/

uint8_t drawchar2(char symbol, int16_t x,int16_t y, uint8_t color, uint8_t style)
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
		    if(pixel[k+fontInfo[i][1]] & (0b10000000 >> wCount))
		    	UB_VGA_SetPixel(xp,yp,color);
		    wCount++;
	    }
	    wCount=0;
	    k++;
	 }
	 return(fontInfo[i][2]);
}


void Drawtext(char* tekst, int16_t x,int16_t y, uint8_t color, uint8_t style) {
int spacing = 0;
int line = 0;

	while(*tekst != '\0') {
		spacing += drawchar2(*tekst, x+spacing, y+line, color, style) + 1;
		tekst++;
		if(x+spacing > VGA_DISPLAY_X-15){
			line+=15;
			spacing=0;
		}
	}

}

void Drawbitmap(int16_t x,int16_t y,int16_t sel)
{
	int yp,xp;
	int k = 0;
	  for(yp=y;yp<(50+y);yp++) {
	    for(xp=x;xp<(50+x);xp++) {
	    	k++;
	    	UB_VGA_SetPixel(xp,yp,bitmaps[sel][k]);
	    }
	}
}





