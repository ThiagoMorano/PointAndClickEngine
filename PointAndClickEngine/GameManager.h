#pragma once
#include <list>
#include "Assets.h"
#include "Graphics.h"

class Game {
public:
	Game();
	~Game();

	void Init(sf::RenderWindow*);
	void GameLoop();


private:
	sf::RenderWindow* window_;

	std::list<IRenderable*> activeRenderers_;



	void Update();
	void Render();

	void RenderObjects();
};

