#include "Time.h"

Time::~Time() {
	delete(instance_);
}

Time::Time() {
	elapsed_time_ = clock_.restart();
}

Time* Time::Instance() {
	return instance_;
}

void Time::Init() {
	if (instance_ == NULL) {
		instance_ = new Time();
	}
}

float Time::DeltaTime() {
	return elapsed_time_.asSeconds();
}

void Time::NewFrame() {
	elapsed_time_ = clock_.restart();
}