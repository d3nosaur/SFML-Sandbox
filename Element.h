#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "ElementType.h"
#include "ElementState.h"

struct Element {
	sf::Color color = sf::Color::White;
	ElementType type = ElementType::NIL;
	ElementState state = ElementState::NIL;
	sf::Vector2i location;

	Element() {};

	virtual void updateTick(int x, int y) {
		std::cout << "Base element update\n";
	}
};