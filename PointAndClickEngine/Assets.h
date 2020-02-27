#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

class FontAsset : public Asset {
public:
	sf::Font* font_;

	FontAsset();
	FontAsset(sf::Font*);
	~FontAsset();
};