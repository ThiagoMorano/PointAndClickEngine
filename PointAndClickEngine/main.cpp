#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "rapidxml-1.13/rapidxml.hpp"

#include "ResourceManager.h"
#include "Game.h"

ResourceManager resourceManager("game.xml");
Game game;


int main() {

	GameConfig* gameConfig = resourceManager.GetGameConfig();

	sf::RenderWindow window(sf::VideoMode(gameConfig->screen_width_, gameConfig->screen_height_), gameConfig->application_name_);
	window.setFramerateLimit(gameConfig->fps);

	game.Init(&window, &resourceManager);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		game.GameLoop();
	}

	delete(gameConfig);

	return 0;
}