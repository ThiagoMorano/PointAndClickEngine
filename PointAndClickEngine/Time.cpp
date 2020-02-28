#include "Time.h"

Time::~Time() {
	delete(instance_);
}

// Instance is created via a call from the Game class.
// This saves checking if the instance exists every call, as well as
// making sure the clock only starts once the game starts
void Time::Init() {
	if (instance_ == NULL) {
		instance_ = new Time();
	}
}


Time::Time() {
	elapsed_time_ = clock_.restart();
}


Time* Time::Instance() {
	return instance_;
}


// Returns time since last frame and the beginning of the new frame
float Time::DeltaTime() {
	return elapsed_time_.asSeconds();
}


// Resets clock
void Time::NewFrame() {
	elapsed_time_ = clock_.restart();
}