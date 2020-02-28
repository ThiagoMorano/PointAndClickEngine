#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "rapidxml-1.13/rapidxml.hpp"

#include "Assets.h"
#include "Entity.h"
#include "Responses.h"
#include "Scene.h"


/// The ResourceManager is the interfacing class between .xml and our game.
/// It loads the game from the .xml file and returning the objects as they will be already
/// used for the application, so no xml handling has to be done outside of here.
///
/// As it's instantiated, it loads and parses the .xml and generates the Asset list with the help of an AssetFactory.
/// As the Game class is initialized, the ResouceManager loads the game scenes and their objects by calling the EntityFactory.
///
/// It's when the ResourceManager is destroyed that all assets and game objects are destroyed, as it deletes asset and scene lists.
/// ResourceManager is also responsible for retrieving the GameConfig values.



// Forward declarations
class AssetFactory;
class EntityFactory;


// Data container for set up of the game window
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

	std::list<Asset*>* GetAssetList();
	Asset* GetAssetOfID(std::string);

	std::list<Scene*>* GetSceneList();

	GameConfig* GetGameConfig();
	std::string GetResourcesPath();


private:
	std::vector<char>* buffer_;
	rapidxml::xml_document<> xml_document_;

	EntityFactory* entity_factory_;
	AssetFactory* asset_factory_;

	std::list<Asset*>* asset_list_;
	std::list<Scene*>* scene_list_;
	std::string resources_path_;
	

	void LoadAssetList();
	void LoadSceneList();

	void LoadGameObjectsIntoScene(Scene*, rapidxml::xml_node<>*);

	void DeleteAssetList();
	void DeleteSceneList();
};