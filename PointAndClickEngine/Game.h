#pragma once
#include <list>
#include "Assets.h"
#include "ResourceManager.h"
#include "Graphics.h"
#include "EntityFactory.h"

class Game {
public:
	Game();
	~Game();

	void Init(sf::RenderWindow*, ResourceManager*);
	void GameLoop();


private:
	sf::RenderWindow* window_;
	ResourceManager* resourceManager_;

	std::list<IRenderable*> activeRenderers_;


	void Update();
	void Render();

	void RenderActiveObjects();
};

