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

	bool CheckOverlapCharacterControllerWithInteractables(CharacterController*);

	sf::RenderWindow* window_;

private:
	Game();

	static Game* instance_;


	ResourceManager* resource_manager_;

	std::list<Scene*>* scenes_;
	Scene* current_scene_;


	void Update();
	void Render();

	void RenderActiveObjects();
};