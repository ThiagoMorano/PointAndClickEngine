#include "EntityFactory.h"
#include "ResourceManager.h"
#include "Game.h"

// Forward declarations of utility functions
rapidxml::xml_node<>* FindChildNode(rapidxml::xml_node<>* node, const char* node_tag);
rapidxml::xml_attribute<>* FindAttribute(rapidxml::xml_node<>* node, const char* attribute_name);
char* GetAttributeValue(rapidxml::xml_node<>* node, const char* attribute_name);


EntityFactory::EntityFactory(ResourceManager* res_manager) : resource_manager_(res_manager) {}


// Instantiates an entity and populate it with components 
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

// Instantiates the correct component based on component_node name
IComponent* EntityFactory::InstantiateComponent(rapidxml::xml_node<>* component_node) {
	IComponent* component = NULL;

	std::string type_name = component_node->name();
	ComponentType type = ParseComponentType(type_name);
	switch (type) {
	case ComponentType::kCharacterController:
		component = dynamic_cast<IComponent*>(InstantiateCharacterController(component_node));
		break;
	case ComponentType::kSpriteRenderer:
		component = dynamic_cast<IComponent*>(InstantiateSpriteRenderer(component_node));
		break;
	case ComponentType::kAnimatedSprite:
		component = dynamic_cast<IComponent*>(InstantiateAnimatedSprite(component_node));
		break;
	case ComponentType::kAudioSource:
		component = dynamic_cast<IComponent*>(InstantiateAudioSource(component_node));
		break;
	case ComponentType::kInteractable:
		component = dynamic_cast<IComponent*>(InstantiateInteractable(component_node));
		break;
	}

	return component;
}

// Function used to parse a string with the type of the component into the correct ComponentType
ComponentType EntityFactory::ParseComponentType(std::string type_name) {
	if (type_name.compare("characterController") == 0) {
		return ComponentType::kCharacterController;
	}
	else if (type_name.compare("spriteRenderer") == 0) {
		return ComponentType::kSpriteRenderer;
	}
	else if (type_name.compare("animatedSprite") == 0) {
		return ComponentType::kAnimatedSprite;
	}
	else if (type_name.compare("audioSource") == 0) {
		return ComponentType::kAudioSource;
	}
	else if (type_name.compare("interactable") == 0) {
		return ComponentType::kInteractable;
	}
}

// Instantiates and sets up a component of type CharacterController
CharacterController* EntityFactory::InstantiateCharacterController(rapidxml::xml_node<>* character_controller_node) {
	CharacterController* character_controller = new CharacterController();

	character_controller->speed_ = static_cast<float>(atof(GetAttributeValue(character_controller_node, "speed")));

	return character_controller;
}

// Instantiates aand sets up a component of type SpriteRenderer
SpriteRenderer* EntityFactory::InstantiateSpriteRenderer(rapidxml::xml_node<>* sprite_renderer_node) {
	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sf::Sprite* sprite = new sf::Sprite();

	std::string asset_id = GetAttributeValue(sprite_renderer_node, "assetID");

	TextureAsset* texture_asset = dynamic_cast<TextureAsset*>(resource_manager_->GetAssetOfID(asset_id));
	sprite_renderer->InitSprite(texture_asset->texture_);

	sprite_renderer->render_layer_ = atoi(GetAttributeValue(sprite_renderer_node, "renderLayer"));

	return sprite_renderer;
}

// Instantiates and sets up a component of type AnimatedSprites
AnimatedSprite* EntityFactory::InstantiateAnimatedSprite(rapidxml::xml_node<>* animated_sprite_node) {
	AnimatedSprite* animated_sprite = new AnimatedSprite();

	std::string asset_id = GetAttributeValue(animated_sprite_node, "assetID");

	animated_sprite->render_layer_ = atoi(GetAttributeValue(animated_sprite_node, "renderLayer"));
	animated_sprite->number_of_keyframes_ = atoi(GetAttributeValue(animated_sprite_node, "keyframes"));
	animated_sprite->duration_ = static_cast<float>(atof(GetAttributeValue(animated_sprite_node, "duration")));
	animated_sprite->keyframe_width_ = atoi(GetAttributeValue(animated_sprite_node, "frameWidth"));
	animated_sprite->keyframe_height_ = atoi(GetAttributeValue(animated_sprite_node, "frameHeight"));

	TextureAsset* texture_asset = dynamic_cast<TextureAsset*>(resource_manager_->GetAssetOfID(asset_id));
	animated_sprite->InitSprite(texture_asset->texture_);

	return animated_sprite;
}

