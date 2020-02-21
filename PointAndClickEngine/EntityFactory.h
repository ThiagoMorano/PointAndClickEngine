#pragma once
#include "Entity.h"
#include "Assets.h"
#include "rapidxml-1.13/rapidxml.hpp"

//
//class EntityFactory
//{
//public:
//	EntityFactory(ResourceManager*);
//
//	Entity* CreateEntity(EntityData*);
//	Entity* CreateEntity(rapidxml::xml_node<>* game_object_node);
//
//private:
//	ResourceManager* resource_manager_;
//
//	IComponent* InstantiateComponent(rapidxml::xml_node<>*);
//	ComponentType ParseComponentType(std::string);
//
//	SpriteRenderer* InstantiateSpriteRenderer(rapidxml::xml_node<>*);
//	AudioSource* InstantiateAudioSource(rapidxml::xml_node<>*);
//};