#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "TraceResult.h"
#include "Element.h"
#include "ElementType.h"

extern const int GRID_WIDTH;
extern const int GRID_HEIGHT;

extern const int SCR_HEIGHT;

extern const int PIXEL_SIZE;

void rayTrace(sf::Vector2i start, sf::Vector2i end, std::function<bool(Element*)> callback);
void rayTrace(sf::Vector2i start, float rotation, int length, std::function<bool(Element*)> callback);
TraceResult rayTrace(sf::Vector2i start, sf::Vector2i end);
TraceResult rayTrace(sf::Vector2i start, float rotation, int length);

int randomInteger(int min, int max);
bool validPosition(int x, int y);

float magnitude(sf::Vector2f vector);
sf::Vector2f divide(sf::Vector2f vector, float value);
sf::Vector2f multiply(sf::Vector2f vector, float value);
sf::Vector2f normalize(sf::Vector2f vector);
sf::Vector2i translatePosition(sf::Vector2i pos);
float dist(sf::Vector2f p1, sf::Vector2f p2);