#include "Components.h"
#include "Game.h"
#include "Responses.h"


#pragma region SpriteRenderer
SpriteRenderer::~SpriteRenderer() {
	delete(sprite_);
}

// Initialize sprite_ with the same values as the entity_'s transformable.
void SpriteRenderer::Init() {
	sprite_->setPosition((entity_->transformable_).getPosition());
	sprite_->setRotation((entity_->transformable_).getRotation());
	sprite_->setScale((entity_->transformable_).getScale());
}

void SpriteRenderer::Render(sf::RenderWindow* window) {
	window->draw(*sprite_);
}

int SpriteRenderer::GetRenderLayer() {
	return render_layer_;
}

bool SpriteRenderer::IsOfType(ComponentType component_type) {
	if (component_type == ComponentType::kSpriteRenderer)
		return true;
	else
		return false;
}

IComponent* SpriteRenderer::GetComponent(ComponentType component_type) {
	return entity_->GetComponent(component_type);
}

void SpriteRenderer::SetEntity(Entity* entity) {
	entity_ = entity;
}

// The sprite_ follows entity_'s transformable
void SpriteRenderer::Update(sf::Transformable* transformable) {
	sprite_->setPosition((entity_->transformable_).getPosition());
	sprite_->setRotation((entity_->transformable_).getRotation());
	sprite_->setScale((entity_->transformable_).getScale());
}

// Instantiates a new sf::Sprite with the passed texture and sets its origin to the center.
void SpriteRenderer::InitSprite(sf::Texture* texture) {
	sprite_ = new sf::Sprite(*texture);
	sprite_->setOrigin(sprite_->getGlobalBounds().width / 2, sprite_->getGlobalBounds().height / 2);
}

sf::Sprite* SpriteRenderer::GetSprite() {
	return sprite_;
}

// Uses sf::Rect functions to verify if the position defined in vector is contained in sprite_
bool SpriteRenderer::CheckOverlap(sf::Vector2i vector) {
	sf::Vector2f vectorf(vector);
	bool was_contained = sprite_->getGlobalBounds().contains(vectorf.x, vectorf.y);
	return was_contained;
}

// Uses sf::Rect functions to verify if the renderer intersecs our sprite_
bool SpriteRenderer::CheckOverlap(SpriteRenderer* renderer) {
	bool intersected = sprite_->getGlobalBounds().intersects(renderer->GetSprite()->getGlobalBounds());
	return intersected;
}
#pragma endregion



#pragma region AnimatedSprite
AnimatedSprite::~AnimatedSprite() {
	std::vector<sf::Sprite*>::iterator it;
	for (it = sprites_.begin(); it != sprites_.end(); it++) {
		delete(*it);
	}
}

// Initializes each sprite of this animation
void AnimatedSprite::Init() {
	std::vector<sf::Sprite*>::iterator it;
	for (it = sprites_.begin(); it != sprites_.end(); it++) {
		(*it)->setOrigin((*it)->getGlobalBounds().width / 2, (*it)->getGlobalBounds().height / 2);
		(*it)->setPosition((entity_->transformable_).getPosition());
		(*it)->setRotation((entity_->transformable_).getRotation());
		(*it)->setScale((entity_->transformable_).getScale());
	}
	

	time_per_keyframe_ = duration_ / number_of_keyframes_;
	current_sprite_ = 0;
}

// Accounts for the passage of time, and continues in the animation accordingly
void AnimatedSprite::Update(sf::Transformable*) {
	elapsed_time_ += Time::Instance()->DeltaTime();
	if (elapsed_time_ >= time_per_keyframe_) {
		NextKeyframe();
		elapsed_time_ = 0.0f;
	}

	// The current sprite's transformable should have the same values as the Entity's
	sprites_[current_sprite_]->setPosition((entity_->transformable_).getPosition());
	sprites_[current_sprite_]->setRotation((entity_->transformable_).getRotation());
	sprites_[current_sprite_]->setScale((entity_->transformable_).getScale());
}

// Iterates through the keyframes
void AnimatedSprite::NextKeyframe() {
	current_sprite_++;
	if (current_sprite_ > number_of_keyframes_ - 1) {
		current_sprite_ = 0;
	}
}

void AnimatedSprite::Render(sf::RenderWindow* window) {
	window->draw(*sprites_[current_sprite_]);
}

int AnimatedSprite::GetRenderLayer() {
	return render_layer_;
}

// An AnimatedSprite is a SpriteRenderer as well, so it should return true for both cases.
bool AnimatedSprite::IsOfType(ComponentType component_type) {
	if (component_type == ComponentType::kSpriteRenderer || component_type == ComponentType::kAnimatedSprite)
		return true;
	else
		return false;
}

IComponent* AnimatedSprite::GetComponent(ComponentType component_type) {
	return entity_->GetComponent(component_type);
}

// Loops through the sprite sheet, assigning each subtexture to the sprite of that keyframe
void AnimatedSprite::InitSprite(sf::Texture* texture) {
	sf::Vector2i texture_size = sf::Vector2i(texture->getSize());

	for (int j = 0; j < texture_size.y / keyframe_height_; j++) {
		for (int i = 0; i < texture_size.x / keyframe_width_; i++) {
			// Stops the iteration if all keyframes have already been assigned.
			// Used in case the sprite sheet doesn't have all rows completely full (not symmetric).
			if (sprites_.size() >= number_of_keyframes_) {
				return;
			}
			sf::Sprite* new_sprite = new sf::Sprite(*texture);
			new_sprite->setTextureRect(sf::IntRect(i * keyframe_width_, j * keyframe_height_, keyframe_width_, keyframe_height_));
			sprites_.push_back(new_sprite);
		}
	}
}

