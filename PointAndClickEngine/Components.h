#pragma once
#include "Graphics.h"

class IComponent
{
	virtual ~IComponent() {};
};

class SpriteRenderer : public IRenderable {
public:
	sf::Sprite* sprite_;

	virtual ~SpriteRenderer();
	virtual void Render(sf::RenderWindow* window);
};