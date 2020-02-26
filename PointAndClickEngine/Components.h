#pragma once
#include "Graphics.h"
#include <list>
#include <SFML/Audio.hpp>

//Forward declarations
class Entity;
class IResponse;

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
	virtual void Init() =0;
	virtual void Update(sf::Transformable*) = 0;
	virtual ComponentType GetComponentType() = 0;
	virtual IComponent* GetComponent(ComponentType) = 0;

protected:
	virtual void SetEntity(Entity*) = 0;
};

class SpriteRenderer : public virtual IComponent, public virtual IRenderable {
public:
	Entity* entity_;

	virtual ~SpriteRenderer();
	virtual void Init();
	virtual void Render(sf::RenderWindow*);
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();
	virtual IComponent* GetComponent(ComponentType);

	void SetSprite(sf::Sprite*);

	bool CheckOverlap(sf::Vector2i);

	bool CheckOverlap(SpriteRenderer*);

protected:
	virtual void SetEntity(Entity*);

	sf::Sprite* sprite_;
};

class CharacterController : public virtual IComponent {
public:
	Entity* entity_;
	float speed_;

	virtual ~CharacterController();
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();
	virtual IComponent* GetComponent(ComponentType);

	bool CheckOverlap(SpriteRenderer*);

private:
	bool should_move_;
	sf::Vector2f destination_;
	sf::Vector2f direction_;

	SpriteRenderer* sprite_renderer_;

	void CalculateDirection(sf::Transformable*);
	void Move(sf::Transformable*);
	bool ArrivedAtDestination(sf::Transformable*);

protected:
	virtual void SetEntity(Entity*);
};

class AudioSource : public virtual IComponent {
public:
	Entity* entity_;
	sf::Sound* sound_;

	virtual ~AudioSource();
	virtual void Init();
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
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual ComponentType GetComponentType();
	virtual IComponent* GetComponent(ComponentType);


	void AddResponse(IResponse*);

	bool WasClickedOn();
	bool CheckOverlapWithCharacterControllers();
	void Interact();

	std::list<IResponse*> responses_;

private:
	bool was_clicked_on_;
	SpriteRenderer* sprite_renderer_;

protected:
	virtual void SetEntity(Entity*);
};