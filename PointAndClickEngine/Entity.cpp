#include "Entity.h"


Entity::~Entity() {
	std::list<IComponent*>::iterator it;
	for (it = components_.begin(); it != components_.end(); it++) {
		delete(*it);
	}
}

void Entity::Init() {
	std::list<IComponent*>::iterator it;
	for (it = components_.begin(); it != components_.end(); it++) {
		(*it)->Init();
	}
}

void Entity::Update() {
	std::list<IComponent*>::iterator it;
	for (it = components_.begin(); it != components_.end(); it++) {
		(*it)->Update(&transformable_);
	}
}

void Entity::AddComponent(IComponent* component) {
	component->SetEntity(this);
	components_.push_back(component);
}

IComponent* Entity::GetComponent(ComponentType componentType) {
	std::list<IComponent*>::iterator it;
	for (it = components_.begin(); it != components_.end(); it++) {
		if ((*it)->GetComponentType() == componentType) {
			return *it;
		}
	}
	return NULL;
}

Entity::Entity() {}
Entity::Entity(std::string id) :id_(id) {}
