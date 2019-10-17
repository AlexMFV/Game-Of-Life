#pragma once
#include "Common.h"
#include <vector>

//Prototypes
void DrawGrid(sf::Uint8* pixels, int gridSize, int sizeX, int sizeY);
int AdjustGridSize(int gridSize, int w, int h);
void DrawSquare(sf::Uint8* pixels, Cursor cur, bool draw);
void DrawSquare(sf::Uint8* pixels, int x, int y, bool draw);
void Process(sf::Uint8* pixels, int pixelX, int pixelY, bool draw);
Cursor GetMouseCoordinates(sf::RenderWindow& window, Cursor cursor);
void ProcessSquares(sf::Uint8* pixels);
bool Check(sf::Uint8* pixels, int x, int y, int squareSize);
int Neighbours(sf::Uint8* pixels, int x, int y, int size);
sf::Color GetSquareColor(sf::Uint8* pixels, int x, int y, int size);
int Formula(int x, int y, int size);

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

void DrawSquare(sf::Uint8* pixels, int x, int y, bool draw) { Process(pixels, x, y, draw); }

void DrawSquare(sf::Uint8* pixels, Cursor cur, bool draw) {
	int pixelX, pixelY;

	pixelX = floor(cur.GetX() / floor(m_width / gridSize));
	pixelY = floor(cur.GetY() / floor((m_height - 1) / gridSize));

	Process(pixels, pixelX, pixelY, draw);
}

void Process(sf::Uint8* pixels, int pixelX, int pixelY, bool draw) {
	if (pixelX >= 0 && pixelX < m_width / floor(m_width / gridSize)
		&& pixelY >= 0 && pixelY < (m_height - 1) / floor((m_height - 1) / gridSize)) {

		int squareSize = floor(m_width / gridSize);

		//The color in which the square is drawn
		sf::Color color;

		if (draw)
			color = squareColor;
		else
			color = transp;

		int i, j;
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

void ProcessSquares(sf::Uint8* pixels) {
	int size = m_width * m_height * 4;
	int squareSize = floor(m_width / gridSize);

	int drawAux = -1;
	int deleteAux = -1;

	std::vector<int> toDraw;
	std::vector<int> toDelete;

	for (int y = 0; y < gridSize; y++) {
		for (int x = 0; x < gridSize; x++) {
			if (Check(pixels, x, y, squareSize))
				toDraw.push_back((x + y * gridSize));
			else
				if(GetSquareColor(pixels, x, y, squareSize) == squareColor)
					toDelete.push_back((x + y * gridSize));
		}
	}

	for (auto i = toDraw.begin(); i != toDraw.end(); i++) {
		int y = *i > gridSize-1 ? floor(*i / gridSize) : 0;
		int x = *i - (gridSize * y);
		DrawSquare(pixels, x, y, true);
	}

	for (auto i = toDelete.begin(); i != toDelete.end(); i++) {
		int y = *i > gridSize-1 ? floor(*i / gridSize) : 0;
		int x = *i - (gridSize * y);
		DrawSquare(pixels, x, y, false);
	}
}

bool Check(sf::Uint8* pixels, int x, int y, int squareSize) {

	//First determine if dead or alive, then check how many neighbors, then draw accordingly
	bool isAlive = GetSquareColor(pixels, x, y, squareSize) == squareColor ? true : false;
	int neibs = Neighbours(pixels, x, y, squareSize);

	if (isAlive) {
		//If alive and population > 3 || < 2, dies
		if (neibs > 3 || neibs < 2)
			return false;

		//If alive and population = 3 || 2, lives
		if (neibs == 3 || neibs == 2)
			return true;
	}
	else {
		//If dead and population = 3, lives
		if (neibs == 3)
			return true;
		return false;
	}
}

int Neighbours(sf::Uint8* pixels, int x, int y, int size) {
	int count = 0;

	////////////////////////////////////////////// THIS WILL NEED A LOT OF IMPROVEMENTS //////////////////////////////////////////////////////
	//Very rough idea of how its supposed to be

	//Count the number of neighbours of the given cell
	//Top left
	if (x-1 >= 0 && y-1 >= 0)
		if(GetSquareColor(pixels, x-1, y-1, size) == squareColor)
			count++;

	//Top mid
	if (x >= 0 && y-1 >= 0)
		if(GetSquareColor(pixels, x, y-1, size) == squareColor)
			count++;

	//Top right
	if (x+1 < gridSize && y-1 >= 0)
		if(GetSquareColor(pixels, x+1, y-1, size) == squareColor)
			count++;

	//Middle left
	if (x-1 >= 0 && y >= 0)
		if(GetSquareColor(pixels, x-1, y, size) == squareColor)
			count++;

	//Middle mid its the provided cell so it does not count
	//if (x >= 0 && y >= 0)
	//	if(GetSquareColor(pixels, x, y, size) == squareColor)
	//		count++;
	
	//Middle right
	if (x+1 < gridSize && y >= 0)
		if(GetSquareColor(pixels, x+1, y, size) == squareColor)
			count++;

	//Bottom left
	if (x-1 >= 0 && y+1 < gridSize)
		if(GetSquareColor(pixels, x-1, y+1, size) == squareColor)
			count++;

	//Bottom mid
	if (x >= 0 && y+1 < gridSize)
		if(GetSquareColor(pixels, x, y+1, size) == squareColor)
			count++;

	//Bottom right
	if (x+1 < gridSize && y+1 < gridSize)
		if(GetSquareColor(pixels, x+1, y+1, size) == squareColor)
			count++;

	return count;
}

sf::Color GetSquareColor(sf::Uint8* pixels, int x, int y, int size) {
	sf::Color sc;
	int pixel = Formula(x, y, size);

	sc.r = pixels[pixel];
	sc.g = pixels[pixel+1];
	sc.b = pixels[pixel+2];
	sc.a = pixels[pixel+3];

	return sc;
}

//Transforms cartesian values (x, y) to "pixel number"
int Formula(int x, int y, int size) {
	return (x * size * 4) + (y * size * m_width * 4) + 4;
}