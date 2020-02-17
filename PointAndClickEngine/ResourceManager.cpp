#include "ResourceManager.h"


rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* node, const char* nodeTag)
{
	for (rapidxml::xml_node<>* childNode = node->first_node(); childNode != NULL; childNode = childNode->next_sibling()) {
		if (strcmp(childNode->name(), nodeTag) == 0) return childNode;
	}
	return NULL;
}

rapidxml::xml_attribute<>* FindAttribute(rapidxml::xml_node<>* node, const char* attributeName)
{
	for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute != NULL; attribute = attribute->next_attribute())
	{
		if (strcmp(attribute->name(), attributeName) == 0) return attribute;
	}
	return NULL;
}

char* GetAttributeValue(rapidxml::xml_node<>* node, const char* attributeName)
{
	for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute != NULL; attribute = attribute->next_attribute())
	{
		if (strcmp(attribute->name(), attributeName) == 0) return attribute->value();
	}
	return NULL;
}

ResourceManager::ResourceManager(std::string gameFileName) {
	LoadData(gameFileName);
}

void ResourceManager::LoadData(std::string gameFileName) {
	std::ifstream xmlFile(gameFileName, std::ios::binary);
	_buffer = new std::vector<char>((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());
	_buffer->push_back('\0');
	xmlFile.close();

	_xmlDocument.parse<0>(&(*_buffer)[0]);
}

GameConfig* ResourceManager::GetGameConfig() {
	GameConfig* gameConfig = new GameConfig();

	rapidxml::xml_node<>* rootNode = _xmlDocument.first_node();
	rapidxml::xml_node<>* nodePointer;
	rapidxml::xml_attribute<>* attributePointer;

	nodePointer = FindChildNode(rootNode, "title");
	if (nodePointer != NULL)
		gameConfig->applicationName = nodePointer->value();

	nodePointer = FindChildNode(rootNode, "window");
	if (nodePointer != NULL) {
		attributePointer = FindAttribute(nodePointer, "width");
		if (attributePointer != NULL)
			gameConfig->screenWidth = atoi(attributePointer->value());

		attributePointer = FindAttribute(nodePointer, "height");
		if (attributePointer != NULL)
			gameConfig->screenHeight = atoi(attributePointer->value());

		attributePointer = FindAttribute(nodePointer, "fps");
		if (attributePointer != NULL)
			gameConfig->fps = atoi(attributePointer->value());
	}

	return gameConfig;
}