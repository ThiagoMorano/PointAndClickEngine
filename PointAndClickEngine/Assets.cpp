#include "Assets.h"

#pragma region Asset
Asset::Asset() {
}


Asset::~Asset() {
}
#pragma endregion

#pragma region SpriteAsset
TextureAsset::TextureAsset() {}
TextureAsset::TextureAsset(sf::Texture* texture) : texture_(texture) {
}

TextureAsset::~TextureAsset() {
	delete(texture_);
}
#pragma endregion

#pragma region SoundAsset
SoundAsset::SoundAsset() {}
SoundAsset::SoundAsset(sf::Sound* sound) : sound_(sound) {
}

SoundAsset::~SoundAsset() {
	delete(sound_);
}
#pragma endregion
