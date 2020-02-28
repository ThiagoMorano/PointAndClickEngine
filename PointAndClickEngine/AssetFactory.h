#pragma once
#include "rapidxml-1.13/rapidxml.hpp"
#include "Assets.h"


/// AssetFactory is a class of the factory pattern that handles the creation of asset objects
/// It does so by having some xml handling logic, so the factory is able to read the <asset> node and
/// instantiate the correct asset based on the node's information.
///
/// The factory has a different method for each type of asset


// Forward declaration
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
