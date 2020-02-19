#pragma once
#include "Graphics.h"
#include <SFML/Audio.hpp>

enum ComponentType {
	kSpriteRenderer, kAudioSource
};


class IComponent
{
public:
	virtual ~IComponent() {};
	virtual ComponentType GetComponentType() = 0;
};

class SpriteRenderer : public IRenderable, IComponent {
public:
	sf::Sprite* sprite_;

	virtual ~SpriteRenderer();
	virtual ComponentType GetComponentType();
	virtual void Render(sf::RenderWindow* window);
};

class AudioSource : public IComponent {
public:
	sf::Sound* sound_;

	virtual ~AudioSource();
	virtual ComponentType GetComponentType();

	void Play();
	bool IsPlaying();
};