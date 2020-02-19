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

	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sprite_renderer->sprite_ = testing_sprite;

	testing_entity->AddComponent((IComponent*)sprite_renderer);

	activeRenderers_.push_back((IRenderable*)(sprite_renderer));
}

void Game::GameLoop() {
	Update();
	Render();
}

void Game::Update() {

}

void Game::Render() {
	window_->clear();
	RenderActiveObjects();
	window_->display();
}

void Game::RenderActiveObjects() {
	std::list<IRenderable*>::iterator iterator;
	//This iteration doesn't have to be backwards as no object would be destroyed during the render cycle
	for (iterator = activeRenderers_.begin(); iterator != activeRenderers_.end(); iterator++) {
		(*iterator)->Render(window_);
	}
}