// Instantiates and sets up a component of type AudioSource
AudioSource* EntityFactory::InstantiateAudioSource(rapidxml::xml_node<>* audio_source_node) {
	AudioSource* audio_source = new AudioSource();
	sf::Sound* sound = new sf::Sound();

	std::string asset_id = GetAttributeValue(audio_source_node, "assetID");

	SoundBufferAsset* sound_buffer_asset = dynamic_cast<SoundBufferAsset*>(resource_manager_->GetAssetOfID(asset_id));
	sound->setBuffer(*(sound_buffer_asset->sound_buffer_));
	audio_source->sound_ = sound;

	return audio_source;
}

// Instantiates and sets up a component of type Interactable, populating it with the correct responses
Interactable* EntityFactory::InstantiateInteractable(rapidxml::xml_node<>* interactable_node) {
	Interactable* interactable_ = new Interactable();

	for (rapidxml::xml_node<>* response_pointer = interactable_node->first_node(); response_pointer != NULL; response_pointer = response_pointer->next_sibling()) {
		IResponse* response = InstantiateReponse(response_pointer);
		interactable_->AddResponse(response);
	}


	return interactable_;
}

// Instantiates a response based on the type of response given in the response_node
IResponse* EntityFactory::InstantiateReponse(rapidxml::xml_node<>* response_node) {
	IResponse* response = NULL;

	std::string response_type = response_node->name();
	if (response_type.compare("soundResponse") == 0) {
		response = dynamic_cast<IResponse*>(InstantiateResponse_Audio(response_node));
	}
	else if (response_type.compare("loadSceneResponse") == 0) {
		response = dynamic_cast<IResponse*>(InstantiateResponse_LoadScene(response_node));
	}
	else if (response_type.compare("textResponse") == 0) {
		response = dynamic_cast<IResponse*>(InstantiateResponse_Text(response_node));
	}

	return response;
}

// Instantiates and sets up a response of type AudioResponse
AudioResponse* EntityFactory::InstantiateResponse_Audio(rapidxml::xml_node<>* audio_response_node) {
	AudioResponse* audio_response = new AudioResponse();
	return audio_response;
}

// Instantiates and sets up a component of type LoadSceneResponse
LoadSceneResponse* EntityFactory::InstantiateResponse_LoadScene(rapidxml::xml_node<>* load_scene_response_node) {
	LoadSceneResponse* load_scene_response = new LoadSceneResponse();
	load_scene_response->scene_id_ = GetAttributeValue(load_scene_response_node, "nextSceneID");
	return load_scene_response;
}

// Instantiates and sets up a component of type TextResponse
TextResponse* EntityFactory::InstantiateResponse_Text(rapidxml::xml_node<>* text_response_node) {
	TextResponse* text_response = new TextResponse();
	
	std::string font_id_ = GetAttributeValue(text_response_node, "fontID");
	sf::Font* font_pointer = dynamic_cast<FontAsset*>(Game::Instance()->resource_manager_->GetAssetOfID(font_id_))->font_;

	text_response->text_ = new sf::Text();
	text_response->text_->setFont(*font_pointer);
	text_response->text_->setString(text_response_node->value());
	text_response->time_to_show_text_ = static_cast<float>(atof(GetAttributeValue(text_response_node, "time")));

	return text_response;
}


// Initializes the transformable of an entity using the values in the <transform> node
void EntityFactory::InitializeTransformable(Entity* entity, rapidxml::xml_node<>* node) {
	rapidxml::xml_node<>* transform_node = FindChildNode(node, "transform");
	// If there's no transform node, transformable will keep the default values
	if (transform_node != NULL) {
		float position_x = static_cast<float>(atof(GetAttributeValue(FindChildNode(transform_node, "position"), "x")));
		float position_y = static_cast<float>(atof(GetAttributeValue(FindChildNode(transform_node, "position"), "y")));
		entity->transformable_.setPosition(position_x, position_y);

		float angle = static_cast<float>(atof(GetAttributeValue(FindChildNode(transform_node, "rotation"), "angle")));
		entity->transformable_.setRotation(angle);

		float scale_x = static_cast<float>(atof(GetAttributeValue(FindChildNode(transform_node, "scale"), "x")));
		float scale_y = static_cast<float>(atof(GetAttributeValue(FindChildNode(transform_node, "scale"), "y")));
		entity->transformable_.setScale(scale_x, scale_y);
	}
}