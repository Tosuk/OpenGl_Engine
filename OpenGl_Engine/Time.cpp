#include "Time.h"

float Time::deltaTime = 0.0f;
float Time::lastFrame = 0.0f;

void Time::updateTime()
{
	
	float currentFrame = static_cast<float>(glfwGetTime());
	Time::deltaTime = currentFrame - Time::lastFrame;
	Time::lastFrame = currentFrame;
}

void Time::Timer(float time)
{
	time -= Time::deltaTime;
	if (time <= 0) {
		return;
	}
}
