#pragma once

#include <SFML/Graphics.hpp>

#include "Element.h"

struct TraceResult {
	Element* hitElement;
	sf::Vector2i lastOpenPosition;
	sf::Vector2f hitPos;
	float distance;
	bool hit;

	TraceResult() {
		hitElement = nullptr;
		distance = -1;
		hit = false;
	};
};