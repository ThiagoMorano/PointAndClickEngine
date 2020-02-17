#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"

class GameConfig {
public:
	std::string applicationName;
	int screenWidth;
	int screenHeight;
	int fps;
};

class ResourceManager
{
private:
	std::vector<char>* _buffer;
	rapidxml::xml_document<> _xmlDocument;

public:
	std::string gameTitle;
	std::string assetsPath;

	ResourceManager(std::string);

	void LoadData(std::string);

	GameConfig* GetGameConfig();
};

