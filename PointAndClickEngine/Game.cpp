#include "Game.h"


Game::~Game() {
}

Game::Game() : window_(NULL) {
}


void Game::Init(sf::RenderWindow* window) {
	window_ = window;
}

void Game::GameLoop() {
	Update();
	Render();
}

void Game::Update() {

}

void Game::Render() {
	window_->clear();

	RenderObjects();

	window_->display();
}

void Game::RenderObjects() {
	std::list<IRenderable*>::iterator iterator;
	for (iterator = activeRenderers_.begin(); iterator != activeRenderers_.end(); iterator++) {
		(*iterator)->Render(window_);
	}
}