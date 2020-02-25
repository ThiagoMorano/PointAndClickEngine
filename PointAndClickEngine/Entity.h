#pragma once
#include <list>
#include <string>
#include "Components.h"

class Entity {
public:
	Entity();
	Entity(std::string);
	~Entity();

	void Update();

	void AddComponent(IComponent*);
	IComponent* GetComponent(ComponentType);
	

	sf::Transformable transformable_;

private:
	std::string id_;
	std::list<IComponent*> components_;
};

