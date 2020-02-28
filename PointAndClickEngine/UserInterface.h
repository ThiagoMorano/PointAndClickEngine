#pragma once
#include <SFML/Graphics.hpp>

/// User interface is used to render on top of the scene.
/// It is also not dependent on the a specific scene.
///
/// Currently it's only used to display texts from textResponses


class UserInterface
{
public:
	void Render(sf::RenderWindow*);

	void ActivateText(sf::Text*, float);
	void StopShowingText();
	void ShowText(sf::RenderWindow*);

private:
	sf::Text* text_to_show_;
	bool should_show_text_;
	float time_to_show_text_;
	float elapsed_time_text_;
};

