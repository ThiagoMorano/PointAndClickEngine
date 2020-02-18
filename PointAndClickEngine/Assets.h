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
	virtual ~Asset();
};

class TextureAsset : public Asset {
public:
	sf::Texture* texture_;

	TextureAsset();
	TextureAsset(sf::Texture*);
	~TextureAsset();
};

class SoundBufferAsset : public Asset {
public:
	sf::SoundBuffer* sound_buffer_;

	SoundBufferAsset();
	SoundBufferAsset(sf::SoundBuffer*);
	~SoundBufferAsset();
};

