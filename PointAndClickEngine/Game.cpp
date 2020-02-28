#include "Game.h"

// Get single instance
Game* Game::Instance() {
	if (instance_ == NULL) {
		instance_ = new Game();
	}
	return instance_;
}

Game::~Game() {
}

Game::Game() : resource_manager_(NULL), scenes_(NULL), current_scene_(NULL) {
}


// Initializes the game by retrieving the list of scenes and initializing Time
void Game::Init(sf::RenderWindow* window, ResourceManager* resource_manager) {
	window_ = window;
	resource_manager_ = resource_manager;

	resource_manager_->Init();
	scenes_ = resource_manager_->GetSceneList();
	current_scene_ = scenes_->front();

	Time::Instance()->Init();
}

//Advances one step in the game loop
void Game::GameLoop() {
	Time::Instance()->NewFrame();
	Update();
	Render();
}

void Game::Update() {
	current_scene_->Update();
}


void Game::Render() {
	// Clear the windows
	window_->clear();

	// Draw scene objects, and user interface in front of it
	current_scene_->Render(window_);
	user_interface_.Render(window_);

	// Displays the drawed objects
	window_->display();
}

// Called by Interactable components to check if the character controllers in the current scene are overlapping
// the interactable's sprite renderer 
bool Game::CheckOverlapWithCharacterController(SpriteRenderer* sprite_renderer) {
	return current_scene_->CheckOverlapWithCharacterController(sprite_renderer);
}

// Check for scene of specific ID and loads it
void Game::LoadSceneOfID(std::string scene_id) {
	std::list<Scene*>::iterator it;
	for (it = scenes_->begin(); it != scenes_->end(); it++) {
		if ((*it)->id_.compare(scene_id) == 0) {
			LoadScene(*it);
		}
	}
}

// Load scene, stoping it's movements
void Game::LoadScene(Scene* scene) {
	current_scene_->StopScene();
	user_interface_.StopShowingText();
	current_scene_ = scene;
}

// Activate a text in the user intereface
void Game::ActivateText(sf::Text* text, float time) {
	user_interface_.ActivateText(text, time);
}