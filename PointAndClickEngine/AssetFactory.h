#pragma once
#include "rapidxml-1.13/rapidxml.hpp"
#include "Assets.h"


class ResourceManager;


class AssetFactory {
public:
	AssetFactory(ResourceManager* resource_manager);

	Asset* CreateAsset(rapidxml::xml_node<>* asset_node);

private:
	ResourceManager* resource_manager_;

	TextureAsset* InstantiateTextureAsset(rapidxml::xml_node<>*);
	SoundBufferAsset* InstantiateSoundBufferAsset(rapidxml::xml_node<>*);
	FontAsset* InstantiateFontAsset(rapidxml::xml_node<>*);
};
