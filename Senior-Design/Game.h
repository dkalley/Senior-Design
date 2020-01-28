#pragma once
#include "pch.h"
#include "Display.h"
#include "ObjectDetector.h"

class Game
{
public:
	Game();
	Display *display;
	ObjectDetector *detector;
	bool Running();
	void stop();

private:
	bool RUN;

};

