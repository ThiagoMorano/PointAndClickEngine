#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Forward declarations
class Entity;
class IResponse;

enum class ComponentType {
	kCharacterController,
	kSpriteRenderer,
	kAnimatedSprite,
	kAudioSource,
	kInteractable
};

class IComponent {
	friend class Entity;

public:
	virtual ~IComponent() {};
	virtual void Init() =0;
	virtual void Update(sf::Transformable*) = 0;
	virtual IComponent* GetComponent(ComponentType) = 0;
	virtual bool IsOfType(ComponentType) = 0;

protected:
	virtual void SetEntity(Entity*) = 0;
};

class IRenderable {
public:
	virtual ~IRenderable() {};
	virtual void Render(sf::RenderWindow*) = 0;
	virtual int GetRenderLayer() = 0;
};



class SpriteRenderer : public virtual IComponent, public virtual IRenderable {
public:
	Entity* entity_;
	int render_layer_;

	virtual ~SpriteRenderer();
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual void Render(sf::RenderWindow*);
	virtual int GetRenderLayer();
	virtual bool IsOfType(ComponentType);
	virtual IComponent* GetComponent(ComponentType);

	virtual void SetSprite(sf::Sprite*);
	virtual sf::Sprite* GetSprite();

	virtual bool CheckOverlap(sf::Vector2i);
	virtual bool CheckOverlap(SpriteRenderer*);

protected:
	virtual void SetEntity(Entity*);

	sf::Sprite* sprite_;
};

class AnimatedSprite : public SpriteRenderer {
public:
	float duration_;
	int number_of_keyframes_;
	int keyframe_width_;
	int keyframe_height_;

	virtual ~AnimatedSprite();
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual void Render(sf::RenderWindow*);
	virtual int GetRenderLayer();
	virtual bool IsOfType(ComponentType);
	virtual IComponent* GetComponent(ComponentType);
	
	virtual void SetSprite(sf::Texture*);
	virtual sf::Sprite* GetSprite();

	virtual bool CheckOverlap(sf::Vector2i);
	virtual bool CheckOverlap(SpriteRenderer*);

	void SetSprite(sf::Sprite*);
	

protected:
	virtual void SetEntity(Entity*);

	void NextKeyframe();

	float elapsed_time_;
	float time_per_keyframe_;

	int current_sprite_;
	std::vector<sf::Sprite*> sprites_;
};

class CharacterController : public virtual IComponent {
public:
	Entity* entity_;
	float speed_;

	virtual ~CharacterController();
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual bool IsOfType(ComponentType);
	virtual IComponent* GetComponent(ComponentType);

	bool CheckOverlap(SpriteRenderer*);
	void StopMovement();

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
	virtual bool IsOfType(ComponentType);
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
	virtual bool IsOfType(ComponentType);
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