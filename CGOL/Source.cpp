#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <iostream>
#include "Canvas.h"
#include "PixelBuffers.h"
#include "Sprites.h"
#include "Common.h"
#include "Textures.h"
#include "Cursor.h"

int main() {
	gridSize = AdjustGridSize(gridSize, m_width, m_height-1);

	//Makes all the pixels in the array, Transparent
	TransparentArray(squaresPixelBuffer);

	sf::RenderWindow window(sf::VideoMode(m_width, m_height), "Conway's Game Of Life");
	window.setVerticalSyncEnabled(true);

	//Set Grid sprite and Textures
	gridTexture.create(m_width, m_height);
	gridSprite.setTexture(gridTexture);

	//Set squares sprites and textures
	squareTexture.create(m_width, m_height);
	squareSprite.setTexture(squareTexture);

	int test = 0;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();

			if (event.type == event.MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Button::Left)
					isMousePressed = true;
					
			if (event.type == event.MouseButtonReleased)
				if(event.mouseButton.button == sf::Mouse::Button::Left)
					isMousePressed = false;

			if (event.type == event.KeyPressed) {
				if (event.key.code == sf::Keyboard::G)
					isGridActive = !isGridActive;

				if (event.key.code == sf::Keyboard::Space)
					isPlaying = !isPlaying;
			}
		}

		window.clear(sf::Color::White);
		//window.draw();

		if (isGridActive) {
			DrawGrid(gridPixelBuffer, gridSize, m_width, m_height);
			gridTexture.update(gridPixelBuffer);
			window.draw(gridSprite);
		}

		if (isMousePressed){
			cursor = GetMouseCoordinates(window, cursor);
			DrawSquare(squaresPixelBuffer, cursor);
			squareTexture.update(squaresPixelBuffer);
		}

		if (isPlaying) {
			//Game Code, Move Squares, process interactions
		}

		window.draw(squareSprite);
		window.display();
	}

	return 0;
}