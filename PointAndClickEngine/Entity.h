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
	~Entity();

	void Update();

	void AddComponent(IComponent*);
	IComponent* GetComponent(ComponentType);

	// 
	//template <typename T> T* GetComponent(ComponentType) {
	//	return NULL;
	//}

	//template <typename T> bool HasComponent() {
	//	return false;
	//}

private:
	std::string id_;
	std::list<IComponent*> components_;
};

