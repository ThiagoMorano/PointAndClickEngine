#pragma once
#include "Entity.h"

class Scene
{
public:
	std::string id_;
	std::list<Entity*> entities_;
	std::list<IRenderable*> active_renderers_;
	Scene();
	~Scene();

	void Update();
	void Render(sf::RenderWindow*);
	void AddEntity(Entity*);
};