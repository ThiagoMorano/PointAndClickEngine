#include "Entity.h"


Entity::~Entity() {
	std::list<IComponent*>::iterator it;
	for (it = components_.begin(); it != components_.end(); it++) {
		delete(*it);
	}
}

// Initializes all components.
// Used to initializes them after all components have been instantiated and added.
void Entity::Init() {
	std::list<IComponent*>::iterator it;
	for (it = components_.begin(); it != components_.end(); it++) {
		(*it)->Init();
	}
}

// Calls update method of each behaviour
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

// Check if entity has a component of given type and returns it.
IComponent* Entity::GetComponent(ComponentType component_type) {
	std::list<IComponent*>::iterator it;
	for (it = components_.begin(); it != components_.end(); it++) {
		if ((*it)->IsOfType(component_type)) {
			return *it;
		}
	}
	return NULL;
}

Entity::Entity() {}
Entity::Entity(std::string id) :id_(id) {}
