#include <SFML/Graphics.hpp>

#include "ImmoveableSolid.cpp"
#include "ElementModification.h"
#include "VertexMath.h"

struct Stone : public ImmoveableSolid {
	Stone() {
		type = ElementType::Stone;

		int brightness = randomInteger(0, 40);
		color = sf::Color(131 - brightness, 136 - brightness, 145 - brightness);
	}
};