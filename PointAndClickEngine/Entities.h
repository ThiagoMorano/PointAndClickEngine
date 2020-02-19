#pragma once
#include "Graphics.h"

class Entity : public IRenderable {
public:
	sf::Sprite* sprite_;


	virtual void Render(sf::RenderWindow* window);
};

class EntityData {
public:
	std::string type_;
	std::string id_;
};
