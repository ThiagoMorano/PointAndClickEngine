#include "ResourceManager.h"

// Forward declarations of utility functions
rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* node, const char* node_tag);
rapidxml::xml_attribute<>* FindAttribute(rapidxml::xml_node<>* node, const char* attribute_name);
char* GetAttributeValue(rapidxml::xml_node<>* node, const char* attribute_name);


EntityFactory::EntityFactory(ResourceManager* res_manager) : resource_manager_(res_manager) {}

Entity* EntityFactory::CreateEntity(rapidxml::xml_node<>* game_object_node) {
	std::string id = GetAttributeValue(game_object_node, "id");
	Entity* entity = new Entity(id);

	rapidxml::xml_node<>* components_node = FindChildNode(game_object_node, "components");
	if (components_node != NULL) {
		for (rapidxml::xml_node<>* component_iterator = components_node->first_node(); component_iterator != NULL; component_iterator = component_iterator->next_sibling()) {
			IComponent* component = InstantiateComponent(component_iterator);
			entity->AddComponent(component);
		}
	}

	InitializeTransformable(entity, game_object_node);

	return entity;
}

IComponent* EntityFactory::InstantiateComponent(rapidxml::xml_node<>* component_node) {
	IComponent* component = NULL;

	std::string type_name = component_node->name();
	ComponentType type = ParseComponentType(type_name);
	switch (type) {
	case ComponentType::kSpriteRenderer:
		component = dynamic_cast<IComponent*>(InstantiateSpriteRenderer(component_node));
		break;
	case ComponentType::kAudioSource:
		component = dynamic_cast<IComponent*>(InstantiateAudioSource(component_node));
		break;
	}

	return component;
}

ComponentType EntityFactory::ParseComponentType(std::string type_name) {
	if (type_name.compare("spriteRenderer") == 0) {
		return ComponentType::kSpriteRenderer;
	}
	else if (type_name.compare("audioSource") == 0) {
		return ComponentType::kAudioSource;
	}
}

SpriteRenderer* EntityFactory::InstantiateSpriteRenderer(rapidxml::xml_node<>* node) {
	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sf::Sprite* sprite = new sf::Sprite();

	std::string asset_id = FindAttribute(node, "assetID")->value();

	TextureAsset* texture_asset = dynamic_cast<TextureAsset*>(resource_manager_->GetAssetOfID(asset_id));
	sprite->setTexture(*(texture_asset->texture_));
	sprite_renderer->sprite_ = sprite;

	return sprite_renderer;
}

AudioSource* EntityFactory::InstantiateAudioSource(rapidxml::xml_node<>* node) {
	AudioSource* audio_source = new AudioSource();
	sf::Sound* sound = new sf::Sound();

	std::string asset_id = FindAttribute(node, "assetID")->value();

	SoundBufferAsset* sound_buffer_asset = dynamic_cast<SoundBufferAsset*>(resource_manager_->GetAssetOfID(asset_id));
	sound->setBuffer(*(sound_buffer_asset->sound_buffer_));
	audio_source->sound_ = sound;

	return audio_source;
}

void EntityFactory::InitializeTransformable(Entity* entity, rapidxml::xml_node<>* node) {
	rapidxml::xml_node<>* transform_node = FindChildNode(node, "transform");
	// If there's no transform node, transformable will keep the default values
	if (transform_node != NULL) {
		float position_x = atof(GetAttributeValue(FindChildNode(transform_node, "position"), "x"));
		float position_y = atof(GetAttributeValue(FindChildNode(transform_node, "position"), "y"));
		entity->transformable_.setPosition(position_x, position_y);

		float angle = atof(GetAttributeValue(FindChildNode(transform_node, "rotation"), "angle"));
		entity->transformable_.setRotation(angle);

		float scale_x = atof(GetAttributeValue(FindChildNode(transform_node, "scale"), "x"));
		float scale_y = atof(GetAttributeValue(FindChildNode(transform_node, "scale"), "y"));
		entity->transformable_.setScale(scale_x, scale_y);
	}
}