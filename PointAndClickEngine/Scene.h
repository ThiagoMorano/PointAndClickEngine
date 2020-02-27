#pragma once
#include "Entity.h"

class Scene
{
public:
	std::string id_;
	std::list<Entity*> entities_;
	std::list<IRenderable*> active_renderers_0_;
	std::list<IRenderable*> active_renderers_1_;
	std::list<IRenderable*> active_renderers_2_;
	std::list<IRenderable*> active_renderers_3_;
	std::list<IRenderable*> active_renderers_4_;

	std::list<CharacterController*> character_controllers_;

	Scene();
	~Scene();

	void Update();
	void Render(sf::RenderWindow*);
	void AddEntity(Entity*);
	void AddRenderer(IRenderable*);

	bool CheckOverlapWithCharacterController(SpriteRenderer*);
	void ShowText(sf::Text*);
	void StopShowingText();

private:
	sf::Text* text_to_show_;
	bool should_show_text_;
	//sf::Vector2i text_position_;
};