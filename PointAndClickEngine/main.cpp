/// Simple Engine for Point & Click Adventure games
///
/// This project was developed for the Game Programming module at the Cologne Game Lab. The assignment consisted of developing 
/// a small framework to enable the creation of Point & Click Adventure games. The libraries SFML and rapidXML were used to 
/// handle game interactions and external file accessibility.

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "rapidxml-1.13/rapidxml.hpp"

#include "ResourceManager.h"
#include "Game.h"


// Memory allocation for static instances of singletons
Game* Game::instance_;
Time* Time::instance_;

int main() {
	ResourceManager resource_manager("game.xml");

	GameConfig* gameConfig = resource_manager.GetGameConfig();

	sf::RenderWindow window(sf::VideoMode(gameConfig->screen_width_, gameConfig->screen_height_), gameConfig->application_name_);
	window.setFramerateLimit(gameConfig->fps);

	Game::Instance()->Init(&window, &resource_manager);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Game::Instance()->GameLoop();
	}

	delete(gameConfig);

	return 0;
}