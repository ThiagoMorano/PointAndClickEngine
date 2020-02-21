#pragma once
#include <list>
#include "Assets.h"
#include "ResourceManager.h"
#include "Graphics.h"
#include "EntityFactory.h"
#include "Scene.h"

class Game {
public:
	Game();
	~Game();

	void Init(sf::RenderWindow*, ResourceManager*);
	void GameLoop();


private:
	sf::RenderWindow* window_;
	ResourceManager* resource_manager_;

	std::list<Scene*>* scenes_;
	Scene* current_scene_;

	//std::list<Entity*> entities_;
	//std::list<IRenderable*> active_renderers_;

	//AudioSource* audio_source;


	void Update();
	void Render();

	void RenderActiveObjects();
};
