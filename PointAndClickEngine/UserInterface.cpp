#include "UserInterface.h"
#include "Time.h"


// Called by the Game class to start displaying a text
void UserInterface::ActivateText(sf::Text* text, float time) {
	should_show_text_ = true;
	text_to_show_ = text;
	time_to_show_text_ = time;
	elapsed_time_text_ = 0.0f;
}


void UserInterface::Render(sf::RenderWindow* window) {
	if (should_show_text_) {
		ShowText(window);
	}
}


// Calculates the time for it to keep showing the text
void UserInterface::ShowText(sf::RenderWindow* window) {
	if (elapsed_time_text_ < time_to_show_text_) {
		elapsed_time_text_ += Time::Instance()->DeltaTime();
		window->draw(*text_to_show_);
	}
	else {
		StopShowingText();
	}
}


// Deactivates the text
void UserInterface::StopShowingText() {
	should_show_text_ = false;
	elapsed_time_text_ = 0.0f;
	text_to_show_ = NULL;
}
