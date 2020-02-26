#include "Components.h"
#include "Game.h"


#pragma region CharacterController
CharacterController::~CharacterController() {

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
	destination_.x = sf::Mouse::getPosition(*Game::instance()->window_).x;
	destination_.y = sf::Mouse::getPosition(*Game::instance()->window_).y;

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

bool CharacterController::CheckOverlapWithInteractable() {
	return true;
}
#pragma endregion


#pragma region SpriteRenderer
SpriteRenderer::~SpriteRenderer() {
	delete(sprite_);
}

void SpriteRenderer::Render(sf::RenderWindow* window) {
	window->draw(*sprite_);
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

bool SpriteRenderer::PositionWithinSprite(sf::Vector2i vector) {
	return true;
}
#pragma endregion


#pragma region AudioSource
AudioSource::~AudioSource() {
	delete(sound_);
}

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
		sf::Vector2i mouse_position = sf::Mouse::getPosition();
		if (sprite_renderer_->PositionWithinSprite(mouse_position)) {
			was_clicked_on_ = true;
		}
	}

	if (was_clicked_on_) {
		if (OverlappingCharacterController()) {
			Interact();
		}
	}
}

bool Interactable::OverlappingCharacterController() {

	return true;
}

void Interactable::Interact() {
}

bool Interactable::WasClickedOn() {
	return true;
}

#pragma endregion
