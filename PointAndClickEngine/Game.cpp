#include "Game.h"


Game::~Game() {
	std::list<Entity*>::iterator it;
	for (it = entities_.begin(); it != entities_.end(); it++) {
		delete(*it);
	}
}

Game::Game() : window_(NULL), resourceManager_(NULL) {
}


void Game::Init(sf::RenderWindow* window, ResourceManager* resourceManager) {
	window_ = window;
	resourceManager_ = resourceManager;

	//testing code
	EntityFactory entityFactory;

	//testing sprite
	sf::Sprite* testing_sprite = new sf::Sprite();
	TextureAsset* texture_asset = (TextureAsset*)resourceManager_->GetAssetOfID("spr_Door");
	testing_sprite->setTexture(*(texture_asset->texture_));

	Entity* testing_sprite_entity;
	testing_sprite_entity = entityFactory.CreateEntity(NULL);
	entities_.push_back(testing_sprite_entity);

	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sprite_renderer->sprite_ = testing_sprite;

	testing_sprite_entity->AddComponent((IComponent*)sprite_renderer);

	activeRenderers_.push_back((IRenderable*)(sprite_renderer));


	//testing audio
	sf::Sound* testing_sound = new sf::Sound();
	SoundBufferAsset* sound_buffer_asset = (SoundBufferAsset*)resourceManager_->GetAssetOfID("sfx_Door");
	testing_sound->setBuffer(*(sound_buffer_asset->sound_buffer_));

	Entity* testing_audio_entity_;
	testing_audio_entity_ = entityFactory.CreateEntity(NULL);
	entities_.push_back(testing_audio_entity_);

	audio_source = new AudioSource();
	audio_source->sound_ = testing_sound;
}

void Game::GameLoop() {
	Update();
	Render();
}

void Game::Update() {
	if (!audio_source->IsPlaying()) {
		audio_source->Play();
	}
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