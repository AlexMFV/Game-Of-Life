#include "SFML/Graphics.hpp"
#include "Cursor.h"

Cursor::Cursor(int _x, int _y) {
	x = _x;
	y = _y;
}

Cursor::Cursor(int _x, int _y, int _button) {
	x = _x;
	y = _y;
	buttonPressed = _button;
}

void Cursor::SetPos(int _x, int _y) {
	x = _x;
	y = _y;
}

void Cursor::SetPos(sf::Vector2i _pos) {
	x = _pos.x;
	y = _pos.y;
}

int Cursor::GetX() {
	return x;
}

int Cursor::GetY() {
	return y;
}