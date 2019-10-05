#pragma once
#include "Common.h"


//Prototypes
void DrawGrid(sf::Image *img, int gridSize);

//Methods
void DrawGrid(sf::Uint8* pixels, int gridSize, int sizeX, int sizeY) {

	int rowNum = sizeY / gridSize;
	int columnNum = sizeX / gridSize;

	for (int i = 0; i < sizeX * sizeY * 4; i++)
	{
		pixels[i] = 150;
	}

	/*for (int row = 0; row < rowNum; row++)
	{
		for (int col = 0; col < columnNum; col++)
		{
			img->setPixel(col * gridSize, row, gridColor);
			img->setPixel(col, row * gridSize, gridColor);
		}
	}*/
}