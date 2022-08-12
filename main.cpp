#include <iostream>
#include <SFML/Graphics.hpp>

#include "VertexMath.h"
#include "ElementModification.h"
#include "ElementCreation.h"

const int SCR_WIDTH = 1600;
const int SCR_HEIGHT = 800;
const int MAX_FRAMERATE = 144;

const int PIXEL_SIZE = 8;

const int GRID_WIDTH = SCR_WIDTH / PIXEL_SIZE;
const int GRID_HEIGHT = SCR_HEIGHT / PIXEL_SIZE;

const sf::Color BACKGROUND_COLOR = sf::Color(32, 50, 61);

std::vector<std::vector<Element*>> automataPixels(GRID_WIDTH);
std::vector<sf::Vertex> visualPixels(GRID_WIDTH * GRID_HEIGHT * 4);

ElementType activeElement = ElementType::Sand;

int drawSize = 5;
float drawOpacity = 1.0f;

float x = 0;
void renderTick(sf::RenderWindow& window) {
	bool flip = true; // flips rendering between left to right and right to left to introduce some randomness

	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = (flip ? 0 : GRID_WIDTH - 1); (flip ? x < GRID_WIDTH : x > -1); (flip ? x++ : x--)) {
			Element* ptr = getElementAtPosition(x, y);

			if (ptr == nullptr) continue;
			
			if (ptr->type != ElementType::NIL && ptr->state != ElementState::ImmoveableSolid) {
				ptr->updateTick(x, y);
			}
		}
		
		flip = !flip;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i pos = translatePosition(sf::Mouse::getPosition(window));
		
		createCircle(pos.x, pos.y, drawSize, activeElement, drawOpacity);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		sf::Vector2i pos = translatePosition(sf::Mouse::getPosition(window));

		createCircle(pos.x, pos.y, drawSize, ElementType::NIL, drawOpacity);
	}

	window.clear(BACKGROUND_COLOR);
	window.draw(&visualPixels[0], visualPixels.size(), sf::Quads);
	window.display();
}

void fillVisualPixels() {
	for (int x = 0; x < GRID_WIDTH; x++) {
		for (int y = 0; y < GRID_HEIGHT; y++) {
			visualPixels[((y + (x * GRID_HEIGHT)) * 4) + 0] = sf::Vertex(sf::Vector2f(PIXEL_SIZE * x,       SCR_HEIGHT - (PIXEL_SIZE * (y + 1))), sf::Color(x * (255 / GRID_WIDTH), y * (255 / GRID_WIDTH), 0)); // top left
			visualPixels[((y + (x * GRID_HEIGHT)) * 4) + 1] = sf::Vertex(sf::Vector2f(PIXEL_SIZE * x,       SCR_HEIGHT - (PIXEL_SIZE * y)),       sf::Color(x * (255 / GRID_WIDTH), y * (255 / GRID_WIDTH), 0)); // bottom left
			visualPixels[((y + (x * GRID_HEIGHT)) * 4) + 2] = sf::Vertex(sf::Vector2f(PIXEL_SIZE * (x + 1), SCR_HEIGHT - (PIXEL_SIZE * y)),       sf::Color(x * (255 / GRID_WIDTH), y * (255 / GRID_WIDTH), 0)); // bottom right
			visualPixels[((y + (x * GRID_HEIGHT)) * 4) + 3] = sf::Vertex(sf::Vector2f(PIXEL_SIZE * (x + 1), SCR_HEIGHT - (PIXEL_SIZE * (y + 1))), sf::Color(x * (255 / GRID_WIDTH), y * (255 / GRID_WIDTH), 0)); // top right
		}
	}
}

void initialCache() {
	for (int x = 0; x < GRID_WIDTH; x++) {
		automataPixels[x] = std::vector<Element*>(GRID_HEIGHT);

		for (int y = 0; y < GRID_HEIGHT; y++) {
			setElementAtPosition(x, y, ElementType::NIL);
		}
	}
}

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "SFML Sandbox");

	fillVisualPixels();
	initialCache();

	int xOffset = GRID_WIDTH / 4;
	int yOffset = GRID_HEIGHT / 4;

	const float frameDelay = 1.0f / MAX_FRAMERATE;
	sf::Clock deltaTracker;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Equal:
							drawSize++;
							std::cout << "Draw Size: " << drawSize << "\n";
							break;
						case sf::Keyboard::Dash:
							drawSize--;
							if (drawSize < 1) drawSize = 1;
							std::cout << "Draw Size: " << drawSize << "\n";
							break;
						case sf::Keyboard::RBracket:
							if (drawOpacity < 0.1f) drawOpacity = 0.0f;
							drawOpacity += 0.1f;
							if (drawOpacity > 1.0) drawOpacity = 1.0f;
							std::cout << "Draw Opacity: " << drawOpacity << "\n";
							break;
						case sf::Keyboard::LBracket:
							drawOpacity -= 0.1f;
							if (drawOpacity < 0.01) drawOpacity = 0.01;
							std::cout << "Draw Opacity: " << drawOpacity << "\n";
							break;
						case sf::Keyboard::Num1:
							activeElement = ElementType::Sand;
							break;
						case sf::Keyboard::Num2:
							activeElement = ElementType::Water;
							break;
						case sf::Keyboard::Num3:
							activeElement = ElementType::Stone;
							break;
						}

					break;
				}
		}

		if (deltaTracker.getElapsedTime().asSeconds() > frameDelay) {
			float fps = 1.0f / deltaTracker.restart().asSeconds();
			//std::cout << "FPS: " << fps << "\n";

			renderTick(window);
		}
	}

	return 0;
}
