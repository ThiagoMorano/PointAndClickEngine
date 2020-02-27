#pragma once
#include <SFML/System.hpp>

class Time
{
	friend class Game;

public:
	~Time();

	static Time* Instance();
	float DeltaTime();


private:
	Time();

	static void Init();
	void NewFrame();

	static Time* instance_;
	sf::Clock clock_;
	sf::Time elapsed_time_;
};

