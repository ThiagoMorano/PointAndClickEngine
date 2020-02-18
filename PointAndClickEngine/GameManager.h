#pragma once
#include <list>
#include "Assets.h"

class GameManager {
public:
	std::list<Asset*>* asset_list_;

	GameManager();
	~GameManager();
};

