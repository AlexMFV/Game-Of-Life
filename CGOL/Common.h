#pragma once

sf::Color gridColor(0, 0, 0, 255); //Default: (71, 71, 71, 255)
sf::Color backgroundColor(255, 255, 255, 255); //Default (255, 255, 255, 255)
bool isGridActive = true;
int gridSize = 20; //Ammout of "pixels" that make the grid ex: 5 = 5x5 grid
int m_width = 800;
int m_height = 800;

bool ChangeStatus(bool value) {
	if (value)
		return false;
	return true;
}