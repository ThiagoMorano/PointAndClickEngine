#include "Components.h"

SpriteRenderer::~SpriteRenderer() {
	delete(sprite_);
}

void SpriteRenderer::Render(sf::RenderWindow* window) {
	window->draw(*sprite_);
}

