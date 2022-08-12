#include <SFML/Graphics.hpp>

#include "Element.h"

struct Empty : Element {
	Empty() {
		type = ElementType::NIL;
		color = sf::Color(32, 50, 61);
	}

	void updateTick(int x, int y) {
		std::cout << "Empty\n";
	}
};