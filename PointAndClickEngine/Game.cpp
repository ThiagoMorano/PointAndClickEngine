#include "Game.h"


Game::~Game() {
}

Game::Game() : window_(NULL), resourceManager_(NULL) {
}


void Game::Init(sf::RenderWindow* window, ResourceManager* resourceManager) {
	window_ = window;
	resourceManager_ = resourceManager;

	//testing code
	sf::Sprite* testing_sprite = new sf::Sprite();
	TextureAsset* texture_asset = dynamic_cast<TextureAsset*>(resourceManager_->GetAssetOfID("spr_Door"));
	testing_sprite->setTexture(*(texture_asset->texture_));

	EntityFactory entityFactory;

	Entity* testing_entity;
	testing_entity = entityFactory.CreateEntity(NULL);

	testing_entity->sprite_ = testing_sprite;

	activeRenderers_.push_back((IRenderable*)(testing_entity));
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