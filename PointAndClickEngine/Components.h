#pragma once
#include "Graphics.h"
#include <SFML/Audio.hpp>

class Entity;

enum class ComponentType {
	kCharacterController,
	kSpriteRenderer,
	kAudioSource,
	kInteractable
};

class IComponent
{
	friend class Entity;

public:
	virtual ~IComponent() {};
	virtual void Update(sf::Transformable*) = 0;
	virtual ComponentType GetComponentType() = 0;
	virtual IComponent* GetComponent(ComponentType) = 0;

protected:
	virtual void SetEntity(Entity*) = 0;
};

class CharacterController : public virtual IComponent {
public:
	Entity* entity_;
	float speed_;

	virtual ~CharacterController();
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();
	virtual IComponent* GetComponent(ComponentType);

	bool CheckOverlapWithInteractable();

private:
	bool should_move_;
	sf::Vector2f destination_;
	sf::Vector2f direction_;


	void CalculateDirection(sf::Transformable*);
	void Move(sf::Transformable*);
	bool ArrivedAtDestination(sf::Transformable*);

protected:
	virtual void SetEntity(Entity*);
};

class SpriteRenderer : public virtual IComponent, public virtual IRenderable {
public:
	Entity* entity_;
	sf::Sprite* sprite_;

	virtual ~SpriteRenderer();
	virtual void Render(sf::RenderWindow*);
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();
	virtual IComponent* GetComponent(ComponentType);

	bool PositionWithinSprite(sf::Vector2i);

protected:
	virtual void SetEntity(Entity*);
};

class AudioSource : public virtual IComponent {
public:
	Entity* entity_;
	sf::Sound* sound_;

	virtual ~AudioSource();
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();
	virtual IComponent* GetComponent(ComponentType);

	void Play();
	void Stop();
	bool IsPlaying();

protected:
	virtual void SetEntity(Entity*);
};

class Interactable : public virtual IComponent {
public:
	Entity* entity_;

	virtual ~Interactable();
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();
	virtual IComponent* GetComponent(ComponentType);

	bool WasClickedOn();
	bool OverlappingCharacterController();
	void Interact();

	SpriteRenderer* sprite_renderer_;

private:
	bool was_clicked_on_;

protected:
	virtual void SetEntity(Entity*);
};