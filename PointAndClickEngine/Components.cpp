#include "Components.h"
#include "Game.h"
#include "Responses.h"

#pragma region SpriteRenderer
SpriteRenderer::~SpriteRenderer() {
	delete(sprite_);
}

void SpriteRenderer::Init() {}

void SpriteRenderer::Render(sf::RenderWindow* window) {
	window->draw(*sprite_);
}

int SpriteRenderer::GetRenderLayer() {
	return render_layer_;
}

ComponentType SpriteRenderer::GetComponentType() {
	return ComponentType::kSpriteRenderer;
}

IComponent* SpriteRenderer::GetComponent(ComponentType component_type) {
	return entity_->GetComponent(component_type);
}

void SpriteRenderer::SetEntity(Entity* entity) {
	entity_ = entity;
}

void SpriteRenderer::Update(sf::Transformable* transformable) {
	sprite_->setPosition(transformable->getPosition());
	sprite_->setRotation(transformable->getRotation());
	sprite_->setScale(transformable->getScale());
}

void SpriteRenderer::SetSprite(sf::Sprite* sprite) {
	sprite_ = sprite;
	sprite_->setOrigin(sprite_->getGlobalBounds().width / 2, sprite_->getGlobalBounds().height / 2);
}

bool SpriteRenderer::CheckOverlap(sf::Vector2i vector) {
	sf::Vector2f vectorf(vector);
	bool was_contained = sprite_->getGlobalBounds().contains(vectorf.x, vectorf.y);
	return was_contained;
}

bool SpriteRenderer::CheckOverlap(SpriteRenderer* renderer) {
	bool intersected = sprite_->getGlobalBounds().intersects(renderer->sprite_->getGlobalBounds());
	return intersected;
}
#pragma endregion



#pragma region CharacterController
CharacterController::~CharacterController() {

}

void CharacterController::Init() {
	sprite_renderer_ = dynamic_cast<SpriteRenderer*>(GetComponent(ComponentType::kSpriteRenderer));
}

ComponentType CharacterController::GetComponentType() {
	return ComponentType::kCharacterController;
}

IComponent* CharacterController::GetComponent(ComponentType component_type) {
	return entity_->GetComponent(component_type);
}

void CharacterController::SetEntity(Entity* entity) {
	entity_ = entity;
}


void CharacterController::Update(sf::Transformable* transformable) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		should_move_ = true;
		CalculateDirection(transformable);
	}

	if (should_move_) {
		if (ArrivedAtDestination(transformable)) {
			should_move_ = false;
		}
		else {
			Move(transformable);
		}
	}
}

void CharacterController::CalculateDirection(sf::Transformable* transformable) {
	destination_.x = static_cast<float>(sf::Mouse::getPosition(*Game::instance()->window_).x);
	destination_.y = static_cast<float>(sf::Mouse::getPosition(*Game::instance()->window_).y);

	direction_ = destination_ - transformable->getPosition();
	float direction_length = sqrtf((direction_.x * direction_.x + direction_.y * direction_.y));
	direction_ = direction_ / direction_length;

}

void CharacterController::Move(sf::Transformable* transformable) {
	transformable->move(speed_ * direction_);
}

bool CharacterController::ArrivedAtDestination(sf::Transformable* transformable) {
	sf::Vector2f distance_vector = destination_ - transformable->getPosition();
	float distance = sqrtf(distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y);

	if (abs(distance) < speed_) {
		transformable->setPosition(destination_);
		return true;
	}
	return false;
}

bool CharacterController::CheckOverlap(SpriteRenderer* sprite_renderer) {
	if (sprite_renderer_ != NULL) {
		return sprite_renderer_->CheckOverlap(sprite_renderer);
	}

	return false;
}

void CharacterController::StopMovement() {
	should_move_ = false;
}
#pragma endregion



#pragma region AudioSource
AudioSource::~AudioSource() {
	delete(sound_);
}

void AudioSource::Init() {}

ComponentType AudioSource::GetComponentType() {
	return ComponentType::kAudioSource;
}

IComponent* AudioSource::GetComponent(ComponentType component_type) {
	return entity_->GetComponent(component_type);
}

void AudioSource::SetEntity(Entity* entity) {
	entity_ = entity;
}

void AudioSource::Play() {
	if (!this->IsPlaying()) {
		sound_->play();
	}
}

bool AudioSource::IsPlaying() {
	return (sound_->getStatus() == sf::SoundSource::Status::Playing);
}

void AudioSource::Update(sf::Transformable* transformable) {}

void AudioSource::Stop() {
	if (this->IsPlaying()) {
		sound_->stop();
	}
}
#pragma endregion



#pragma region Interactable
Interactable::~Interactable() {}

void Interactable::Init() {
	sprite_renderer_ = dynamic_cast<SpriteRenderer*>(entity_->GetComponent(ComponentType::kSpriteRenderer));

	std::list<IResponse*>::iterator it;
	for (it = responses_.begin(); it != responses_.end(); it++) {
		(*it)->Init();
	}
}

ComponentType Interactable::GetComponentType() {
	return ComponentType::kInteractable;
}

IComponent* Interactable::GetComponent(ComponentType component_type) {
	return entity_->GetComponent(component_type);
}

void Interactable::SetEntity(Entity* entity) {
	entity_ = entity;
}

void Interactable::Update(sf::Transformable* transformable) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mouse_position = sf::Mouse::getPosition(*Game::instance()->window_);
		if (sprite_renderer_->CheckOverlap(mouse_position)) {
			was_clicked_on_ = true;
		}
		else {
			was_clicked_on_ = false;
		}
	}

	if (was_clicked_on_) {
		if (CheckOverlapWithCharacterControllers()) {
			Interact();
			was_clicked_on_ = false;
		}
	}
}

bool Interactable::CheckOverlapWithCharacterControllers() {
	if (sprite_renderer_ != NULL) {
		return Game::instance()->CheckOverlapWithCharacterController(sprite_renderer_);
	}

	return false;
}

void Interactable::Interact() {
	std::list<IResponse*>::iterator it;
	for (it = responses_.begin(); it != responses_.end(); it++) {
		(*it)->Invoke();
	}
}

void Interactable::AddResponse(IResponse* response) {
	response->SetInteractable(this);
	responses_.push_back(response);
}

bool Interactable::WasClickedOn() {
	return true;
}

#pragma endregion
