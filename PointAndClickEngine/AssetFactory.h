#pragma once
#include <string>
#include "Assets.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetFactory {
public:
	Asset* CreateAsset(AssetData* assetData);
};