#include <SFML/Graphics.hpp>
#include <functional>

#include "Element.h"
#include "ElementModification.h"
#include "VertexMath.h"

struct MoveableSolid : public Element {
	MoveableSolid() {
		type = ElementType::NIL;
		state = ElementState::MoveableSolid;
		color = sf::Color::White;
	}

	void updateTick(int x, int y) override {
		if (!validPosition(x, y - 1)) return;

		Element* checkElement = getElementAtPosition(x, y - 1);
		
		// down movement
		if(checkElement->type == ElementType::NIL || checkElement->state == ElementState::Liquid) {
			if (checkElement->state == ElementState::Liquid)
				color = sf::Color(color.r * 0.99, color.g * 0.99, color.b * 0.99);

			swapElementPositions(x, y, x, y - 1);
			return;
		}

		// down left and down right
		for (int i = -1; i <= 1; i += 2) {
			if (!validPosition(x + i, y - 1)) continue;

			checkElement = getElementAtPosition(x + i, y - 1);
			if (checkElement->type == ElementType::NIL || checkElement->state == ElementState::Liquid) {
				if (checkElement->state == ElementState::Liquid)
					color = sf::Color(color.r * 0.99, color.g * 0.99, color.b * 0.99);

				swapElementPositions(x, y, x + i, y - 1);
				return;
			}
		}
	}
};