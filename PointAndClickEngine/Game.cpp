#include "Game.h"


Game::~Game() {
	std::list<Scene*>::iterator it;
	for (it = scenes_->begin(); it != scenes_->end(); it++) {
		delete(*it);
	}

	//delete(audio_source);
}

Game::Game() : window_(NULL), resource_manager_(NULL), scenes_(NULL), current_scene_(NULL) {
}


void Game::Init(sf::RenderWindow* window, ResourceManager* resource_manager) {
	window_ = window;
	resource_manager_ = resource_manager;

	scenes_ = resource_manager_->GetSceneList();
	current_scene_ = scenes_->front();

	//testing code
	//EntityFactory entityFactory(resource_manager_);

	//testing sprite
	//sf::Sprite* testing_sprite = new sf::Sprite();
	//TextureAsset* texture_asset = (TextureAsset*)resource_manager_->GetAssetOfID("spr_Door");
	//testing_sprite->setTexture(*(texture_asset->texture_));

	//Entity* testing_sprite_entity;
	//EntityData data;
	//testing_sprite_entity = entityFactory.CreateEntity(&data);
	//entities_.push_back(testing_sprite_entity);

	//SpriteRenderer* sprite_renderer = new SpriteRenderer();
	//sprite_renderer->sprite_ = testing_sprite;

	//testing_sprite_entity->AddComponent((IComponent*)sprite_renderer);

	//active_renderers_.push_back((IRenderable*)(sprite_renderer));


	//testing audio
	//sf::Sound* testing_sound = new sf::Sound();
	//SoundBufferAsset* sound_buffer_asset = (SoundBufferAsset*)resource_manager_->GetAssetOfID("sfx_Door");
	//testing_sound->setBuffer(*(sound_buffer_asset->sound_buffer_));

	//Entity* testing_audio_entity_;
	//testing_audio_entity_ = entityFactory.CreateEntity(&data);
	//entities_.push_back(testing_audio_entity_);

	//audio_source = new AudioSource();
	//audio_source->sound_ = testing_sound;
}

void Game::GameLoop() {
	Update();
	Render();
}

void Game::Update() {
	current_scene_->Update();

	//if (!audio_source->IsPlaying()) {
	//	audio_source->Play();
	//}
}

void Game::Render() {
	window_->clear();
	current_scene_->Render(window_);
	//RenderActiveObjects();
	window_->display();
}

void Game::RenderActiveObjects() {
	std::list<IRenderable*>::iterator iterator;
	//This iteration doesn't have to be backwards as no object would be destroyed during the render cycle
	//for (iterator = active_renderers_.begin(); iterator != active_renderers_.end(); iterator++) {
	//	(*iterator)->Render(window_);
	//}
}