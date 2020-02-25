#pragma once
#include "Graphics.h"
#include <SFML/Audio.hpp>

enum class ComponentType {
	kCharacterController, kSpriteRenderer, kAudioSource
};

class IComponent
{
public:
	virtual ~IComponent() {};
	virtual void Update(sf::Transformable*) = 0;
	virtual ComponentType GetComponentType() = 0;
};

class CharacterController : public virtual IComponent {
public:
	float speed;

	virtual ~CharacterController();
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();

private:
	bool should_move_;
	sf::Vector2f destination_;
	sf::Vector2f direction_;


	void CalculateDirection(sf::Transformable*);
	void Move(sf::Transformable*);
	bool ArrivedAtDestination(sf::Transformable*);
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


