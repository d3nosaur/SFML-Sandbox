#include <SFML/Graphics.hpp>
#include "Fluid.cpp"

#include "ElementModification.h"
#include "VertexMath.h"

struct Water : Fluid {
	Water() {
		type = ElementType::Water;

		int brightness = randomInteger(0, 2);
		color = sf::Color(80 - brightness, (148 + (randomInteger(-1, 1) * 5)) - brightness, (242 + (randomInteger(-1, 0) * 5) - brightness));

		spreadRate = 4;
	}
};