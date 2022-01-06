#include "pch.h"
#include "Display.h"


using namespace cv;
using namespace std;

constexpr auto WINDOW_NAME = "SD2";
constexpr auto GRID_NAME = "images/png/wilderness-map-grid.png";
constexpr auto CURRENT_NAME = "images/png/wilderness-map-current.png";
constexpr auto NPC_NAME = "images/png/dragon2.png";
//constexpr auto LAST = "images/last_modification.jpg";
//constexpr auto CURRENT = "images/last_modification.jpg";
//constexpr auto LOADING = "images/Loading.jpg";

int LAST_FLAG = 0;
bool GLOBAL_KILL = true;

Display::Display()
{

}

// Needed to convert an image to bmp
void Display::convert_image(string imgPath)
{
	// Open and create new filename 
	Mat image = this->open_image(imgPath);
	Mat image_bmp;
	string newImgPath;
	string::size_type i = imgPath.find('.');
	newImgPath = imgPath;
	newImgPath.erase(i, imgPath.length() - i);
	newImgPath.append(".bmp");

	// Convert image to bmp
	image.convertTo(image_bmp, CV_8UC3);
	
	// Save converted image to new file path
	imwrite(newImgPath, image_bmp);

}


void Display::display_NPC(string filename, int location, Mat image) 
{
	int row, col;

	// Translate location to coordinates
	row = location / 32;
	col = location % 32;
	
	// Open NPC image
	Mat NPC = open_image(NPC_NAME);
	Mat temp;
	Mat image_bmp;

	// If not adding to an already loaded image
	if (image.empty())
		temp = open_image(CURRENT_NAME);
	else temp = image;

	resize(NPC, NPC, Size(40, 30));

	// If the NPC has a transparent channel merge the images
	// Channels 1-3 -> RGB
	// Channel 4 -> Transparency
	if(NPC.channels() == 4)
		drawTransparency(temp, NPC, col * 40, row * 30);

	// Else just overlay the image on top of the map
	else
	{
		// Fully create image
		Mat insetImage(temp, Rect(col * 40, row * 30 , 40, 30));
		NPC.copyTo(insetImage);
	}
	
	// Save images as png and bmp // PNG MAY NOT BE NEEDED IN FINAL VERSION
	imwrite("images/png/wilderness-map-current.png", temp);

	temp.convertTo(image_bmp, CV_8UC3);
	imwrite("images/bmp/wilderness-map-current.bmp", image_bmp);
	
	update_image = true;

	return;
}

void Display::drawTransparency(Mat frame, Mat transp, int xPos, int yPos) 
{
	Mat mask;
	vector<Mat> layers;

	// Splits the layers of the transparent image
	split(transp, layers); // seperate channels

	// Creates an image using the RGB layers of the transparent image
	Mat rgb[3] = { layers[0],layers[1],layers[2] };

	// Mask is the transparent channel
	mask = layers[3]; 

	// put together the RGB channels, now transp insn't transparent 
	merge(rgb, 3, transp);

	// Copy transparent image onto map image
	transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
}

void Display::display_area(int distance, int location, int type)
{
	// Load map without NPCs to place the NPCs on top of the effects
	Mat original_map = open_image("images/png/wilderness-map-current.png");
	Mat block, image_bmp;
	float alpha = 0.6;
	int loc_row, loc_col, row, col;

	// Filter the type of area that will be displayed
	if(type == MOVE)
		block = open_image("images/png/good.png");
	else 
		block = open_image("images/png/bad.png");

	// Translate location to coordinates
	loc_row = location / 32;
	loc_col = location % 32;

	// Resize block to the size of a grid space
	resize(block, block, Size(40, 30));
	
	// Final image after all the addition
	Mat final_map = original_map.clone();


	// Initialize row and col
	row = loc_row - distance;
	col = loc_col - distance;

	for (int i = 0; i < distance*2 + 1; i++)
	{
		for (int j = 0; j < distance*2 + 1; j++)
		{
			// If player loction, then do not add space
			if (row == loc_row && col == loc_col) 
			{
				col++;
				continue;
			}

			// Region of interest on the original map to be blended with effect
			Rect roi = Rect(col * 40, row * 30, block.cols, block.rows);

			// Set the ROIs for the selected sections of A and out_image (the same at the moment)
			Mat original_roi = original_map(roi);
			Mat final_roi = final_map(roi);

			// Blend the ROI of A with B into the ROI of out_image
			addWeighted(original_roi, alpha, block, 1 - alpha, 0.0, final_roi);
			col++;
		}
		row++;
		col = loc_col - distance;
	}

	// Place all NPCs onto the final map
	this->addNPCS(final_map);

	// Save the images
	imwrite("images/png/wilderness-map-current.png", final_map);

	final_map.convertTo(image_bmp, CV_8UC3);
	imwrite("images/bmp/wilderness-map-current.bmp", image_bmp);
}

void Display::addNPCS(Mat image)
{
	// Loop over all the NPCs and place them on the passed image
	for (Player player : this->NPCS)
	{
		this->display_NPC(player.get_filename(), player.get_location(), image);
	}
}

Mat Display::open_image(string imagePath) {
	// Read in the image
	Mat image = imread(imagePath, IMREAD_UNCHANGED);

	// Validate image existence
	if (image.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return image;
	}
	return image;
}


void Display::revert_image()
{
	// Clean the image to before NPCs are on the map
	Mat map = open_image(GRID_NAME);
	Mat image_bmp;
	imwrite("images/png/wilderness-map-current.png", map);

	map.convertTo(image_bmp, CV_8UC3);
	imwrite("images/bmp/wilderness-map-current.bmp", image_bmp);
	return;
}

void Display::LoadImages(string imgPath, HWND* hImage, HBITMAP* image)
{
	// Load bitmap for windows application
	*image = (HBITMAP)LoadImageA(NULL, imgPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

}


// Currently used for testing, will be an option if the user's map does not already have
// grid lines
void Display::drawGrid()
{
	//Display::convert_image("images/Current_Game_Images/dragon.png");
	Mat map = open_image("images/bmp/wilderness-map.bmp");
	resize(map, map, Size(1280, 720));
	int i;
	 //Create Grid Cols
	for (i = 0; i <= 1280; i += 40)
		line(map, Point(i, 0), Point(i, 720), Scalar(0, 0, 0));

	 //Create Grid Rows
	for (i = 0; i <= 720; i += 30)
		line(map, Point(0, i), Point(1280, i), Scalar(0, 0, 0));
	imwrite("images/bmp/wilderness-map-grid.bmp", map);
	return;
	

}
