#pragma once
#include <SFML/Graphics.hpp>

class IRenderable {
public:
	virtual ~IRenderable() {};
	virtual void Render(sf::RenderWindow*) = 0;
};
