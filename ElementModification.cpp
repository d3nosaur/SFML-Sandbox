#include <SFML/Graphics.hpp>
#include <iostream>

#include "Sand.cpp"
#include "Water.cpp"
#include "Empty.cpp"
#include "Stone.cpp"

#include "ElementModification.h"
#include "VertexMath.h"

extern const int GRID_HEIGHT;

extern std::vector<std::vector<Element*>> automataPixels;
extern std::vector<sf::Vertex> visualPixels;

void setVertexColor(int x, int y, sf::Color color) {
	visualPixels[((y + (x * GRID_HEIGHT)) * 4) + 0].color = color;
	visualPixels[((y + (x * GRID_HEIGHT)) * 4) + 1].color = color;
	visualPixels[((y + (x * GRID_HEIGHT)) * 4) + 2].color = color;
	visualPixels[((y + (x * GRID_HEIGHT)) * 4) + 3].color = color;
}

Element* typeToElement(ElementType type) {
	switch (type) {
	case ElementType::Sand:
		return new Sand();
	case ElementType::Water:
		return new Water();
	case ElementType::Stone:
		return new Stone();
	case ElementType::NIL:
		return new Empty();
	}
}

Element* getElementAtPosition(int x, int y) {
	return automataPixels[x][y];
}

Element* getElementAtPosition(sf::Vector2i location) {
	return getElementAtPosition(location.x, location.y);
}

void swapElementPositions(int x1, int y1, int x2, int y2) {
	if (!validPosition(x1, y1) || !validPosition(x2, y2)) return;

	Element* e1 = getElementAtPosition(x1, y1);
	Element* e2 = getElementAtPosition(x2, y2);

	sf::Color holdColor = e1->color;
	setVertexColor(x1, y1, e2->color);
	setVertexColor(x2, y2, holdColor);

	automataPixels[x1][y1]->location = sf::Vector2i(x2, y2);
	automataPixels[x2][y2]->location = sf::Vector2i(x1, y1);

	std::swap(automataPixels[x1][y1], automataPixels[x2][y2]);
}

void swapElementPositions(sf::Vector2i l1, sf::Vector2i l2) {
	swapElementPositions(l1.x, l1.y, l2.x, l2.y);
}

void setElementAtPosition(int x, int y, ElementType element) {
	if (!validPosition(x, y))
		return;

	Element* newElement = typeToElement(element);

	newElement->location = sf::Vector2i(x, y);
	setVertexColor(x, y, newElement->color);
	automataPixels[x][y] = newElement;
}