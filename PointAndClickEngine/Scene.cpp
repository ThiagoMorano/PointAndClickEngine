#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
	std::list<Entity*>::iterator it;
	for (it = entities_.begin(); it != entities_.end(); it++) {
		delete(*it);
	}
}

void Scene::Update() {
	std::list<Entity*>::iterator it;
	for (it = entities_.begin(); it != entities_.end(); it++) {
		(*it)->Update();
	}
}

void Scene::Render(sf::RenderWindow* window) {
	//This iteration doesn't have to be backwards as no object would be destroyed during the render cycle
	std::list<IRenderable*>::iterator it;
	for (it = active_renderers_.begin(); it != active_renderers_.end(); it++) {
		(*it)->Render(window);
	}
}

void Scene::AddEntity(Entity* entity) {
	entities_.push_back(entity);
	if (entity->GetComponent(ComponentType::kSpriteRenderer) != NULL) {
		active_renderers_.push_back(dynamic_cast<IRenderable*>(entity->GetComponent(ComponentType::kSpriteRenderer)));
	}
}

bool Scene::CheckOverlapCharacterControllerWithInteractables(CharacterController* character_controller) {
	std::list<Interactable*>::iterator it;
	for (it = interactable_items_.begin(); it != interactable_items_.end(); it++) {
		(*it)->OverlappingCharacterController();
	}
	return false;
}