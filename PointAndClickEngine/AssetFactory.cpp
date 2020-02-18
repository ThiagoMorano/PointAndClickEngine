#include "AssetFactory.h"

Asset* AssetFactory::CreateAsset(AssetData* asset_data) {
	Asset* asset = NULL;

	if (asset_data->type_.compare("image") == 0) {
		sf::Texture* new_texture = new sf::Texture();
		new_texture->loadFromFile(asset_data->path_);
		asset = new TextureAsset(new_texture);
	}
	else if (asset_data->type_.compare("sound") == 0) {
		sf::SoundBuffer* new_sound = new sf::SoundBuffer();
		new_sound->loadFromFile(asset_data->path_);
		asset = new SoundBufferAsset(new_sound);
	}
	asset->id_ = asset_data->id_;

	return asset;
}