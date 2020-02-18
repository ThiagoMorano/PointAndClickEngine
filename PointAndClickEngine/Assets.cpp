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
SoundBufferAsset::SoundBufferAsset() {}
SoundBufferAsset::SoundBufferAsset(sf::SoundBuffer* sound) : sound_buffer_(sound) {
}

SoundBufferAsset::~SoundBufferAsset() {
	delete(sound_buffer_);
}
#pragma endregion
