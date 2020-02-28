#pragma once
#include <string>
#include "SFML/Graphics.hpp"

/// Responses are the feedback of interactions with Interactable components
/// Their main method is Invoke(), which implements the expected feedback of each type of response

//Forward declarations
class AudioSource;
class Interactable;


// For a class to be a response, it must implement the IResponse interface
class IResponse {
public:
	virtual ~IResponse() {}
	virtual void Init() = 0;
	virtual void Invoke() = 0;
	virtual void SetInteractable(Interactable*) = 0;
};


// A response that plays the audio of an audioSource component attached to the interactable entity
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


// This response loads a new scene (defined by scene_id_).
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


// Used to display a textual feedback on the user interface
class TextResponse : public virtual IResponse {
public:
	virtual ~TextResponse();
	virtual void Init();
	virtual void Invoke();
	virtual void SetInteractable(Interactable*);

	sf::Text* text_;
	float time_to_show_text_;

protected:
	Interactable* interactable_;
};