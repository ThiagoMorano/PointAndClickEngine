#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


/// Asset objects are data containers used to hold resources that should be loaded from external files.
/// They are loaded by the ResourceManager class on its creation.
///
/// Assets are mainly used to load those resources into memory already before gameplay starts,
/// and as different game objects can make use of the same asset, this process has to be done only once.


class Asset {
public:
	std::string id_;

	Asset();
	virtual ~Asset();
};


// Holds a sf::Texture that can be used by SpriteRenderers and AnimatedSprites
class TextureAsset : public Asset {
public:
	sf::Texture* texture_;

	TextureAsset();
	TextureAsset(sf::Texture*);
	~TextureAsset();
};


// Holds a sf::SoundBuffer that can be used by AudioSources
class SoundBufferAsset : public Asset {
public:
	sf::SoundBuffer* sound_buffer_;

	SoundBufferAsset();
	SoundBufferAsset(sf::SoundBuffer*);
	~SoundBufferAsset();
};


// Holds a sf::Font that can be used by TextResponses
class FontAsset : public Asset {
public:
	sf::Font* font_;

	FontAsset();
	FontAsset(sf::Font*);
	~FontAsset();
};