#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class AssetData {
public:
	std::string type_;
	std::string id_;
	std::string path_;
};

class Asset {
public:
	std::string id_;

	Asset();
	~Asset();
};

class SpriteAsset : public Asset {
public:
	sf::Sprite* sprite_;

	SpriteAsset();
	SpriteAsset(sf::Sprite*);
	~SpriteAsset();
};

class SoundAsset : public Asset {
public:
	sf::Sound* sound_;

	SoundAsset();
	SoundAsset(sf::Sound*);
	~SoundAsset();
};

