#pragma once
#include <list>
#include "ResourceManager.h"
#include "Scene.h"
#include "Assets.h"
#include "Graphics.h"

// Singleton
class Game {
public:
	~Game();

	static Game* instance();

	void Init(sf::RenderWindow*, ResourceManager*);
	void GameLoop();

	bool CheckOverlapWithCharacterController(SpriteRenderer*);

	sf::RenderWindow* window_;
	ResourceManager* resource_manager_;

private:
	Game();

	static Game* instance_;

	std::list<Scene*>* scenes_;
	Scene* current_scene_;


	void Update();
	void Render();

	void RenderActiveObjects();
};