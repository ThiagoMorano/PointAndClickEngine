#include "Responses.h"
#include "Components.h"
#include "Game.h"


AudioResponse::~AudioResponse() {}

void AudioResponse::Init() {
	audio_source_ = dynamic_cast<AudioSource*>(interactable_->GetComponent(ComponentType::kAudioSource));
}

void AudioResponse::SetInteractable(Interactable* interactable) {
	interactable_ = interactable;
}

void AudioResponse::Invoke() {
	audio_source_->Play();
}




LoadSceneResponse::~LoadSceneResponse() {}
void LoadSceneResponse::Init() {}

void LoadSceneResponse::SetInteractable(Interactable* interactable) {
	interactable_ = interactable;
}

void LoadSceneResponse::Invoke() {
	Game::Instance()->LoadSceneOfID(scene_id_);
}




TextResponse::~TextResponse() {
	delete(text_);
}

void TextResponse::Init() {}

void TextResponse::SetInteractable(Interactable* interactable) {
	interactable_ = interactable;
}

void TextResponse::Invoke() {
	Game::Instance()->ActivateText(text_, time_to_show_text_);
}