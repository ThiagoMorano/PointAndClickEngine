#include "Components.h"
#include "Game.h"


#pragma region CharacterController
CharacterController::~CharacterController() {

}

ComponentType CharacterController::GetComponentType() {
	return ComponentType::kCharacterController;
}

void CharacterController::Update(sf::Transformable* transformable) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		should_move_ = true;
		CalculateDirection(transformable);
	}

	if (should_move_) {
		Move(transformable);

		if (ArrivedAtDestination(transformable)) {
			should_move_ = false;
		}
	}
}

void CharacterController::CalculateDirection(sf::Transformable* transformable) {
	destination_.x = sf::Mouse::getPosition().x;
	destination_.y = sf::Mouse::getPosition().y;

	direction_ = destination_ - transformable->getPosition();
	float direction_length = sqrtf((direction_.x * direction_.x + direction_.y * direction_.y));
	direction_ = direction_ / direction_length;

}

void CharacterController::Move(sf::Transformable* transformable) {
	transformable->move(speed * direction_);
}

bool CharacterController::ArrivedAtDestination(sf::Transformable* transformable) {
	sf::Vector2f distance_vector = destination_ - transformable->getPosition();
	float distance = sqrtf(distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y);

	if (abs(distance) < 5) {
		return true;
	}
	return false;
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

void SpriteRenderer::Update(sf::Transformable* transformable) {
	sprite_->setPosition(transformable->getPosition());
	sprite_->setRotation(transformable->getRotation());
	sprite_->setScale(transformable->getScale());
}
#pragma endregion


#pragma region AudioSource
AudioSource::~AudioSource() {
	delete(sound_);
}

ComponentType AudioSource::GetComponentType() {
	return ComponentType::kAudioSource;
}

void AudioSource::Play() {
	sound_->play();
}

bool AudioSource::IsPlaying() {
	return (sound_->getStatus() == sf::SoundSource::Status::Playing);
}

void AudioSource::Update(sf::Transformable* transformable) {
	if (!this->IsPlaying()) {
		this->Play();
	}
}

#pragma endregion