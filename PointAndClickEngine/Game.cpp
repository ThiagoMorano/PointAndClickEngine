#include "Game.h"


Game* Game::instance() {
	if (instance_ == NULL) {
		instance_ = new Game();
	}
	return instance_;
}

Game::~Game() {
}

Game::Game() : resource_manager_(NULL), scenes_(NULL), current_scene_(NULL) {
}


void Game::Init(sf::RenderWindow* window, ResourceManager* resource_manager) {
	window_ = window;
	resource_manager_ = resource_manager;

	scenes_ = resource_manager_->GetSceneList();
	current_scene_ = scenes_->front();
}

void Game::GameLoop() {
	Update();
	Render();
}

void Game::Update() {
	current_scene_->Update();
}

void Game::Render() {
	window_->clear();
	current_scene_->Render(window_);
	window_->display();
}

void Game::RenderActiveObjects() {
	std::list<IRenderable*>::iterator iterator;
}

bool Game::CheckOverlapCharacterControllerWithInteractables(CharacterController* character_controller) {
	return current_scene_->CheckOverlapCharacterControllerWithInteractables(character_controller);
}