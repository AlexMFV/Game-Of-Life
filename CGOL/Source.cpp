#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <iostream>
#include "Canvas.h"

int main() {

	int gridSize = 20; //Ammout of "pixels" that make the grid ex: 5 = 5x5 grid
	int m_width = 600;
	int m_height = 600;

	sf::RenderWindow window(sf::VideoMode(m_width, m_height), "Conway's Game Of Life");

	sf::Uint8 *pixelBuffer = new sf::Uint8[m_width * m_height * 4];

	sf::Texture texture;
	texture.create(m_width, m_height);
	
	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();
		}

		window.clear();
		//window.draw();

		DrawGrid(pixelBuffer, gridSize, m_width, m_height);

		texture.update(pixelBuffer);

		window.draw(sprite);
		window.display();

	}

	return 0;
}