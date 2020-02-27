#pragma once
#include <list>
#include "ResourceManager.h"
#include "Time.h"
#include "Scene.h"
#include "Assets.h"


// Singleton
class Game {
public:
	~Game();

	static Game* Instance();

	void Init(sf::RenderWindow*, ResourceManager*);
	void GameLoop();

	bool CheckOverlapWithCharacterController(SpriteRenderer*);

	void LoadSceneOfID(std::string);
	void LoadScene(Scene*);

	void ActivateText(sf::Text*, float);

	sf::RenderWindow* window_;
	ResourceManager* resource_manager_;

private:
	Game();

	static Game* instance_;

	std::list<Scene*>* scenes_;
	Scene* current_scene_;
	
	sf::Text text_to_show_;

	void Update();
	void Render();

	void RenderActiveObjects();
};