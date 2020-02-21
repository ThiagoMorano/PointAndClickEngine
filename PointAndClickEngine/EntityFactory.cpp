#include "ResourceManager.h"

EntityFactory::EntityFactory(ResourceManager* res_manager) : resource_manager_(res_manager) {}

rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* node, const char* node_tag) {
	for (rapidxml::xml_node<>* child_node = node->first_node(); child_node != NULL; child_node = child_node->next_sibling()) {
		if (strcmp(child_node->name(), node_tag) == 0) return child_node;
	}
	return NULL;
}

rapidxml::xml_attribute<>* FindAttribute(rapidxml::xml_node<>* node, const char* attribute_name) {
	for (rapidxml::xml_attribute<>* attribute = node->first_attribute(); attribute != NULL; attribute = attribute->next_attribute()) {
		if (strcmp(attribute->name(), attribute_name) == 0) return attribute;
	}
	return NULL;
}


Entity* EntityFactory::CreateEntity(rapidxml::xml_node<>* game_object_node) {
	std::string id = FindAttribute(game_object_node, "id")->value();
	Entity* entity = new Entity(id);

	rapidxml::xml_node<>* components_node = FindChildNode(game_object_node, "components");
	if (components_node != NULL) {
		for (rapidxml::xml_node<>* component_iterator = components_node->first_node(); component_iterator != NULL; component_iterator = component_iterator->next_sibling()) {
			IComponent* component = InstantiateComponent(component_iterator);
			entity->AddComponent(component);
		}
	}

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