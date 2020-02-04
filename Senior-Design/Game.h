#pragma once
#include "pch.h"
#include "Display.h"
#include "ObjectDetector.h"
#include "Bluetooth.h"

class Game
{
public:
	Game();
	Display *display;
	ObjectDetector *detector;
	Bluetooth *bluetooth;
	void GameMain(HWND* hImage, HBITMAP* image);
	bool Running();
	void stop();

private:
	bool RUN;

};

