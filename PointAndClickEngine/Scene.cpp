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
	std::list<IRenderable*>::iterator it;
	for (it = active_renderers_.begin(); it != active_renderers_.end(); it++) {
		((SpriteRenderer*)(*it))->Render(window);
	}
}

void Scene::AddEntity(Entity* entity) {
	entities_.push_back(entity);
	if (entity->GetComponent(ComponentType::kSpriteRenderer) != NULL) {
		active_renderers_.push_back((IRenderable*)entity->GetComponent(ComponentType::kSpriteRenderer));
	}
}