#include "api_io.h"

void UB_VGA_FillScreen(uint8_t color);
void DrawLine(uint16_t x,uint16_t y,uint16_t x1, uint16_t y1, uint8_t color);
void DrawLineNeg(uint16_t x,uint16_t y,uint16_t x1, uint16_t y1, uint8_t color);
void DrawLinePos(uint16_t x,uint16_t y,uint16_t x1, uint16_t y1, uint8_t color);
