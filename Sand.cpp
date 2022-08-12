#include <SFML/Graphics.hpp>

#include "MoveableSolid.cpp"
#include "ElementModification.h"
#include "VertexMath.h"

struct Sand : public MoveableSolid {
	Sand() {
		type = ElementType::Sand;

		int brightness = randomInteger(0, 40);
		color = sf::Color((227 + (randomInteger(0, 5) * 5)) - brightness, (189 + (randomInteger(-2, 0) * 5)) - brightness, 100 - brightness);
	}
};