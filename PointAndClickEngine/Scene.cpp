#include "Scene.h"
#include "Time.h"

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
	//Those iterations don't have to be backwards as no object would be destroyed during the render cycle
	std::list<IRenderable*>::iterator it;

	for (it = active_renderers_4_.begin(); it != active_renderers_4_.end(); it++) {
		(*it)->Render(window);
	}
	for (it = active_renderers_3_.begin(); it != active_renderers_3_.end(); it++) {
		(*it)->Render(window);
	}
	for (it = active_renderers_2_.begin(); it != active_renderers_2_.end(); it++) {
		(*it)->Render(window);
	}
	for (it = active_renderers_1_.begin(); it != active_renderers_1_.end(); it++) {
		(*it)->Render(window);
	}
	for (it = active_renderers_0_.begin(); it != active_renderers_0_.end(); it++) {
		(*it)->Render(window);
	}
}

void Scene::StopScene() {
	std::list<CharacterController*>::iterator it;
	for (it = (character_controllers_).begin(); it != character_controllers_.end(); it++) {
		(*it)->StopMovement();
	}
}

void Scene::AddEntity(Entity* entity) {
	entities_.push_back(entity);
	if (entity->GetComponent(ComponentType::kSpriteRenderer) != NULL) {

		AddRenderer(dynamic_cast<IRenderable*>(entity->GetComponent(ComponentType::kSpriteRenderer)));
	}
	if (entity->GetComponent(ComponentType::kCharacterController) != NULL) {
		character_controllers_.push_back(dynamic_cast<CharacterController*>(entity->GetComponent(ComponentType::kCharacterController)));
	}
}

void Scene::AddRenderer(IRenderable* renderable) {
	switch (renderable->GetRenderLayer()) {
	case 0:
		active_renderers_0_.push_back(renderable);
		break;
	case 1:
		active_renderers_1_.push_back(renderable);
		break;
	case 2:
		active_renderers_2_.push_back(renderable);
		break;
	case 3:
		active_renderers_3_.push_back(renderable);
		break;
	case 4:
		active_renderers_4_.push_back(renderable);
		break;
	}
}

bool Scene::CheckOverlapWithCharacterController(SpriteRenderer* sprite_renderer) {
	std::list<CharacterController*>::iterator it;
	for (it = character_controllers_.begin(); it != character_controllers_.end(); it++) {
		if ((*it)->CheckOverlap(sprite_renderer)) {
			return true;
		}
	}
	return false;
}