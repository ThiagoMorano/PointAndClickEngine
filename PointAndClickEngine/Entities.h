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

	AddComponent();


private:
	std::string id_;
	std::list<IComponent*> components_;
};

