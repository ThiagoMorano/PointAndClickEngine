#pragma once
#include <string>
#include "SFML/Graphics.hpp"

//Forward declarations
class AudioSource;
class Interactable;

class IResponse {
public:
	virtual ~IResponse() {}
	virtual void Init() = 0;
	virtual void Invoke() = 0;
	virtual void SetInteractable(Interactable*) = 0;
};


class AudioResponse : public virtual IResponse {
public:
	virtual ~AudioResponse();
	virtual void Init();
	virtual void Invoke();
	virtual void SetInteractable(Interactable*);

	AudioSource* audio_source_;

protected:
	Interactable* interactable_;
};

class LoadSceneResponse : public virtual IResponse {
public:
	virtual ~LoadSceneResponse();
	virtual void Init();
	virtual void Invoke();
	virtual void SetInteractable(Interactable*);

	std::string scene_id_;

protected:
	Interactable* interactable_;
};

class TextResponse : public virtual IResponse {
public:
	virtual ~TextResponse();
	virtual void Init();
	virtual void Invoke();
	virtual void SetInteractable(Interactable*);

	sf::Text* text_;

protected:
	Interactable* interactable_;

};