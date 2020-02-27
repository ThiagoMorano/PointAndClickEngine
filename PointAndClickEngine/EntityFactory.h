#pragma once
#include "rapidxml-1.13/rapidxml.hpp"
#include "Entity.h"
#include "Responses.h"

class ResourceManager;


class EntityFactory
{
public:
	EntityFactory(ResourceManager*);

	Entity* CreateEntity(rapidxml::xml_node<>* game_object_node);

private:
	ResourceManager* resource_manager_;

	IComponent* InstantiateComponent(rapidxml::xml_node<>*);
	ComponentType ParseComponentType(std::string);

	void InitializeTransformable(Entity*, rapidxml::xml_node<>*);

	CharacterController* InstantiateCharacterController(rapidxml::xml_node<>*);
	SpriteRenderer* InstantiateSpriteRenderer(rapidxml::xml_node<>*);
	AudioSource* InstantiateAudioSource(rapidxml::xml_node<>*);
	Interactable* InstantiateInteractable(rapidxml::xml_node<>*);

	IResponse* InstantiateReponse(rapidxml::xml_node<>*);
	AudioResponse* InstantiateResponse_Audio(rapidxml::xml_node<>*);
	LoadSceneResponse* InstantiateResponse_LoadScene(rapidxml::xml_node<>*);
	TextResponse* InstantiateResponse_Text(rapidxml::xml_node<>*);
};