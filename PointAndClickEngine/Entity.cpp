#include "Entity.h"


Entity::~Entity() {
	std::list<IComponent*>::iterator it;
	for (it = components_.begin(); it != components_.end(); it++) {
		delete(*it);
	}
}

void Entity::AddComponent(IComponent* component) {
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