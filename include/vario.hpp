#ifndef __VARIO_HPP
#define __VARIO_HPP

#include <MCUFRIEND_kbv.h>

void updateVario(MCUFRIEND_kbv &tft, float sink, float temperature);
void drawVarioArrow(MCUFRIEND_kbv &tft, float sink);
void writeVarioValue(MCUFRIEND_kbv &tft, float sink);
void drawVarioTriangle(MCUFRIEND_kbv &tft, float sink);
void writeTemperature(MCUFRIEND_kbv &tft, float temperature);

#endif