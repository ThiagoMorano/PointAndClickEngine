#include "AssetFactory.h"
#include "ResourceManager.h"

// Forward declarations of utility functions
rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* node, const char* node_tag);
rapidxml::xml_attribute<>* FindAttribute(rapidxml::xml_node<>* node, const char* attribute_name);
char* GetAttributeValue(rapidxml::xml_node<>* node, const char* attribute_name);

AssetFactory::AssetFactory(ResourceManager* resource_manager) : resource_manager_(resource_manager) {}

Asset* AssetFactory::CreateAsset(rapidxml::xml_node<>* asset_node) {
	std::string type = GetAttributeValue(asset_node, "type");

	Asset* asset = NULL;
	if (type.compare("image") == 0) {
		asset = InstantiateTextureAsset(asset_node);
	}
	else if (type.compare("sound") == 0) {
		asset = InstantiateSoundBufferAsset(asset_node);
	}
	else if (type.compare("font") == 0) {
		asset = InstantiateFontAsset(asset_node);
	}

	asset->id_ = GetAttributeValue(asset_node, "id");

	return asset;

}

TextureAsset* AssetFactory::InstantiateTextureAsset(rapidxml::xml_node<>* asset_node) {
	sf::Texture* new_texture = new sf::Texture();
	new_texture->loadFromFile(resource_manager_->GetResourcesPath() + asset_node->value());
	return new TextureAsset(new_texture);
}

SoundBufferAsset* AssetFactory::InstantiateSoundBufferAsset(rapidxml::xml_node<>* asset_node) {
	sf::SoundBuffer* new_sound = new sf::SoundBuffer();
	new_sound->loadFromFile(resource_manager_->GetResourcesPath() + asset_node->value());
	return new SoundBufferAsset(new_sound);
}

FontAsset* AssetFactory::InstantiateFontAsset(rapidxml::xml_node<>* asset_node) {
	sf::Font* new_font = new sf::Font();
	new_font->loadFromFile(resource_manager_->GetResourcesPath() + asset_node->value());
	return new FontAsset(new_font);
}