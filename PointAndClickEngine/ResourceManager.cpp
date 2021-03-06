#include "ResourceManager.h"
#include "AssetFactory.h"
#include "EntityFactory.h"


#pragma region Utils 
/// Utility functions to better handle rapidxml API

rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* node, const char* node_tag) {
	for (rapidxml::xml_node<>* child_node = node->first_node(); child_node != NULL; child_node = child_node->next_sibling()) {
		if (strcmp(child_node->name(), node_tag) == 0) return child_node;
	}
	return NULL;
}

rapidxml::xml_attribute<>* FindAttribute(rapidxml::xml_node<>* node, const char* attribute_name) {
	for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute != NULL; attribute = attribute->next_attribute()) {
		if (strcmp(attribute->name(), attribute_name) == 0) return attribute;
	}
	return NULL;
}

char* GetAttributeValue(rapidxml::xml_node<>* node, const char* attribute_name) {
	for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute != NULL; attribute = attribute->next_attribute()) {
		if (strcmp(attribute->name(), attribute_name) == 0) return attribute->value();
	}
	return NULL;
}
#pragma endregion



#pragma region ResourceManager
ResourceManager::~ResourceManager() {
	delete(buffer_);
	delete(asset_factory_);
	delete(entity_factory_);

	DeleteAssetList();
	DeleteSceneList();
}

// Iterates through asset list destroying its content
void ResourceManager::DeleteAssetList() {
	std::list<Asset*>::iterator it_assets;
	for (it_assets = asset_list_->begin(); it_assets != asset_list_->end(); it_assets++) {
		delete((*it_assets));
	}
	delete(asset_list_);
}

// Iterates through scene list destroying its content
void ResourceManager::DeleteSceneList() {
	std::list<Scene*>::iterator it_scene;
	for (it_scene = scene_list_->begin(); it_scene != scene_list_->end(); it_scene++) {
		delete((*it_scene));
	}
	delete(scene_list_);
}


// Loads xml tree and AssetList on instantiation
ResourceManager::ResourceManager(std::string game_file_name) {
	asset_factory_ = new AssetFactory(this);
	entity_factory_ = new EntityFactory(this);
	
	LoadFileData(game_file_name);
	LoadAssetList();
}

// Parse the xml file of given name
void ResourceManager::LoadFileData(std::string game_file_name) {
	std::ifstream xmlFile(game_file_name, std::ios::binary);
	buffer_ = new std::vector<char>((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer_->push_back('\0');
	xmlFile.close();

	xml_document_.parse<0>(&(*buffer_)[0]);
}

// Loads asset list according to the xml tree
void ResourceManager::LoadAssetList() {
	asset_list_ = new std::list<Asset*>();

	rapidxml::xml_node<>* root_node = xml_document_.first_node();
	rapidxml::xml_node<>* node_iterator;
	rapidxml::xml_attribute<>* attribute_iterator;

	node_iterator = FindChildNode(root_node, "resources");
	if (node_iterator != NULL) {

		attribute_iterator = FindAttribute(node_iterator, "path");
		if (attribute_iterator != NULL) {
			resources_path_ = attribute_iterator->value();

			// Traverse until <resources> node, and start loading assets
			Asset* new_asset;
			for (node_iterator = FindChildNode(node_iterator, "asset"); node_iterator != NULL; node_iterator = node_iterator->next_sibling()) {
				new_asset = asset_factory_->CreateAsset(node_iterator);
				asset_list_->push_back(new_asset);
			}
		}
	}
}


// Called by the Game class once the game should initialize
void ResourceManager::Init() {
	LoadSceneList();
}

// Load each scene described in the xml file
void ResourceManager::LoadSceneList() {
	scene_list_ = new std::list<Scene*>();

	rapidxml::xml_node<>* root_node = xml_document_.first_node();
	rapidxml::xml_node<>* node_iterator;
	rapidxml::xml_attribute<>* attribute_iterator;


	node_iterator = FindChildNode(root_node, "scenes");
	if (node_iterator != NULL) {

		Scene* instantiated_scene = NULL;
		rapidxml::xml_node<>* game_object_node;

		//Iterate through <scene> nodes
		for (node_iterator = FindChildNode(node_iterator, "scene"); node_iterator != NULL; node_iterator = node_iterator->next_sibling()) {
			instantiated_scene = new Scene();
			instantiated_scene->id_ = FindAttribute(node_iterator, "id")->value();

			game_object_node = FindChildNode(node_iterator, "gameObject");
			if (game_object_node != NULL) {
				LoadGameObjectsIntoScene(instantiated_scene, game_object_node);
			}
			scene_list_->push_back(instantiated_scene);
		}
	}
}

// Load all objects of a given scene into it
void ResourceManager::LoadGameObjectsIntoScene(Scene* scene, rapidxml::xml_node<>* game_object_node) {
	Entity* entity_pointer;

	//Iterate through <gameObject> nodes
	for (rapidxml::xml_node<>* node_iterator = game_object_node; node_iterator != NULL; node_iterator = node_iterator->next_sibling()) {
		entity_pointer = entity_factory_->CreateEntity(node_iterator);
		entity_pointer->Init();
		scene->AddEntity(entity_pointer);
	}
}


// Returns the asset list, generating it in case it didn't exist
std::list<Asset*>* ResourceManager::GetAssetList() {
	if (asset_list_ == NULL) {
		LoadAssetList();
	}
	return asset_list_;
}


// Retrieves an asset of a given ID
Asset* ResourceManager::GetAssetOfID(std::string id) {
	std::list<Asset*>::iterator iterator;
	for (iterator = asset_list_->begin(); iterator != asset_list_->end(); iterator++) {
		if ((*iterator)->id_.compare(id) == 0)
			return *iterator;
	}

	return NULL;
}


// Returns the scene list, generating it in case it didn't exist
std::list<Scene*>* ResourceManager::GetSceneList() {
	if (scene_list_ == NULL) {
		LoadSceneList();
	}
	return scene_list_;
}


// Retrieves the resources path
std::string ResourceManager::GetResourcesPath() {
	return resources_path_;
}


// Loads and returns a GameConfig object
GameConfig* ResourceManager::GetGameConfig() {
	GameConfig* gameConfig = new GameConfig();

	rapidxml::xml_node<>* rootNode = xml_document_.first_node();
	rapidxml::xml_node<>* nodePointer;
	rapidxml::xml_attribute<>* attributePointer;

	nodePointer = FindChildNode(rootNode, "title");
	if (nodePointer != NULL)
		gameConfig->application_name_ = nodePointer->value();

	nodePointer = FindChildNode(rootNode, "window");
	if (nodePointer != NULL) {
		attributePointer = FindAttribute(nodePointer, "width");
		if (attributePointer != NULL)
			gameConfig->screen_width_ = atoi(attributePointer->value());

		attributePointer = FindAttribute(nodePointer, "height");
		if (attributePointer != NULL)
			gameConfig->screen_height_ = atoi(attributePointer->value());

		attributePointer = FindAttribute(nodePointer, "fps");
		if (attributePointer != NULL)
			gameConfig->fps = atoi(attributePointer->value());
	}

	return gameConfig;
}
#pragma endregion