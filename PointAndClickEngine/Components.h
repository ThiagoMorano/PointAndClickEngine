#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/// Components are responsible for each behaviour that an Entity can have


//Forward declarations
class Entity;
class IResponse;


// Each type of component is defined within this enum class
enum class ComponentType {
	kCharacterController,
	kSpriteRenderer,
	kAnimatedSprite,
	kAudioSource,
	kInteractable
};


// For a class to be a component, it must implement the IComponent interface
class IComponent {
	friend class Entity;

public:
	virtual ~IComponent() {};
	
	// Called by the holding Entity to initialize the components after all its components have been instantiated.
	virtual void Init() =0;

	// Called by the holding Entity to simulated the behaviour of components that are time dependent.
	virtual void Update(sf::Transformable*) = 0;

	// Returns component of given type that is attached to the holding entity. Returns NULL if there's no such component.
	virtual IComponent* GetComponent(ComponentType) = 0;

	// Returns true if the component is of the given type.
	virtual bool IsOfType(ComponentType) = 0;

protected:
	// Called by the holding Entity (friend class) once the component is instantiated.
	virtual void SetEntity(Entity*) = 0;
};


// For a component to be able to draw in the screen, i.e., to be included in the active renderers of a scene,
// they must implement the IRenderable interface
class IRenderable {
public:
	virtual ~IRenderable() {};

	// Draws the object in the given sf::RenderWindow.
	virtual void Render(sf::RenderWindow*) = 0;
	
	// Returns the render layer the object is on.
	virtual int GetRenderLayer() = 0;
};


// A sprite renderer defines a single sprite that an object draws
// The component is also necessary for checking for overlaps between objects,
// as the feature uses sf::Rect of sf::Sprite to check for intersections
class SpriteRenderer : public virtual IComponent, public virtual IRenderable {
public:
	virtual ~SpriteRenderer();

	// IComponent
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual IComponent* GetComponent(ComponentType);
	virtual bool IsOfType(ComponentType);

	// IRendereable
	virtual void Render(sf::RenderWindow*);
	virtual int GetRenderLayer();
	
	virtual sf::Sprite* GetSprite();
	virtual void InitSprite(sf::Texture*);
	virtual bool CheckOverlap(sf::Vector2i);
	virtual bool CheckOverlap(SpriteRenderer*);

	Entity* entity_;
	int render_layer_;

protected:
	virtual void SetEntity(Entity*);

	sf::Sprite* sprite_;
};


// AnimatedSprites define a set of keyframes (sprites) that are used to display an animation.
// It extends SpriteRenderer as it also should check for overlaps.
class AnimatedSprite : public SpriteRenderer {
public:
	virtual ~AnimatedSprite();
	
	// IComponent
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual IComponent* GetComponent(ComponentType);
	virtual bool IsOfType(ComponentType);
	
	// IRenderable
	virtual void Render(sf::RenderWindow*);
	virtual int GetRenderLayer();
	
	// extends SpriteRenderer
	virtual sf::Sprite* GetSprite();
	virtual void InitSprite(sf::Texture*);
	virtual bool CheckOverlap(sf::Vector2i);
	virtual bool CheckOverlap(SpriteRenderer*);

	float duration_;
	int number_of_keyframes_;
	int keyframe_width_;
	int keyframe_height_;

protected:
	virtual void SetEntity(Entity*);

	void NextKeyframe();

	float elapsed_time_;
	float time_per_keyframe_;

	int current_sprite_;
	std::vector<sf::Sprite*> sprites_;
};


// Character Controller defines that an object can move responding to clicks.
// Ideally only the player object would have this component, as it's used to trigger
// interactions with Interactable components
class CharacterController : public virtual IComponent {
public:
	virtual ~CharacterController();

	// IComponent
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual IComponent* GetComponent(ComponentType);
	virtual bool IsOfType(ComponentType);

	bool CheckOverlap(SpriteRenderer*);
	void StopMovement();


	Entity* entity_;
	float speed_;

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


// AudioSource allows object to play sounds in the scene.
class AudioSource : public virtual IComponent {
public:
	virtual ~AudioSource();

	// IComponent
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual IComponent* GetComponent(ComponentType);
	virtual bool IsOfType(ComponentType);

	void Play();
	void Stop();
	bool IsPlaying();

	Entity* entity_;
	sf::Sound* sound_;

protected:
	virtual void SetEntity(Entity*);
};


// The Interactable component assigns interactivity to game objects.
// The component checks for sf::Mouse::Left in its Update, and if the object was clicked
// it sets was_clicked_on_ to true.
// After being clicked, it starts checking for overlaps with a CharacterController, and if this overlap
// occurs, the Interact() method is called, which calls Invoke() of each of the responses.
class Interactable : public virtual IComponent {
public:
	virtual ~Interactable();

	// IComponent
	virtual void Init();
	virtual void Update(sf::Transformable*);
	virtual IComponent* GetComponent(ComponentType);
	virtual bool IsOfType(ComponentType);

	void AddResponse(IResponse*);

	bool WasClickedOn();
	bool CheckOverlapWithCharacterControllers();
	void Interact();

	Entity* entity_;
	std::list<IResponse*> responses_;

private:
	bool was_clicked_on_;
	SpriteRenderer* sprite_renderer_;

protected:
	virtual void SetEntity(Entity*);
};