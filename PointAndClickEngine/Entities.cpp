#include "Entities.h"

void Entity::Render(sf::RenderWindow* window) {
	window->draw(*sprite_);
}

