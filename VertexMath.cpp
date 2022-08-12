#include <SFML/Graphics.hpp>
#include <functional>

#include "VertexMath.h"
#include "TraceResult.h"
#include "ElementModification.h"

extern const int SCR_WIDTH;
extern const int SCR_HEIGHT;

extern const int PIXEL_SIZE;

extern const int GRID_WIDTH;
extern const int GRID_HEIGHT;

int randomInteger(int min, int max) {
	return rand() % (max - min + 1) + min;
}

bool validPosition(int x, int y) {
	if (x < 0 || x > GRID_WIDTH - 1 || y < 0 || y > GRID_HEIGHT - 1) return false;

	return true;
}

sf::Vector2i translatePosition(sf::Vector2i pos) {
	return sf::Vector2i(pos.x / PIXEL_SIZE, (SCR_HEIGHT - pos.y) / PIXEL_SIZE);
}

float magnitude(sf::Vector2f vector) {
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

sf::Vector2f divide(sf::Vector2f vector, float value) {
	return sf::Vector2f(vector.x / value, vector.y / value);
}

sf::Vector2f multiply(sf::Vector2f vector, float value) {
	return sf::Vector2f(vector.x * value, vector.y * value);
}

sf::Vector2f normalize(sf::Vector2f vector) {
	return divide(vector, magnitude(vector));
}

float dist(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

// DDA algorithm to efficiently step through each grid space on the path
// 4th argument is a function that will be called for each element the ray passes
// if the function returns false it will stop tracing the ray

void rayTrace(sf::Vector2i start, sf::Vector2i end, std::function<bool(Element*)> callback) {
	sf::Vector2f fStart = sf::Vector2f(start.x, start.y);
	sf::Vector2f fEnd = sf::Vector2f(end.x, end.y);

	sf::Vector2f delta = sf::Vector2f(fEnd.x - fStart.x, fEnd.y - fStart.y);

	float numSteps;
	if (abs(delta.x) > abs(delta.y)) {
		numSteps = abs(delta.x);
	}
	else {
		numSteps = abs(delta.y);
	}

	sf::Vector2f increments = sf::Vector2f(delta.x / numSteps, delta.y / numSteps);
	sf::Vector2f curPos = sf::Vector2f(fStart.x + increments.x, fStart.y + increments.y);

	for (int i = 0; i < numSteps; i++) {
		if (!validPosition(curPos.x, curPos.y)) {
			return;
		}

		Element* element = getElementAtPosition(curPos.x, curPos.y);

		if (callback(element))
			return;

		curPos.x += increments.x;
		curPos.y += increments.y;
	}
}

void rayTrace(sf::Vector2i start, float rotation, int length, std::function<bool(Element*)> callback) {
	sf::Vector2f direction(cos(rotation), sin(rotation));
	direction = multiply(direction, length);
	
	rayTrace(start, sf::Vector2i(direction.x + start.x, direction.y + start.y), callback);
}

TraceResult rayTrace(sf::Vector2i start, sf::Vector2i end) {
	sf::Vector2f fStart = sf::Vector2f(start.x, start.y);
	sf::Vector2f fEnd = sf::Vector2f(end.x, end.y);

	sf::Vector2f delta = sf::Vector2f(fEnd.x - fStart.x, fEnd.y - fStart.y);

	float numSteps;
	if (abs(delta.x) > abs(delta.y)) {
		numSteps = abs(delta.x);
	}
	else {
		numSteps = abs(delta.y);
	}

	sf::Vector2f increments = sf::Vector2f(delta.x / numSteps, delta.y / numSteps);
	sf::Vector2f curPos = sf::Vector2f(fStart.x + increments.x, fStart.y + increments.y);

	TraceResult result;

	for (int i = 0; i < numSteps; i++) {
		if (!validPosition(curPos.x, curPos.y)) {
			result.hit = true;
			result.hitElement = nullptr;
			result.lastOpenPosition = sf::Vector2i(curPos.x - increments.x, curPos.y - increments.y);
			break;
		}

		Element* element = getElementAtPosition(curPos.x, curPos.y);

		if (element->type != ElementType::NIL) {
			result.hit = true;
			result.hitElement = element;
			result.lastOpenPosition = sf::Vector2i(curPos.x - increments.x, curPos.y - increments.y);
			break;
		}

		curPos.x += increments.x;
		curPos.y += increments.y;
	}

	if (result.hit) {
		result.distance = magnitude(curPos);
		result.hitPos = curPos;
	}

	return result;
}

TraceResult rayTrace(sf::Vector2i start, float rotation, int length) {
	sf::Vector2f direction(cos(rotation), sin(rotation));
	direction = multiply(direction, length);

	return rayTrace(start, sf::Vector2i(direction.x + start.x, direction.y + start.y));
}