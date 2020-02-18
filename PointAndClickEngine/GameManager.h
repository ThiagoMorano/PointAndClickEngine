#pragma once
#include <list>
#include "Asset.h"

class GameManager
{
private:
	std::list<Asset> assetList;

public:
	GameManager();
	~GameManager();
};

