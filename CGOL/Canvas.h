#pragma once
#include "Common.h"


//Prototypes
void DrawGrid(sf::Uint8* pixels, int gridSize, int sizeX, int sizeY);
int AdjustGridSize(int gridSize, int w, int h);
void DrawSquare(sf::Uint8* pixels, Cursor cur, bool type);
Cursor GetMouseCoordinates(sf::RenderWindow& window, Cursor cursor);

//Methods
void DrawGrid(sf::Uint8* pixels, int gridSize, int sizeX, int sizeY) {

	int rowNum = sizeY / gridSize;
	int columnNum = sizeX / gridSize;

	for (int aux = 0; aux < sizeX * sizeY; aux++)
	{
		int i = aux * 4;

		//Horizontal Lines & Vertical Lines respectively
		if (aux % columnNum < 1 || (aux / sizeX) % rowNum >= 0 && (aux / sizeX) % rowNum < 1 || (aux + 1) % sizeX == 0) {
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
	gridSize = gridSize > w / 2 ? w / 2 : gridSize;

	while (w % gridSize != 0 && h % gridSize != 0)
		gridSize += 1;
	return gridSize;
}

void DrawSquare(sf::Uint8* pixels, Cursor cur, bool draw) {

	int pixelX, pixelY;

	pixelX = floor(cur.GetX() / floor(m_width / gridSize));
	pixelY = floor(cur.GetY() / floor((m_height - 1) / gridSize));

	if (pixelX >= 0 && pixelX < m_width / floor(m_width / gridSize)
		&& pixelY >= 0 && pixelY < (m_height - 1) / floor((m_height - 1) / gridSize)) {

		int squareSize = floor(m_width / gridSize);
		
		//The color in which the square is drawn
		sf::Color color;

		if (draw)
			color = squareColor;
		else
			color = backgroundColor;
		
		int i,j;
		for (draw ? i = 0 : i = 1; i < squareSize; i++)
		{
			for (draw ? j = 0 : j = 1; j < squareSize; j++)
			{
				int calculate = (pixelX * squareSize * 4) + (pixelY * squareSize * m_width * 4) + (i * 4) + (j * m_width * 4);
				
				pixels[calculate] = color.r;
				pixels[calculate + 1] = color.g;
				pixels[calculate + 2] = color.b;
				pixels[calculate + 3] = color.a;
			}
		}
	}
}

Cursor GetMouseCoordinates(sf::RenderWindow& window, Cursor cursor) {
	cursor.SetPos(sf::Mouse::getPosition(window));
	return cursor;
}