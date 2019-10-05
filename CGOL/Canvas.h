#pragma once
#include "Common.h"


//Prototypes
void DrawGrid(sf::Uint8 *pixels, int gridSize, int sizeX, int sizeY);

//Methods
void DrawGrid(sf::Uint8 *pixels, int gridSize, int sizeX, int sizeY) {

	int rowNum = sizeY / gridSize;
	int columnNum = sizeX / gridSize;
	
	for (int aux = 0; aux < sizeX * sizeY; aux++)
	{
		int i = aux * 4;

		//Still need to draw horizontal lines
		if (aux % columnNum == 0) {
			pixels[i] = 70;
			pixels[i + 1] = 70;
			pixels[i + 2] = 70;
			pixels[i + 3] = 255;
		}
		else {
			pixels[i] = 255;
			pixels[i + 1] = 255;
			pixels[i + 2] = 255;
			pixels[i + 3] = 255;
		}
	}
}