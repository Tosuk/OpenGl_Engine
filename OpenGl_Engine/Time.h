#pragma once
#ifndef TIME_H
#define TIME_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>


//you could put everything in the class Time in the header file, but it is better to put the implementation in a cpp file
//but you could also implement the function in the header file which might be better for faster compilation and better optimization
//but it is not recommended to put the implementation in the header file
//im not sure if this is the best way to implement the time class, but it works

class Time
{
public:
	static float deltaTime;
	static float lastFrame;
	static void updateTime();
	static void Timer(float time); //is not used and also Problematic because its static 
								   //and a timer should be a object so you can use multiple timers(probebly putting it into its own class)
};

#endif 