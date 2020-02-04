#include "pch.h"
#include "Game.h"


// When the game is created, create instances of all necessay objects
Game::Game()
{
	display = new Display();
	detector = new ObjectDetector();
	bluetooth = new Bluetooth();
	RUN = true;
}
/* NOT USING CURRENTLY */
void Game::GameMain(HWND* hImage, HBITMAP* image)
{
	while (this->Running())
	{
		waitKey(100);
		if (this->display->update_image)
		{
			//this->display->LoadImages(DISPLAY_IMAGE, hImage, image);
			SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);
			this->display->update_image = false;
		}

	}
}

// To let windows process know that this process is still running
bool Game::Running() 
{
	return RUN;
}


// Game ending protocol
void Game::stop()
{
	// Revert the current image to the base image, let main process know game is over
	display->revert_image();
	RUN = false;
}

