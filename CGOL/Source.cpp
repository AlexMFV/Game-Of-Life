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

	bool debug = false;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();

			if (event.type == event.MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Button::Left)
					isMousePressed = true;

				if (event.mouseButton.button == sf::Mouse::Button::Right)
					isMouseClearPressed = true;
			}
					
			if (event.type == event.MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left)
					isMousePressed = false;

				if (event.mouseButton.button == sf::Mouse::Button::Right)
					isMouseClearPressed = false;
			}

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

		//Handle drawing or clearing the squares
		if (isMouseClearPressed) {
			cursor = GetMouseCoordinates(window, cursor);
			DrawSquare(squaresPixelBuffer, cursor, false);
			squareTexture.update(squaresPixelBuffer);
		}

		if (isMousePressed){
			cursor = GetMouseCoordinates(window, cursor);
			DrawSquare(squaresPixelBuffer, cursor, true);
			squareTexture.update(squaresPixelBuffer);
		}

		if (isPlaying) {
			//Game Code, Move Squares, process interactions
			ProcessSquares(squaresPixelBuffer);
			squareTexture.update(squaresPixelBuffer);
		}

		///////////// DEBUG PURPOSES ONLY //////////////
		//if (debug) {
		//	DrawSquare(squaresPixelBuffer, 1, 1, true);
		//	squareTexture.update(squaresPixelBuffer);
		//	debug = !debug;
		//}
		//else {
		//	DrawSquare(squaresPixelBuffer, 1, 1, false);
		//	squareTexture.update(squaresPixelBuffer);
		//	debug = !debug;
		//}
		///////////// DEBUG PURPOSES ONLY //////////////

		window.draw(squareSprite);
		window.display();
	}

	return 0;
}