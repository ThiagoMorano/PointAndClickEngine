#pragma once
#include <list>
#include "ResourceManager.h"
#include "Scene.h"
#include "Assets.h"
#include "Graphics.h"


class Game {
public:
	Game();
	~Game();

	void Init(sf::RenderWindow*, ResourceManager*);
	void GameLoop();

	static sf::RenderWindow* window_;
private:

	ResourceManager* resource_manager_;

	std::list<Scene*>* scenes_;
	Scene* current_scene_;


	void Update();
	void Render();

	void RenderActiveObjects();
};

