#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "rapidxml-1.13/rapidxml.hpp"

#include "Assets.h"
#include "Entity.h"
#include "Scene.h"

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

	Entity* CreateEntity(rapidxml::xml_node<>* game_object_node);

private:
	ResourceManager* resource_manager_;

	IComponent* InstantiateComponent(rapidxml::xml_node<>*);
	ComponentType ParseComponentType(std::string);

	void InitializeTransformable(Entity*, rapidxml::xml_node<>*);

	SpriteRenderer* InstantiateSpriteRenderer(rapidxml::xml_node<>*);
	AudioSource* InstantiateAudioSource(rapidxml::xml_node<>*);
};

class AssetFactory {
public:
	AssetFactory(ResourceManager* resource_manager);

	Asset* CreateAsset(rapidxml::xml_node<>*);

private:
	ResourceManager* resource_manager_;

	TextureAsset* InstantiateTextureAsset(rapidxml::xml_node<>*);
	SoundBufferAsset* InstantiateSoundBufferAsset(rapidxml::xml_node<>*);
};