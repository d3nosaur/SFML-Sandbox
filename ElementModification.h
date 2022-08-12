#pragma once

#include <SFML/Graphics.hpp>
#include "Element.h"
#include "ElementType.h"

Element* typeToElement(ElementType element);
Element* getElementAtPosition(int x, int y);
Element* getElementAtPosition(sf::Vector2i location);
void swapElementPositions(int x1, int y1, int x2, int y2);
void swapElementPositions(sf::Vector2i l1, sf::Vector2i l2);
void setElementAtPosition(int x, int y, ElementType Element);