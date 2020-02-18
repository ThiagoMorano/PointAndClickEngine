#include "AssetFactory.h"

Asset* AssetFactory::CreateAsset(AssetData* assetData) {
	Asset* asset = NULL;

	if (assetData->type_.compare("image") == 0) {
		asset = new SpriteAsset();
	}
	else if (assetData->type_.compare("sound") == 0) {
		asset = new SoundAsset();
	}
	asset->id_ = assetData->id_;

	return asset;
}