#pragma once
#include <SFML/Graphics.hpp>

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

