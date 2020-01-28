#pragma once
#include "pch.h"

// OpenCV headers
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


using namespace cv;
using namespace std;

class Display
{
private:

public:
	string display_pipeline;
	bool update_image;
	void display_NPC(string filename, int location);
	Display();
	Mat open_image(string imagePath);
	void convert_image(string imgPath);
	void revert_image();
};


