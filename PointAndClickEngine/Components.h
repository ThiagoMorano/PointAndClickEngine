#pragma once
#include "Graphics.h"
#include <SFML/Audio.hpp>

enum class ComponentType {
	kSpriteRenderer, kAudioSource
};

class IComponent
{
public:
	virtual ~IComponent() {};
	virtual void Update() = 0;
	virtual ComponentType GetComponentType() = 0;
};

class SpriteRenderer : public IRenderable, public IComponent {
public:
	sf::Sprite* sprite_;

	virtual ~SpriteRenderer();
	virtual void Render(sf::RenderWindow*);
	virtual void Update();
	virtual ComponentType GetComponentType();
};

class AudioSource : public IComponent {
public:
	sf::Sound* sound_;

	virtual ~AudioSource();
	virtual void Update();
	virtual ComponentType GetComponentType();

	void Play();
	bool IsPlaying();
};