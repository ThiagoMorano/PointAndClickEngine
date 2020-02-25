#include "Components.h"

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