// Returns the current sprite
sf::Sprite* AnimatedSprite::GetSprite() {
	return sprites_[current_sprite_];
}

// Check for overlap between the position in vector and the current sprite
bool AnimatedSprite::CheckOverlap(sf::Vector2i vector) {
	sf::Vector2f vectorf(vector);
	bool was_contained = sprites_[current_sprite_]->getGlobalBounds().contains(vectorf.x, vectorf.y);
	return was_contained;
}

// Check for overlap between the passed renderer and the current sprite
bool AnimatedSprite::CheckOverlap(SpriteRenderer* renderer) {
	bool intersected = sprites_[current_sprite_]->getGlobalBounds().intersects(renderer->GetSprite()->getGlobalBounds());
	return intersected;
}

void AnimatedSprite::SetEntity(Entity* entity) {
	entity_ = entity;
}

#pragma endregion



#pragma region CharacterController
CharacterController::~CharacterController() {}

// Initializes the reference to the sprite renderer / animated sprite
void CharacterController::Init() {
	sprite_renderer_ = dynamic_cast<SpriteRenderer*>(GetComponent(ComponentType::kSpriteRenderer));
}

bool CharacterController::IsOfType(ComponentType component_type) {
	if (component_type == ComponentType::kCharacterController)
		return true;
	else
		return false;
}

IComponent* CharacterController::GetComponent(ComponentType component_type) {
	return entity_->GetComponent(component_type);
}

void CharacterController::SetEntity(Entity* entity) {
	entity_ = entity;
}

void CharacterController::Update(sf::Transformable* transformable) {
	// Watches for mouse left click input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		should_move_ = true;
		CalculateDirection(transformable);
	}

	// If there was a click, moves until it arrives at the destination
	if (should_move_) {
		if (ArrivedAtDestination(transformable)) {
			should_move_ = false;
		}
		else {
			Move(transformable);
		}
	}
}

// Calculates new direction based on entity's positions and the position of the click
void CharacterController::CalculateDirection(sf::Transformable* transformable) {
	destination_.x = static_cast<float>(sf::Mouse::getPosition(*Game::Instance()->window_).x);
	destination_.y = static_cast<float>(sf::Mouse::getPosition(*Game::Instance()->window_).y);

	direction_ = destination_ - transformable->getPosition();
	float direction_length = sqrtf((direction_.x * direction_.x + direction_.y * direction_.y));
	direction_ = direction_ / direction_length;
}

void CharacterController::Move(sf::Transformable* transformable) {
	transformable->move(speed_ * direction_ * Time::Instance()->DeltaTime());
}

bool CharacterController::ArrivedAtDestination(sf::Transformable* transformable) {
	sf::Vector2f distance_vector = destination_ - transformable->getPosition();
	float distance = sqrtf(distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y);

	// Gives a small buffer to consider what is "arrived" so it doesn't flick around the destination
	if (abs(distance) < speed_ * Time::Instance()->DeltaTime()) {
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

bool AudioSource::IsOfType(ComponentType component_type) {
	if (component_type == ComponentType::kAudioSource)
		return true;
	else
		return false;
}

IComponent* AudioSource::GetComponent(ComponentType component_type) {
	return entity_->GetComponent(component_type);
}

void AudioSource::SetEntity(Entity* entity) {
	entity_ = entity;
}

// Play sound if it's not yet being played
void AudioSource::Play() {
	if (!this->IsPlaying()) {
		sound_->play();
	}
}

// Wraps sf::SoundSource::Status to check if the sound is being played
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

// Initializes the sprite renderer and responses
void Interactable::Init() {
	sprite_renderer_ = dynamic_cast<SpriteRenderer*>(entity_->GetComponent(ComponentType::kSpriteRenderer));

	std::list<IResponse*>::iterator it;
	for (it = responses_.begin(); it != responses_.end(); it++) {
		(*it)->Init();
	}
}

bool Interactable::IsOfType(ComponentType component_type) {
	if (component_type == ComponentType::kInteractable)
		return true;
	else
		return false;
}

IComponent* Interactable::GetComponent(ComponentType component_type) {
	return entity_->GetComponent(component_type);
}

void Interactable::SetEntity(Entity* entity) {
	entity_ = entity;
}

void Interactable::Update(sf::Transformable* transformable) {
	// Watches for mouse left click input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mouse_position = sf::Mouse::getPosition(*Game::Instance()->window_);
		if (sprite_renderer_->CheckOverlap(mouse_position)) { // Check whether the click happened within this->spriete_renderer_
			was_clicked_on_ = true;
		}
		else {
			was_clicked_on_ = false;
		}
	}

	// If the click happened on this object, start checking for overlap with character controllers
	if (was_clicked_on_) {
		if (CheckOverlapWithCharacterControllers()) {
			Interact();
			was_clicked_on_ = false;
		}
	}
}

// Check for overlaps with character controllers in the current scene
bool Interactable::CheckOverlapWithCharacterControllers() {
	if (sprite_renderer_ != NULL) {
		return Game::Instance()->CheckOverlapWithCharacterController(sprite_renderer_);
	}

	return false;
}

// Interacting with this object invokes all responses for it.
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
