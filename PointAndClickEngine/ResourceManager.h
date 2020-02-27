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
#include "Responses.h"
#include "Scene.h"

// Forward declarations
class AssetFactory;
class EntityFactory;


class GameConfig {
public:
	std::string application_name_;
	int screen_width_;
	int screen_height_;
	int fps;
};


class ResourceManager {
public:
	~ResourceManager();
	ResourceManager(std::string);
	
	void Init();

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

	EntityFactory* entity_factory_;
	AssetFactory* asset_factory_;

	void LoadAssetList();
	void LoadSceneList();

	void LoadGameObjectsIntoScene(Scene*, rapidxml::xml_node<>*);

	void DeleteAssetList();
	void DeleteSceneList();
};