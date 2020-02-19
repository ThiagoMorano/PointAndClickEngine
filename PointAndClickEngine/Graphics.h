#pragma once
#include <SFML/Graphics.hpp>


class IRenderable {
public:
	virtual ~IRenderable() {};
	virtual void Render(sf::RenderWindow*) = 0;
};

class Renderer : public IRenderable {
public:
	virtual ~Renderer();
	virtual void Render(sf::RenderWindow*);


private:

};