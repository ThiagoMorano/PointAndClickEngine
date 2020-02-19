#pragma once
#include "Entities.h"

class EntityFactory
{
public:
	Entity* CreateEntity(EntityData*);
};

