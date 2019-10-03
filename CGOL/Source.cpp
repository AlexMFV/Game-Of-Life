#include <SFML/Graphics.hpp>
#include <stdint.h>

int main() {

	sf::RenderWindow window(sf::VideoMode(200, 200), "Conway's Game Of Life");

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();
		}

		window.clear();
		//window.draw();
		window.display();
	}

	return 0;
}