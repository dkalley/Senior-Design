#include "pch.h"
#include "Game.h"


Game::Game()
{
	display = new Display();
	detector = new ObjectDetector();
	RUN = true;
}

bool Game::Running() 
{
	return RUN;
}

void Game::stop()
{
	display->revert_image();
	RUN = false;
}
