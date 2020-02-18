#include "ResourceManager.h"

rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* node, const char* nodeTag) {
	for (rapidxml::xml_node<>* childNode = node->first_node(); childNode != NULL; childNode = childNode->next_sibling()) {
		if (strcmp(childNode->name(), nodeTag) == 0) return childNode;
	}
	return NULL;
}

rapidxml::xml_attribute<>* FindAttribute(rapidxml::xml_node<>* node, const char* attributeName) {
	for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute != NULL; attribute = attribute->next_attribute()) {
		if (strcmp(attribute->name(), attributeName) == 0) return attribute;
	}
	return NULL;
}

char* GetAttributeValue(rapidxml::xml_node<>* node, const char* attributeName) {
	for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute != NULL; attribute = attribute->next_attribute()) {
		if (strcmp(attribute->name(), attributeName) == 0) return attribute->value();
	}
	return NULL;
}

ResourceManager::ResourceManager(std::string gameFileName) {
	LoadData(gameFileName);
}

ResourceManager::~ResourceManager() {
	delete(buffer_);
	delete(asset_list_);
}

void ResourceManager::LoadData(std::string gameFileName) {
	std::ifstream xmlFile(gameFileName, std::ios::binary);
	buffer_ = new std::vector<char>((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	buffer_->push_back('\0');
	xmlFile.close();

	xml_document_.parse<0>(&(*buffer_)[0]);
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

std::list<Asset*>* ResourceManager::GetAssetList() {
	LoadAssetList();
	return asset_list_;
}

void ResourceManager::LoadAssetList() {
	asset_list_ = new std::list<Asset*>();



	rapidxml::xml_node<>* rootNode = xml_document_.first_node();
	rapidxml::xml_node<>* nodePointer;
	rapidxml::xml_attribute<>* attributePointer;

	nodePointer = FindChildNode(rootNode, "resources");
	if (nodePointer != NULL) {

		attributePointer = FindAttribute(nodePointer, "path");
		if (attributePointer != NULL) {
			resources_path_ = attributePointer->value();

			AssetFactory assetFactory;
			AssetData* newAssetData;
			Asset* newAsset;
			for (nodePointer = nodePointer->first_node(); nodePointer != NULL; nodePointer = nodePointer->next_sibling()) {

				newAssetData = new AssetData();
				newAssetData->type_ = GetAttributeValue(nodePointer, "type");
				newAssetData->id_ = GetAttributeValue(nodePointer, "id");
				newAssetData->path_ = nodePointer->value();

				newAsset = assetFactory.CreateAsset(newAssetData);
				asset_list_->push_back(newAsset);
			}
		}
	}
}