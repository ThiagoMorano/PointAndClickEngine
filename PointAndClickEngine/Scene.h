#pragma once
#include "Entity.h"

/// The Scene class holds the objects that are defined in a specific screen.
/// When a scene is active, it is also responsible for propagating the Update and Render calls to its objects.

class Scene
{
public:
	Scene();
	~Scene();

	void Update();
	void Render(sf::RenderWindow*);
	void AddEntity(Entity*);
	void AddRenderer(IRenderable*);

	void StopScene();

	bool CheckOverlapWithCharacterController(SpriteRenderer*);

	std::string id_;
	std::list<Entity*> entities_;
	std::list<IRenderable*> active_renderers_0_;
	std::list<IRenderable*> active_renderers_1_;
	std::list<IRenderable*> active_renderers_2_;
	std::list<IRenderable*> active_renderers_3_;
	std::list<IRenderable*> active_renderers_4_;

	std::list<CharacterController*> character_controllers_;
};