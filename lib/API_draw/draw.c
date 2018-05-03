#include "draw.h"
#include "stdlib.h"
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

void DrawLinePos(uint16_t x,uint16_t y,uint16_t x1, uint16_t y1, uint8_t color)
{
	int16_t dx = x1 - x;
	int16_t dy = y1 - y;
	int16_t xstep = 1;
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
		D += 2*dx;
		UB_VGA_SetPixel(x,i,color);
	}
}

void DrawLineNeg(uint16_t x,uint16_t y,uint16_t x1, uint16_t y1, uint8_t color)
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
		D += 2*dy;
		UB_VGA_SetPixel(i,y,color);

	}
}

void DrawLine(uint16_t x,uint16_t y,uint16_t x1, uint16_t y1, uint8_t color)
{
	if(abs(y1-y)<abs(x1-x))
	{
		if(x > x1) // lijn van rechts naar links (startpunt rechts van eindpunt)
		{
			DrawLineNeg(x1,y1,x,y,color);
		}
		else // lijn van links naar recht (startpunt links van eindpunt)
		{
			DrawLineNeg(x,y,x1,y1,color);
		}
	}
	else
	{
		if(y > y1) // startpunt lijn ligt "hoger" dan eindpunt
		{
			DrawLinePos(x1,y1,x,y,color);
		}
		else // startpunt lijn ligt "lager" dan eindpunt
		{
			DrawLinePos(x,y,x1,y1,color);
		}
	}
}
