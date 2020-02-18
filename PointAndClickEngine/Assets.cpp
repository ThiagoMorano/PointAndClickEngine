#include "Assets.h"

#pragma region Asset
Asset::Asset() {
}


Asset::~Asset() {
}
#pragma endregion

#pragma region SpriteAsset
SpriteAsset::SpriteAsset() {}
SpriteAsset::SpriteAsset(sf::Sprite* sprite) : sprite_(sprite) {
}

SpriteAsset::~SpriteAsset() {
	delete(sprite_);
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
