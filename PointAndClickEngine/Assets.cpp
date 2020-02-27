#include "Assets.h"

#pragma region Asset
Asset::Asset() {}
Asset::~Asset() {}
#pragma endregion


#pragma region SpriteAsset
TextureAsset::TextureAsset() : texture_(NULL) {}
TextureAsset::TextureAsset(sf::Texture* texture) : texture_(texture) {}
TextureAsset::~TextureAsset() {
	delete(texture_);
}
#pragma endregion


#pragma region SoundAsset
SoundBufferAsset::SoundBufferAsset() : sound_buffer_(NULL) {}
SoundBufferAsset::SoundBufferAsset(sf::SoundBuffer* sound) : sound_buffer_(sound) {}
SoundBufferAsset::~SoundBufferAsset() {
	delete(sound_buffer_);
}
#pragma endregion


#pragma region FontAsset
FontAsset::FontAsset() : font_(NULL) {}
FontAsset::FontAsset(sf::Font* font) : font_(font) {}
FontAsset::~FontAsset() {
	delete (font_);
}
#pragma endregion

#pragma region SpriteSheetAsset
SpriteSheetAsset::SpriteSheetAsset() : sprite_sheet_(NULL) {}
SpriteSheetAsset::SpriteSheetAsset(sf::Texture* sprite_sheet, int width, int height) : sprite_sheet_(sprite_sheet), width_(width), height_(height) {}
SpriteSheetAsset::~SpriteSheetAsset() {
	delete(sprite_sheet_);
}
#pragma endregion
