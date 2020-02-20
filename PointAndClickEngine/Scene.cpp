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
		(*it)->Render(window);
	}
}