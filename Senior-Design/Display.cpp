#include "pch.h"
#include "Display.h"


using namespace cv;
using namespace std;

constexpr auto WINDOW_NAME = "SD2";
constexpr auto GRID_NAME = "images/Current_Game_Images/map_with_grid.bmp";
constexpr auto LAST = "images/last_modification.jpg";
constexpr auto CURRENT = "images/last_modification.jpg";
constexpr auto LOADING = "images/Loading.jpg";

int LAST_FLAG = 0;
bool GLOBAL_KILL = true;

Display::Display()
{

}

// Needed to convert an image to bmp
void Display::convert_image(string imgPath)
{
	Mat image = this->open_image(imgPath);
	Mat image_bmp;
	string newImgPath;
	string::size_type i = imgPath.find('.');
	newImgPath = imgPath;
	newImgPath.erase(i, imgPath.length() - i);
	newImgPath.append(".bmp");

	image.convertTo(image_bmp, CV_8UC3);

	imwrite(newImgPath, image_bmp);

}


void Display::display_NPC(string filename, int location) {
	int row, col;

	col = (location / 24) % 24;
	row = location % 24;
	
	// Open NPC image
	Mat NPC = open_image(filename);
	Mat temp = open_image(GRID_NAME);
	Mat image_bmp;

	//NPC.convertTo(image_bmp, CV_8UC3);
	resize(NPC, NPC, Size(45, 45));

	// Fully create image
	Mat insetImage(temp, Rect(row * 45, col * 45, 45, 45));
	NPC.copyTo(insetImage);

	//imwrite("images/Current_Game_Images/testing.bmp", image_bmp);
	imwrite("images/Current_Game_Images/shown.bmp", temp);
	update_image = true;

	return;
}

Mat Display::open_image(string imagePath) {
	// Read in the image
	Mat image = imread(imagePath, IMREAD_COLOR);

	// Validate image existence
	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return image;
	}
	return image;
}

void Display::revert_image()
{
	Mat map = open_image(GRID_NAME);
	imwrite("images/Current_Game_Images/shown.bmp", map);
	return;
}
