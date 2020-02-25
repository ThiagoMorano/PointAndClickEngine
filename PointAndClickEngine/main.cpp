#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "rapidxml-1.13/rapidxml.hpp"

#include "ResourceManager.h"
#include "Game.h"

int main() {
	ResourceManager resource_manager("game.xml");
	Game game;

	GameConfig* gameConfig = resource_manager.GetGameConfig();

	sf::RenderWindow window(sf::VideoMode(gameConfig->screen_width_, gameConfig->screen_height_), gameConfig->application_name_);
	window.setFramerateLimit(gameConfig->fps);

	game.Init(&window, &resource_manager);

	sf::Sprite testing_sprite;
	TextureAsset* text = dynamic_cast<TextureAsset*>(resource_manager.GetAssetOfID("spr_Key"));
	testing_sprite.setTexture(*(text->texture_));

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