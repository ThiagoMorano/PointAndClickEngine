#pragma once
#include <SFML/System.hpp>

/// Time wraps a sf::Clock and exposes thenecessary behaviour using DeltaTime()
///
/// It was created as its own class in case there would be necessary to handle
/// time differently for specific objects.

// Singleton
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

