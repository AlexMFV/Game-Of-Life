#pragma once
#include "Common.h"


//Prototypes
void DrawGrid(sf::Uint8 *pixels, int gridSize, int sizeX, int sizeY);
int AdjustGridSize(int gridSize, int w, int h);
void DrawSquare(int mouseX, int mouseY);
void DrawSquare(Cursor cur);
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

void DrawSquare(Cursor cur) {
	//Draw the square in the calculated position
}

Cursor GetMouseCoordinates(sf::RenderWindow& window, Cursor cursor) {
	cursor.SetPos(sf::Mouse::getPosition(window));
	return cursor;
}