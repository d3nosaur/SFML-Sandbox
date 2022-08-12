#pragma once

#include <SFML/Graphics.hpp>
#include "ElementType.h"

extern const int GRID_WIDTH;
extern const int GRID_HEIGHT;

void createCircle(int x, int y, int radius, ElementType Element, float fillRate);
void createRectangle(int x1, int y1, int x2, int y2, ElementType Element);