#pragma once
#include "rapidxml-1.13/rapidxml.hpp"
#include "Entity.h"
#include "Responses.h"


/// EntityFactory is a class of the factory pattern that handles the creation of entity objects
/// It does so by having some xml handling logic, so the factory is able to read the <gameObject> node and
/// instantiate the entity and populate it with the correct components, based on the <components> node
///
/// Thus the EntityFactory also handles the instantiation of components, doing so by having a different method
/// for each type of component.
///
/// If the component is an Interactable, it's the EntityFactory that handles the creation of that component's responses



// Forward declaration
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
	AnimatedSprite* InstantiateAnimatedSprite(rapidxml::xml_node<>*);
	AudioSource* InstantiateAudioSource(rapidxml::xml_node<>*);
	Interactable* InstantiateInteractable(rapidxml::xml_node<>*);

	IResponse* InstantiateReponse(rapidxml::xml_node<>*);
	AudioResponse* InstantiateResponse_Audio(rapidxml::xml_node<>*);
	LoadSceneResponse* InstantiateResponse_LoadScene(rapidxml::xml_node<>*);
	TextResponse* InstantiateResponse_Text(rapidxml::xml_node<>*);
};