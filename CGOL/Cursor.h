#pragma once
#include "SFML/Graphics.hpp"

class Cursor {

private:
	int x;
	int y;
	int buttonPressed = -1; //-1 = None, 0 = Left, 1 = Right, 2 = MiddleWheel, 3 = ExtraButton1, 4 = ExtraButton2

public:
	Cursor(int _x, int _y);
	Cursor(int _x, int _y, int _button);
	void SetPos(int _x, int _y);
	void SetPos(sf::Vector2i _pos);
	int GetX();
	int GetY();
};