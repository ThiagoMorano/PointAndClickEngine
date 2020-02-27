#include "Game.h"

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


void Game::Init(sf::RenderWindow* window, ResourceManager* resource_manager) {
	window_ = window;
	resource_manager_ = resource_manager;

	resource_manager_->Init();
	scenes_ = resource_manager_->GetSceneList();
	current_scene_ = scenes_->front();

	Time::Init();

}

void Game::GameLoop() {
	Time::Instance()->NewFrame();
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

bool Game::CheckOverlapWithCharacterController(SpriteRenderer* sprite_renderer) {
	return current_scene_->CheckOverlapWithCharacterController(sprite_renderer);
}

void Game::LoadSceneOfID(std::string scene_id) {
	std::list<Scene*>::iterator it;
	for (it = scenes_->begin(); it != scenes_->end(); it++) {
		if ((*it)->id_.compare(scene_id) == 0) {
			LoadScene(*it);
		}
	}
}

void Game::LoadScene(Scene* scene) {
	std::list<CharacterController*>::iterator it;
	for (it = (current_scene_->character_controllers_).begin(); it != (current_scene_->character_controllers_).end(); it++) {
		(*it)->StopMovement();
	}
	current_scene_ = scene;
}


void Game::ActivateText(sf::Text* text, float time) {
	current_scene_->ActivateText(text, time);
}