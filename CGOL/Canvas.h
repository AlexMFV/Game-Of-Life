#pragma once
#include "Common.h"


//Prototypes
void DrawGrid(sf::Uint8 *pixels, int gridSize, int sizeX, int sizeY);
int AdjustGridSize(int gridSize, int w, int h);
void DrawSquare(int mouseX, int mouseY);
void DrawSquare(sf::Uint8 *pixels, Cursor cur);
Cursor GetMouseCoordinates(sf::RenderWindow& window, Cursor cursor);

//Methods
void DrawGrid(sf::Uint8 *pixels, int gridSize, int sizeX, int sizeY) {

	int rowNum = sizeY / gridSize;
	int columnNum = sizeX / gridSize;
	
	for (int aux = 0; aux < sizeX * sizeY; aux++)
	{ 
		int i = aux * 4;

		//Horizontal Lines & Vertical Lines respectively
		if (aux % columnNum < 1 || (aux / sizeX) % rowNum >= 0 && (aux / sizeX) % rowNum < 1 || (aux+1) % sizeX == 0){
			pixels[i] = gridColor.r;
			pixels[i + 1] = gridColor.g;
			pixels[i + 2] = gridColor.b;
			pixels[i + 3] = gridColor.a;
		}
		else {
			pixels[i] = backgroundColor.r;
			pixels[i + 1] = backgroundColor.g;
			pixels[i + 2] = backgroundColor.b;
			pixels[i + 3] = backgroundColor.a;
		}
	}
}

int AdjustGridSize(int gridSize, int w, int h) {
	gridSize = gridSize > w/2 ? w/2 : gridSize;

	while (w % gridSize != 0 && h % gridSize != 0)
		gridSize += 1;
	return gridSize;
}

//The overloads receive the mouseX and mouseY relative to the window, not the screen
void DrawSquare(int mouseX, int mouseY) {
	//Draw the square in the calculated position
}

void DrawSquare(sf::Uint8* pixels, Cursor cur) {
	int pixelX, pixelY;

	pixelX = floor(cur.GetX() / floor(m_width / gridSize));
	pixelY = floor(cur.GetY() / floor((m_height-1) / gridSize));

	if(pixelX >= 0 && pixelX <= floor(m_width / gridSize)
		&& pixelY >= 0 && pixelY <= floor((m_height-1) / gridSize)) {

		int squareSize = floor(m_width / gridSize);

		for (int i = 0; i < squareSize; i++)
		{
			for (int j = 0; j < squareSize; j++)
			{
				pixels[(pixelX * squareSize * 4) + (pixelY * squareSize * m_width * 4) + (i*4) + (j * m_width * 4)] = squareColor.r;
				pixels[(pixelX * squareSize * 4) + (pixelY * squareSize * m_width * 4) + (i * 4) + (j * m_width * 4) + 1] = squareColor.g;
				pixels[(pixelX * squareSize * 4) + (pixelY * squareSize * m_width * 4) + (i * 4) + (j * m_width * 4) + 2] = squareColor.b;
				pixels[(pixelX * squareSize * 4) + (pixelY * squareSize * m_width * 4) + (i * 4) + (j * m_width * 4) + 3] = squareColor.a;
			}
		}
		
		//Maybe create a new array with window dimensions, identify the squares with a 1 or 0,
		//after that, run the array and sum 4 to the pixels for each array access change colors,
		//if 1 on the array then add (255, 0, 0, 255) on pixels array, otherwise if 0
		//add (0, 0, 0, 0) to pixels[i] [i+1] [i+2] [i+3] 

		/*for (int i = 0; i < m_height; i++)
			for (int j = 0; j < m_width; j++)
				if (squarePixels[i][j] == 0 && i == pixelY && j == pixelY)
					squarePixels[i][j] = 1;*/

		//int squareSizeX = floor(m_width / gridSize);
		//int squareSizeY = floor(m_height / gridSize);
		//int x = floor(cur.GetX() / gridSize) * gridSize * pixelX;
		//int y = floor(cur.GetY() / gridSize) * gridSize;

		//for (int i = 0; i < squareSizeY; i++) {
		//	for (int j = 0; j < squareSizeX; j++) {
		//		int adjI = i * 4;
		//		int adjJ = j * 4;
		//		pixels[x + (y * m_width * 4) + j] = squareColor.r;
		//		pixels[x + (y * m_width * 4) + j + 1] = squareColor.r;
		//		pixels[x + (y * m_width * 4) + j + 2] = squareColor.r;
		//		pixels[x + (y * m_width * 4) + j + 3] = squareColor.r;

		//		/*pixels[x + ((y + i) * m_width) + j] = squareColor.r;
		//		pixels[x + ((y + i) * m_width) + j + 1] = squareColor.g;
		//		pixels[x + ((y + i) * m_width) + j + 2] = squareColor.b;
		//		pixels[x + ((y + i) * m_width) + j + 3] = squareColor.a;*/
		//	}
		//}

	}
}

Cursor GetMouseCoordinates(sf::RenderWindow& window, Cursor cursor) {
	cursor.SetPos(sf::Mouse::getPosition(window));
	return cursor;
}