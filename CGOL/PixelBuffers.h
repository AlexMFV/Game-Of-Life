#pragma once

sf::Uint8* gridPixelBuffer = new sf::Uint8[m_width * m_height * 4];
sf::Uint8* squaresPixelBuffer = new sf::Uint8[m_width * m_height * 4];
sf::Uint8* bgPixelBuffer = new sf::Uint8[m_width * m_height * 4];

//int** squarePixels = new int* [m_height];
//int squarePixels[m_height][m_width];