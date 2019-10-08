#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <iostream>
#include "Canvas.h"
#include "PixelBuffers.h"
#include "Sprites.h"
#include "Common.h"
#include "Textures.h"

int main() {
	m_height += 1;

	gridSize = AdjustGridSize(gridSize, m_width, m_height-1);

	sf::RenderWindow window(sf::VideoMode(m_width, m_height), "Conway's Game Of Life");

	//Set Grid sprite and Textures
	gridTexture.create(m_width, m_height);
	gridSprite.setTexture(gridTexture);

	int test = 0;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();

			if (event.type == event.KeyPressed)
				if (event.key.code == sf::Keyboard::G)
					isGridActive = ChangeStatus(isGridActive);
		}

		window.clear(sf::Color::White);
		//window.draw();

		if (isGridActive) {
			DrawGrid(gridPixelBuffer, gridSize, m_width, m_height);
			gridTexture.update(gridPixelBuffer);
			window.draw(gridSprite);
		}

		window.display();

	}

	return 0;
}