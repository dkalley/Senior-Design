#pragma once
#include "pch.h"
#include "Player.h"

// OpenCV headers
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


using namespace cv;
using namespace std;



class Display
{
#define MOVE 0
#define ATTACK 1

private:

public:
	void LoadImages(string imgPath, HWND* hImage, HBITMAP* image);
	void drawGrid();
	void drawTransparency(Mat frame, Mat transp, int xPos, int yPos);
	void display_area(int distance, int location, int type);
	void addNPCS(Mat image);

	Mat grid_image;
	vector<Player> NPCS;
	string display_pipeline;
	bool update_image;
	void display_NPC(string filename, int location, Mat image);
	Display();
	Mat open_image(string imagePath);
	void convert_image(string imgPath);
	void revert_image();
};


