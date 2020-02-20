#include "ResourceManager.h"

rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* node, const char* node_tag) {
	for (rapidxml::xml_node<>* childNode = node->first_node(); childNode != NULL; childNode = childNode->next_sibling()) {
		if (strcmp(childNode->name(), node_tag) == 0) return childNode;
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

ResourceManager::~ResourceManager() {
	delete(buffer_);
	delete(asset_list_);
}

ResourceManager::ResourceManager(std::string game_file_name) {
	LoadFileData(game_file_name);
	LoadAssetList();
}

void ResourceManager::LoadFileData(std::string game_file_name) {
	std::ifstream xmlFile(game_file_name, std::ios::binary);
	buffer_ = new std::vector<char>((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer_->push_back('\0');
	xmlFile.close();

	xml_document_.parse<0>(&(*buffer_)[0]);
}

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

			AssetFactory asset_factory;
			AssetData* new_asset_data;
			Asset* new_asset;
			for (node_iterator = node_iterator->first_node(); node_iterator != NULL; node_iterator = node_iterator->next_sibling()) {

				new_asset_data = new AssetData();
				new_asset_data->type_ = GetAttributeValue(node_iterator, "type");
				new_asset_data->id_ = GetAttributeValue(node_iterator, "id");
				new_asset_data->path_ = resources_path_ + node_iterator->value();

				new_asset = asset_factory.CreateAsset(new_asset_data);
				asset_list_->push_back(new_asset);
			}
		}
	}
}

std::list<Asset*>* ResourceManager::GetAssetList() {
	if (asset_list_ == NULL) {
		LoadAssetList();
	}
	return asset_list_;
}

Asset* ResourceManager::GetAssetOfID(std::string id) {
	std::list<Asset*>::iterator iterator;
	for (iterator = asset_list_->begin(); iterator != asset_list_->end(); iterator++) {
		if ((*iterator)->id_.compare(id) == 0)
			return *iterator;
	}

	return NULL;
}

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

std::string ResourceManager::GetResourcesPath() {
	return resources_path_;
}



std::list<Scene*>* ResourceManager::GetSceneList() {
	if (scene_list_ == NULL) {
		LoadSceneList();
	}
	return scene_list_;
}

void ResourceManager::LoadSceneList() {
	std::list<Scene*>* scene_list = new std::list<Scene*>();

	rapidxml::xml_node<>* root_node = xml_document_.first_node();
	rapidxml::xml_node<>* node_iterator;
	rapidxml::xml_attribute<>* attribute_iterator;

	node_iterator = FindChildNode(root_node, "scenes");
	if (node_iterator != NULL) {
		node_iterator = FindChildNode(node_iterator, "scene");

		if (node_iterator != NULL) {

		}
	}
}