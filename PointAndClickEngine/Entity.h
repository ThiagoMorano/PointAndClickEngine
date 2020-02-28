#pragma once
#include <list>
#include <string>
#include "Components.h"

/// Entities are game objects that belong to a scene of the game
/// An Entity works as a container of components, and its behaviour is defined by those components


class Entity {
public:
	Entity();
	Entity(std::string);
	~Entity();

	void Init();
	void Update();

	void AddComponent(IComponent*);
	IComponent* GetComponent(ComponentType);
	

	sf::Transformable transformable_;

private:
	std::string id_;
	std::list<IComponent*> components_;
};

