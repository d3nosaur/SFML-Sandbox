#include <SFML/Graphics.hpp>
#include "Element.h"

#include "ElementModification.h"
#include "VertexMath.h"

extern const int GRID_HEIGHT;

struct Fluid : Element {
	int spreadRate = 5;

	Fluid() {
		type = ElementType::NIL;
		state = ElementState::Liquid;
		color = sf::Color::White;
	}

	void updateTick(int x, int y) override {
		// down movement
		if(validPosition(x, y - 1) && getElementAtPosition(x, y - 1)->type == ElementType::NIL) {
			swapElementPositions(x, y, x, y - 1);
			return;
		}

		// left and right movement
		bool direction = 0 + (rand() % (1 - 0 + 1)) == 1;
		int steps = 1;
		while (steps < spreadRate) {
			int xPos = x + (direction ? -1 * steps : 1 * steps);

			// hit something, break out of loop
			if (!validPosition(xPos, y) || getElementAtPosition(xPos, y)->type != ElementType::NIL) break;

			swapElementPositions(x, y, xPos, y);
		}
	}
};