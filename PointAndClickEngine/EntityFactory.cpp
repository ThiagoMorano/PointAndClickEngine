#include "EntityFactory.h"

Entity* EntityFactory::CreateEntity(EntityData* entityData) {
	Entity* entity = NULL;
	//if (entityData->type_.compare("sprite") == 0) {
	entity = new Entity();
	//}
	return entity;
}