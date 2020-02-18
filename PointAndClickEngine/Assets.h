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

class TextureAsset : public Asset {
public:
	sf::Texture* texture_;

	TextureAsset();
	TextureAsset(sf::Texture*);
	~TextureAsset();
};

class SoundAsset : public Asset {
public:
	sf::Sound* sound_;

	SoundAsset();
	SoundAsset(sf::Sound*);
	~SoundAsset();
};

