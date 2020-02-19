#include "Entity.h"

void Entity::AddComponent(IComponent* component) {
	components_.push_back(component);
}