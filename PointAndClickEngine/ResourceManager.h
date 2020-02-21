#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include "rapidxml-1.13/rapidxml.hpp"

#include "AssetFactory.h"
#include "SceneFactory.h"
#include "EntityFactory.h"

class GameConfig {
public:
	std::string application_name_;
	int screen_width_;
	int screen_height_;
	int fps;
};

class ResourceManager {
public:
	ResourceManager(std::string);
	~ResourceManager();

	void LoadFileData(std::string);

	GameConfig* GetGameConfig();
	std::string GetResourcesPath();

	std::list<Asset*>* GetAssetList();
	Asset* GetAssetOfID(std::string);

	std::list<Scene*>* GetSceneList();


private:
	std::vector<char>* buffer_;
	rapidxml::xml_document<> xml_document_;

	std::string resources_path_;
	std::list<Asset*>* asset_list_;
	std::list<Scene*>* scene_list_;

	void LoadAssetList();
	void LoadSceneList();

	void LoadGameObjectsIntoScene(Scene*, rapidxml::xml_node<>*);

	void DeleteAssetList();
	void DeleteSceneList();
};


class EntityFactory
{
public:
	EntityFactory(ResourceManager*);

	Entity* CreateEntity(EntityData*);
	Entity* CreateEntity(rapidxml::xml_node<>* game_object_node);

private:
	ResourceManager* resource_manager_;

	IComponent* InstantiateComponent(rapidxml::xml_node<>*);
	ComponentType ParseComponentType(std::string);

	SpriteRenderer* InstantiateSpriteRenderer(rapidxml::xml_node<>*);
	AudioSource* InstantiateAudioSource(rapidxml::xml_node<>*);
};