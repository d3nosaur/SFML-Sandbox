#include <SFML/Graphics.hpp>

#include "Element.h"
#include "ElementModification.h"
#include "VertexMath.h"

struct ImmoveableSolid : public Element {
	ImmoveableSolid() {
		type = ElementType::NIL;
		state = ElementState::ImmoveableSolid;
		color = sf::Color::White;
	}
};