#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "rapidxml-1.13/rapidxml.hpp"

#include "AssetFactory.h"


class GameConfig {
public:
	std::string application_name_;
	int screen_width_;
	int screen_height_;
	int fps;
};

class ResourceManager {
public:
	std::string game_title_;
	std::string assets_path_;

	ResourceManager(std::string);
	~ResourceManager();

	void LoadData(std::string);

	GameConfig* GetGameConfig();

	std::list<Asset*>* GetAssetList();

private:
	std::vector<char>* buffer_;
	rapidxml::xml_document<> xml_document_;

	std::string resources_path_;
	std::list<Asset*>* asset_list_;

	void LoadAssetList();
};

