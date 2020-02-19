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

	sf::Sound testing_sound;
	SoundBufferAsset* sound_buffer_asset = dynamic_cast<SoundBufferAsset*>(resourceManager.GetAssetOfID("sfx_Door"));
	testing_sound.setBuffer(*(sound_buffer_asset->sound_buffer_));



	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (testing_sound.getStatus() != sf::SoundSource::Status::Playing) {
			testing_sound.play();
		}
		game.GameLoop();
	}

	delete(sound_buffer_asset);
	delete(gameConfig);

	return 0;
}