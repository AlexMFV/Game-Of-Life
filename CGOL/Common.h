#pragma once
#include "Cursor.h"
#include <iostream>

sf::Color gridColor(0, 0, 0, 255); //Default: (71, 71, 71, 255)
sf::Color backgroundColor(255, 255, 255, 255); //Default (255, 255, 255, 255)
sf::Color squareColor(0, 0, 0, 255); //Default (0,0,0,255)
sf::Color transp(0, 0, 0, 0);

//Grid Variables
bool isGridActive = true;
int gridSize = 20; //Ammout of "pixels" that make the grid ex: 5 = 5x5 grid

//Window Variables
const int m_width = 800;
const int m_height = 800 + 1; //Never remove the + 1 (Add the size as you want)

//Mouse Variables
bool isMousePressed = false;
bool isMouseClearPressed = false;
Cursor cursor(0,0);

//Main Game Variables
bool isPlaying = false;

//bool ChangeStatus(bool value);
void TransparentArray(sf::Uint8* pixels);

//bool ChangeStatus(bool value) {
//	return !value;
//}

void TransparentArray(sf::Uint8* pixels) {
	for (int i = 0; i < m_width * m_height; i++)
	{
		int aux = i * 4;

		pixels[aux] = transp.r;
		pixels[aux+1] = transp.g;
		pixels[aux+2] = transp.b;
		pixels[aux+3] = transp.a;
	}
}