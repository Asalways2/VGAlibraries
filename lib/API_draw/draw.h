
#include "api_io.h"

#include "stdlib.h"
#include <math.h>
#include "bitmap.h"
#include "FontRegular.h"
#include "FontItalic.h"
#include "FontBold.h"

void UB_VGA_FillScreen(uint8_t color);
void DrawLine(int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color, int8_t width);
void DrawLineNeg(int16_t x,int16_t y,int16_t x1, int16_t y1, uint8_t color, int8_t width);
void DrawLinePos(int16_t x,int16_t y,int16_t x1, int16_t y1, uint8_t color, int8_t width);
void DrawRect(int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color);
void DrawTriangle(int16_t x, int16_t y, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int8_t color);
void DrawEllips(int16_t x,int16_t y,int16_t x1, int16_t y1, int8_t color);
void Drawbitmap(int16_t x,int16_t y,int16_t sel);
void Drawtext(char* tekst, int16_t x,int16_t y, uint8_t color, uint8_t style);
uint8_t drawchar(char symbol, int16_t x,int16_t y, uint8_t color, uint8_t style);
