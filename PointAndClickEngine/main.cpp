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

	sf::Sprite testing_sprite;
	TextureAsset* texture_asset = dynamic_cast<TextureAsset*>(resourceManager->GetAssetOfID("spr_Door"));
	testing_sprite.setTexture(*(texture_asset->texture_));

	sf::Sound testing_sound;
	SoundBufferAsset* sound_buffer_asset = dynamic_cast<SoundBufferAsset*>(resourceManager->GetAssetOfID("sfx_Door"));
	testing_sound.setBuffer(*(sound_buffer_asset->sound_buffer_));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}



		window.clear();
		if (testing_sound.getStatus() != sf::SoundSource::Status::Playing) {
			testing_sound.play();
		}
		window.draw(testing_sprite);
		window.display();
	}

	return 0;
}