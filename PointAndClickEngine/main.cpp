#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "rapidxml-1.13/rapidxml.hpp"

#include "ResourceManager.h"
#include "GameManager.h"

ResourceManager* resourceManager = new ResourceManager("game.xml");

GameManager* gameManager = new GameManager();

int main() {
	GameConfig* gameConfig = resourceManager->GetGameConfig();

	sf::RenderWindow window(sf::VideoMode(gameConfig->screen_width_, gameConfig->screen_height_), gameConfig->application_name_);
	window.setFramerateLimit(gameConfig->fps);

	gameManager->asset_list_ = resourceManager->GetAssetList();

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}



		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}