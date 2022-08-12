#include <iostream>
#include <SFML/Graphics.hpp>

#include "ElementCreation.h"
#include "ElementModification.h"
#include "VertexMath.h"

extern const int GRID_WIDTH;
extern const int GRID_HEIGHT;

void createCircle(int x, int y, int radius, ElementType Element, float fillRate) {
	sf::Vector2f center(x, y);
	for (int x1 = 0; x1 < GRID_WIDTH; x1++) {
		for (int y1 = 0; y1 < GRID_HEIGHT; y1++) {
			if (fillRate > rand() / double(RAND_MAX) && dist(center, sf::Vector2f(x1, y1)) < radius) {
				setElementAtPosition(x1, y1, Element);
			}
		}
	}
}

void createRectangle(int x1, int y1, int x2, int y2, ElementType Element) {
	for (int x = x1; x != x2; x++) {
		for (int y = y1; y != y2; y++) {
			setElementAtPosition(x, y, Element);
		}
	}
}