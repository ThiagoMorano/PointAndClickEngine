#pragma once
#include <list>
#include <string>
#include "Components.h"

class EntityData {
public:
	std::list<std::string> components_;
	std::string id_;
};


class Entity {
public:
	Entity();
	Entity(std::string);
	~Entity();

	void Update();

	void AddComponent(IComponent*);
	IComponent* GetComponent(ComponentType);

private:
	std::string id_;
	std::list<IComponent*> components_;
};

