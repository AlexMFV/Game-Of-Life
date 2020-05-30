#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <iostream>
#include "Canvas.h"
#include "PixelBuffers.h"
#include "Sprites.h"
#include "Common.h"
#include "Textures.h"
#include "Cursor.h"
#include <stdlib.h>

using namespace std;

int main() {
	gridSize = AdjustGridSize(gridSize, m_width, m_height-1);

	//Makes all the pixels in the array, Transparent
	TransparentArray(squaresPixelBuffer);
	ColoredArray(bgPixelBuffer);

	sf::RenderWindow window(sf::VideoMode(m_width, m_height), "Conway's Game Of Life");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(fps_limit);

	//Set Grid sprite and Textures
	gridTexture.create(m_width, m_height);
	gridSprite.setTexture(gridTexture);

	//Set squares sprites and textures
	squareTexture.create(m_width, m_height);
	squareSprite.setTexture(squareTexture);

	//Back ground Texture and sprite
	bgTexture.create(m_width, m_height);
	bgTexture.update(bgPixelBuffer);
	bgSprite.setTexture(bgTexture);

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

				if (event.key.code == sf::Keyboard::Subtract)
				{
					if (fps_limit > 5)
						fps_limit -= 5;
					window.setFramerateLimit(fps_limit);
				}

				if (event.key.code == sf::Keyboard::Add)
				{
					if (fps_limit < 60)
						fps_limit += 5;
					window.setFramerateLimit(fps_limit);
				}

				if (event.key.code == sf::Keyboard::Multiply)
				{
					fps_limit = 30;
					window.setFramerateLimit(fps_limit);
				}

				if (event.key.code == sf::Keyboard::Space) {
					isPlaying ? ColoredArray(bgPixelBuffer) : TransparentArray(bgPixelBuffer);
					bgTexture.update(bgPixelBuffer);
					isPlaying = !isPlaying;
				}

				if (event.key.code == sf::Keyboard::O) {
					squaresPixelBuffer = nullptr;
					squaresPixelBuffer = new sf::Uint8[m_width * m_height * 4];
					TransparentArray(squaresPixelBuffer);
					squareTexture.update(squaresPixelBuffer);
				}
			}
		}

		//Write current FPS to console
		//std::cout << "Current FPS: " << fps_limit;

		window.clear(sf::Color::White);

		if (isGridActive) {
			DrawGrid(gridPixelBuffer, gridSize, m_width, m_height);
			gridTexture.update(gridPixelBuffer);
			window.draw(gridSprite);
		}
		/*else
		{
			TransparentArray(gridPixelBuffer);
			gridTexture.update(gridPixelBuffer);
			window.draw(gridSprite);
		}*/

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

		//window.draw(gridSprite);
		window.draw(bgSprite);
		window.draw(squareSprite);
		window.display();
	}

	return 0;
}