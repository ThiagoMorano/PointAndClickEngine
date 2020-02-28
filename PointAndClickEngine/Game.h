#pragma once
#include <list>
#include "ResourceManager.h"
#include "Time.h"
#include "Scene.h"
#include "Assets.h"
#include "UserInterface.h"

/// Game class is a singleton class that is responsible for the game flow.
/// Its main method is the GameLoop(), which takes care of calling Update() and Render().
///
/// The class holds references to each scene of the game in the scenes_ list, while also
/// holding a pointer to the scene that is currently active.


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

	UserInterface user_interface_;

	void Update();
	void Render();
	void RenderActiveObjects();
};