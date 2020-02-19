#pragma once
#include "Entity.h"

class EntityFactory
{
public:
	Entity* CreateEntity(EntityData*);
};