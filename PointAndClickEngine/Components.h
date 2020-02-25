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
	virtual void Update(sf::Transformable*) = 0;
	virtual ComponentType GetComponentType() = 0;
};

class SpriteRenderer : public virtual IComponent, public virtual IRenderable {
public:
	sf::Sprite* sprite_;

	virtual ~SpriteRenderer();
	virtual void Render(sf::RenderWindow*);
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();
};

class AudioSource : public virtual IComponent {
public:
	sf::Sound* sound_;

	virtual ~AudioSource();
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();

	void Play();
	bool IsPlaying();
};