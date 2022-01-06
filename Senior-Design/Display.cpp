#include "pch.h"
#include "Display.h"

int LAST_FLAG = 0;
bool GLOBAL_KILL = true;

Display::Display(HWND *hwnd, HBITMAP *image, HWND *hImage)
{
	this->hwnd = hwnd;
	this->image = image;
	this->hImage = hImage;
	//lastaction = nullptr;
	X_SCREEN_LENGTH = 1280;
	Y_SCREEN_LENGTH = 720;
	X_PHY_LENGTH = 30;
	Y_PHY_LENGTH = 22;
	NUM_COL = 30 - 1;
	NUM_ROW = 22 - 1;
	X_PIXEL_LENGTH = X_SCREEN_LENGTH / X_PHY_LENGTH;
	Y_PIXEL_LENGTH = Y_SCREEN_LENGTH / Y_PHY_LENGTH;
	for (int i = 0; i < 660; i++)
	{
		grid[i] = false;
		NPCS[i] = false;
		occupied[i] = false;
	}
	PREVIEW_X = 600;
	PREVIEW_Y = 338;
	actionflag = false;
	PAUSE = true;
}

void Display::TestMouse()
{
	POINT p;
	int i = 0;
	for (i = 0; i < 100; i++)
	{
		if (!GetCursorPos(&p))
		{
			// Error
		}
	}

}

//void Display::Process_Point(LONG ptx, LONG pty, int Mode)
//{
//	std::ofstream myfile;
//	myfile.open("processpoint.txt", std::ofstream::app);
//
//	int grid_space;
//	switch (Mode)
//	{
//	case MAIN_MENU:
//		break;
//	case BTH_CONNECT:
//		break;
//	case GAME_VIEW:
//		// Determine grid space
//		grid_space = ptx / X_PIXEL_LENGTH + pty / Y_PIXEL_LENGTH * X_PHY_LENGTH;
//		myfile << "X: " << ptx / X_PIXEL_LENGTH << "\tY: " << pty / Y_PIXEL_LENGTH << std::endl;
//		myfile << "X: " << ptx << "\tY: " << pty << std::endl;
//		myfile << "Grid Space: " << grid_space << std::endl;
//		//24 rows 32 cols
//		// Highlight grid space
//
//		// If display area is active
//		if (lastaction != nullptr)
//		{
//			myfile << "lastaction is not null" << std::endl;
//			// If the selected space is highlighted
//			if (grid[grid_space])
//			{
//				myfile << "Selected gridspace is highlighted" << std::endl;
//				myfile << lastaction->x << " " << lastaction->y << std::endl;
//				// Remove area
//				remove_area(lastaction);
//				LoadImages("images/bmp/wilderness-map-current.bmp", this->hImage, this->image);
//				SendMessageW(*this->hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);
//				// Update player
//			}
//		}
//
//		break;
//		if (!grid[grid_space])
//		{
//			myfile << "Display spot" << std::endl;
//			Display_Spot(grid_space, MOVE);
//			grid[grid_space] = true;
//		}
//		else
//		{
//			myfile << "Remove spot" << std::endl;
//			grid[grid_space] = false;
//			Remove_Spot(grid_space);
//		}
//			
//		myfile.close();
//		break;
//	}
//}

void Display::Remove_Spot(int location)
{
	//// Save images as png and bmp // PNG MAY NOT BE NEEDED IN FINAL VERSION
	//cv::Mat original_map = open_image("images/png/wilderness-map-grid.png");
	//cv::Mat image_bmp;
	//original_map.convertTo(image_bmp, CV_8UC3);

	//cv::imwrite("images/bmp/wilderness-map-current.bmp", image_bmp);

	//for (int i = 0; i < 768; i++)
	//	if (grid[i])
	//		Display_Spot(i, MOVE);

	// Load map without NPCs to place the NPCs on top of the effects
	cv::Mat original_map = open_image(PATHTOGRID);
	cv::Mat clean_map = open_image(PATHTOCLEAN);
	cv::Mat block, image_bmp;
	//block = open_image("images/png/bad.png");
	float alpha = 1; // No blending
	int loc_row, loc_col, row, col;

	// Translate location to coordinates
	loc_row = location / 30;
	loc_col = location % 30;

	// Final image after all the addition
	cv::Mat final_map = original_map.clone();

	// Region of interest on the original map to be blended with effect
	cv::Rect roi = cv::Rect(loc_col * X_PIXEL_LENGTH, loc_row * Y_PIXEL_LENGTH, X_PIXEL_LENGTH, Y_PIXEL_LENGTH);

	// Set the ROIs for the selected sections of A and out_image (the same at the moment)
	cv::Mat original_roi = original_map(roi);
	cv::Mat clean_roi = clean_map(roi);
	cv::Mat final_roi = final_map(roi);

	//cv::Mat final_roi(final_map, roi);
	clean_roi.copyTo(original_roi);
	// Blend the ROI of A with B into the ROI of out_image
	addWeighted(original_roi, alpha, NULL, 1 - alpha, 0.0, final_roi);

	final_map.convertTo(image_bmp, CV_8UC3);
	cv::imwrite(PATHTOGRID, image_bmp);
}

void Display::Remove_Spot(int col, int row)
{
	//// Save images as png and bmp // PNG MAY NOT BE NEEDED IN FINAL VERSION
	//cv::Mat original_map = open_image("images/png/wilderness-map-grid.png");
	//cv::Mat image_bmp;
	//original_map.convertTo(image_bmp, CV_8UC3);

	//cv::imwrite("images/bmp/wilderness-map-current.bmp", image_bmp);

	//for (int i = 0; i < 768; i++)
	//	if (grid[i])
	//		Display_Spot(i, MOVE);

	// Load map without NPCs to place the NPCs on top of the effects
	cv::Mat original_map = open_image(PATHTOGRID);
	cv::Mat clean_map = open_image(PATHTOCLEAN);
	cv::Mat block, image_bmp;
	//block = open_image("images/png/bad.png");
	float alpha = 1; // No blending
	int loc_row, loc_col;

	// Translate location to coordinates
	loc_row = row;
	loc_col = col;

	// Final image after all the addition
	cv::Mat final_map = original_map.clone();

	// Region of interest on the original map to be blended with effect
	cv::Rect roi = cv::Rect(loc_col * X_PIXEL_LENGTH, loc_row * Y_PIXEL_LENGTH, X_PIXEL_LENGTH, Y_PIXEL_LENGTH);

	// Set the ROIs for the selected sections of A and out_image (the same at the moment)
	cv::Mat original_roi = original_map(roi);
	cv::Mat clean_roi = clean_map(roi);
	cv::Mat final_roi = final_map(roi);

	//cv::Mat final_roi(final_map, roi);
	clean_roi.copyTo(original_roi);
	// Blend the ROI of A with B into the ROI of out_image
	addWeighted(original_roi, alpha, NULL, 1 - alpha, 0.0, final_roi);

	final_map.convertTo(image_bmp, CV_8UC3);
	cv::imwrite(PATHTOGRID, image_bmp);
}

// Needed to convert an image to bmp
void Display::convert_image(std::string imgPath)
{
	// Open and create new filename 
	cv::Mat image = this->open_image(imgPath);
	cv::Mat image_bmp;
	std::string newImgPath;
	std::string::size_type i = imgPath.find('.');
	newImgPath = imgPath;
	newImgPath.erase(i, imgPath.length() - i);
	newImgPath.append(".bmp");

	// Convert image to bmp
	image.convertTo(image_bmp, CV_8UC3);
	
	// Save converted image to new file path
	imwrite(newImgPath, image_bmp);

}

void Display::display_NPC(std::string filename, int location, cv::Mat image)
{
	int row, col;

	// Translate location to coordinates
	row = location / 30;
	col = location % 30;
	
	// Open NPC image
	cv::Mat NPC;// = open_image(NPC_NAME);
	cv::Mat temp;
	cv::Mat image_bmp;

	// If not adding to an already loaded image
	/*if (image.empty())
		temp = open_image(CURRENT_NAME);
	else temp = image;*/

	cv::resize(NPC, NPC, cv::Size(X_PIXEL_LENGTH, Y_PIXEL_LENGTH));

	// If the NPC has a transparent channel merge the images
	// Channels 1-3 -> RGB
	// Channel 4 -> Transparency
	if(NPC.channels() == 4)
		drawTransparency(temp, NPC, col * X_PIXEL_LENGTH, row * Y_PIXEL_LENGTH);

	// Else just overlay the image on top of the map
	else
	{
		// Fully create image
		cv::Mat insertImage(temp, cv::Rect(col * X_PIXEL_LENGTH, row * Y_PIXEL_LENGTH, X_PIXEL_LENGTH, Y_PIXEL_LENGTH));
		NPC.copyTo(insertImage);
	}
	
	temp.convertTo(image_bmp, CV_8UC3);
	cv::imwrite(PATHTOGRID, image_bmp);
	
	update_image = true;

	return;
}

cv::Mat Display::drawTransparency(cv::Mat frame, cv::Mat transp, int xPos, int yPos)
{
	cv::Mat mask;
	std::vector<cv::Mat> layers;
	// Splits the layers of the transparent image
	split(transp, layers); // seperate channels
	// Creates an image using the RGB layers of the transparent image
	cv::Mat rgb[3] = { layers[0],layers[1],layers[2] };

	// Mask is the transparent channel
	mask = layers[3]; 

	// put together the RGB channels, now transp insn't transparent 
	merge(rgb, 3, transp);

	// Copy transparent image onto map image
	try
	{
		// Region of interest on the original map to be blended with effect
		cv::Rect roi = cv::Rect(yPos, xPos, X_PIXEL_LENGTH, Y_PIXEL_LENGTH);

		cv::Mat frameroi = frame(roi);

		mask.convertTo(mask, CV_8U);
		//transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);
		transp.copyTo(frameroi, mask);
	}
	catch (cv::Exception e)
	{
	}

	return frame;
}

void Display::display_area(int distance, int location, int ptx, int pty, int type)
{
	actionflag = true;
	// Load map without NPCs to place the NPCs on top of the effects
	cv::Mat original_map = open_image(PATHTOGRID);
	cv::Mat block, image_bmp, channel4block;
	float alpha = 0.6;
	int loc_row, loc_col, row, col;
	int temploc = location;

	// If no location sent, determine location
	if(temploc == -1)
		temploc = ptx / X_PIXEL_LENGTH + pty / Y_PIXEL_LENGTH * X_PHY_LENGTH;

	// Filter the type of area that will be displayed
	if (type == MOVE)
		block = open_image(PATHTOGOOD);
	else if (type == ATTACK)
		block = open_image(PATHTOBAD);
	else
		return;

	// If the map has 4 channels, and the block doesnt, add a channel
	if (original_map.channels() == 4 && block.channels() != 4)
	{
		cv::Mat matChannels[4];
		cv::split(block, matChannels);

		// create alpha channel
		cv::Mat alpha2 = matChannels[0] + matChannels[1] + matChannels[2];
		matChannels[3] = alpha2;

		cv::merge(matChannels, 4, channel4block);
	}
	// Otherwise no change required
	else
	{
		channel4block = block;
	}

	// Translate location to coordinates
	loc_row = temploc / 30;
	loc_col = temploc % 30;

	// Resize block to the size of a grid space
	cv::resize(channel4block, channel4block, cv::Size(X_PIXEL_LENGTH, Y_PIXEL_LENGTH));
	
	// Final image after all the addition
	cv::Mat final_map = original_map.clone();

	// Initialize row and col
	row = loc_row - distance;
	col = loc_col - distance;

	for (int i = 0; i < distance * 2 + 1; i++)
	{
		// If row is below the image, break for loop, filling is done
		if (row > NUM_ROW)
		{
			break;
		}
		// If row is above image, add to the row and continue
		if (row < 0)
		{
			row++;
			col = loc_col - distance;
			continue;
		}
		for (int j = 0; j < distance * 2 + 1; j++)
		{
			// If the column is to the right of the image, break you are done
			if (col > NUM_COL)
			{
				break;
			}
			// If the column is to the left of the image, increase column and continue
			if (col < 0)
			{
				col++;
				continue;
			}

			// If player loction, then do not add space
			if (row == loc_row && col == loc_col) 
			{
				col++;
				continue;
			}

			// Signal that the grid space is highlighted
			grid[ptx / X_PIXEL_LENGTH + pty / Y_PIXEL_LENGTH * X_PHY_LENGTH] = true;

			// Region of interest on the original map to be blended with effect
			cv::Rect roi = cv::Rect(col * X_PIXEL_LENGTH, row * Y_PIXEL_LENGTH, X_PIXEL_LENGTH, Y_PIXEL_LENGTH);

			// Set the ROIs for the selected sections of A and out_image (the same at the moment)
			cv::Mat original_roi = original_map(roi);
			cv::Mat final_roi = final_map(roi);

			// Blend the ROI of A with B into the ROI of out_image
			addWeighted(original_roi, alpha, channel4block, 1 - alpha, 0.0, final_roi);
			col++;
		}
		row++;
		col = loc_col - distance;
	}

	// Place all NPCs onto the final map
	this->addNPCS(final_map);

	final_map.convertTo(image_bmp, CV_8UC3);
	cv::imwrite(PATHTOGRID, image_bmp);
}

void Display::display_area(Action_Struct action)
{
	actionflag = true;
	//lastaction = action;

	// Load map without NPCs to place the NPCs on top of the effects
	cv::Mat original_map = open_image(PATHTOGRID);
	cv::Mat block, image_bmp, channel4block;
	float alpha = 0.6;
	int loc_row, loc_col, row, col;
	int temploc;
	int distance;

	// Determine the grid location
	//temploc = action.x / X_PIXEL_LENGTH + action.y / Y_PIXEL_LENGTH * X_PHY_LENGTH;

	// Filter the type of area that will be displayed
	if (action.mode == MOVE)
	{
		block = open_image(PATHTOGOOD);
		distance = action.speed / 5;
	}

	else if (action.mode == ATTACK)
	{
		block = open_image(PATHTOBAD);
		distance = action.range / 5;
	}

	else
		return;

	// If the map has 4 channels, and the block doesnt, add a channel
	if (original_map.channels() == 4 && block.channels() != 4)
	{
		cv::Mat matChannels[4];
		cv::split(block, matChannels);

		// create alpha channel
		cv::Mat alpha2 = matChannels[0] + matChannels[1] + matChannels[2];
		matChannels[3] = alpha2;

		cv::merge(matChannels, 4, channel4block);
	}
	// Otherwise no change required
	else
	{
		channel4block = block;
	}

	// Translate location to coordinates
	//loc_row = temploc / 32;
	//loc_col = temploc % 32;
	loc_row = action.y;
	loc_col = action.x;

	// Resize block to the size of a grid space
	cv::resize(channel4block, channel4block, cv::Size(X_PIXEL_LENGTH, Y_PIXEL_LENGTH));

	// Final image after all the addition
	cv::Mat final_map = original_map.clone();

	// Initialize row and col
	row = loc_row - distance;
	col = loc_col - distance;
	
	for (int i = 0; i < distance * 2 + 1; i++)
	{
		// If row is below the image, break for loop, filling is done
		if (row > NUM_ROW)
		{
			break;
		}
		// If row is above image, add to the row and continue
		if (row < 0)
		{
			row++;
			col = loc_col - distance;
			continue;
		}
		for (int j = 0; j < distance * 2 + 1; j++)
		{
			// If the column is to the right of the image, break you are done
			if (col > NUM_COL)
			{
				break;
			}
			// If the column is to the left of the image, increase column and continue
			if (col < 0)
			{
				col++;
				continue;
			}
			// If player loction, then do not add space
			if (row == loc_row && col == loc_col)
			{
				col++;
				continue;
			}

			// Signal that the grid space is highlighted
			grid[row*X_PHY_LENGTH + col] = true;
			// Region of interest on the original map to be blended with effect
			cv::Rect roi = cv::Rect(col * X_PIXEL_LENGTH, row * Y_PIXEL_LENGTH, X_PIXEL_LENGTH, Y_PIXEL_LENGTH);
			// Set the ROIs for the selected sections of A and out_image (the same at the moment)
			cv::Mat original_roi = original_map(roi);
			cv::Mat final_roi = final_map(roi);
			// Blend the ROI of A with B into the ROI of out_image
			addWeighted(original_roi, alpha, channel4block, 1 - alpha, 0.0, final_roi);
			col++;
		}
		row++;
		col = loc_col - distance;
	}

	// Place all NPCs onto the final map
	//this->addNPCS(final_map);

	final_map.convertTo(image_bmp, CV_8UC3);
	PAUSE = true;
	cv::imwrite(PATHTOGRID, image_bmp);
	PAUSE = false;
}

void Display::remove_area(int distance, int location, int ptx, int pty, int type)
{
	actionflag = true;
	// Load map without NPCs to place the NPCs on top of the effects
	cv::Mat original_map = open_image(PATHTOGRID);
	cv::Mat block, image_bmp;
	float alpha = 0.6;
	int loc_row, loc_col, row, col;
	int temploc = location;

	// If no location sent, determine location
	if (temploc == -1)
		temploc = ptx / X_PIXEL_LENGTH + pty / Y_PIXEL_LENGTH * X_PHY_LENGTH;

	// Translate location to coordinates
	loc_row = temploc / 30;
	loc_col = temploc % 30;

	// Resize block to the size of a grid space
	cv::resize(block, block, cv::Size(X_PIXEL_LENGTH, Y_PIXEL_LENGTH));

	// Final image after all the addition
	cv::Mat final_map = original_map.clone();

	// Initialize row and col
	row = loc_row - distance;
	col = loc_col - distance;

	for (int i = 0; i < distance * 2 + 1; i++)
	{
		// If row is below the image, break for loop, filling is done
		if (row > NUM_ROW)
		{
			break;
		}
		// If row is above image, add to the row and continue
		if (row < 0)
		{
			row++;
			col = loc_col - distance;
			continue;
		}
		for (int j = 0; j < distance * 2 + 1; j++)
		{
			// If the column is to the right of the image, break you are done
			if (col > NUM_COL)
			{
				break;
			}
			// If the column is to the left of the image, increase column and continue
			if (col < 0)
			{
				col++;
				continue;
			}

			// If player loction, then do not add space
			if (row == loc_row && col == loc_col)
			{
				col++;
				continue;
			}

			// Signal that the grid space is highlighted
			grid[ptx / X_PIXEL_LENGTH + pty / Y_PIXEL_LENGTH * X_PHY_LENGTH] = false;
			Remove_Spot(ptx / X_PIXEL_LENGTH + pty / Y_PIXEL_LENGTH * X_PHY_LENGTH);
			col++;
		}
		row++;
		col = loc_col - distance;
	}

	// Place all NPCs onto the final map
	this->addNPCS(final_map);

	final_map.convertTo(image_bmp, CV_8UC3);
	cv::imwrite(PATHTOGRID, image_bmp);
}

void Display::remove_area(LPAction_Struct action)
{
	actionflag = true;
	// Load map without NPCs to place the NPCs on top of the effects
	cv::Mat clean_map = open_image(PATHTOCLEAN);
	cv::Mat original_map = open_image(PATHTOGRID);
	cv::Mat block, image_bmp;
	// Final image after all the addition
	cv::Mat final_map = original_map.clone();
	float alpha = 0;
	int loc_row, loc_col, row, col;
	int temploc;
	int distance;

	if(action->mode == MOVE)
		distance = action->speed / 5;
	else if(action->mode == ATTACK)
		distance = action->range / 5;

	// Determine the grid space
	//temploc = action->x / X_PIXEL_LENGTH + action->y / Y_PIXEL_LENGTH * X_PHY_LENGTH;

	// Translate location to coordinates
	loc_row = action->y;
	loc_col = action->x;


	// Initialize row and col
	row = loc_row - distance;
	col = loc_col - distance;

	for (int i = 0; i < distance * 2 + 1; i++)
	{
		// If row is below the image, break for loop, filling is done
		if (row > NUM_ROW)
		{
			break;
		}
		// If row is above image, add to the row and continue
		if (row < 0)
		{
			row++;
			col = loc_col - distance;
			continue;
		}
		for (int j = 0; j < distance * 2 + 1; j++)
		{
			// If the column is to the right of the image, break you are done
			if (col > NUM_COL)
			{
				break;
			}
			// If the column is to the left of the image, increase column and continue
			if (col < 0)
			{
				col++;
				continue;
			}
			// If player loction, then do not add space
			if (row == loc_row && col == loc_col)
			{
				col++;
				continue;
			}

			// Signal that the grid space is highlighted
			grid[row*X_PHY_LENGTH + col] = false;

			//// Region of interest on the original map to be blended with effect
			//cv::Rect roi = cv::Rect(col * X_PIXEL_LENGTH, row * Y_PIXEL_LENGTH, block.cols, block.rows);

			//// Set the ROIs for the selected sections of A and out_image (the same at the moment)
			//cv::Mat original_roi = original_map(roi);
			//cv::Mat final_roi = final_map(roi);

			//// Blend the ROI of A with B into the ROI of out_image
			//addWeighted(original_roi, alpha, block, 1 - alpha, 0.0, final_roi);

			// Region of interest on the original map to be blended with effect
			cv::Rect roi = cv::Rect(col * X_PIXEL_LENGTH, row * Y_PIXEL_LENGTH, X_PIXEL_LENGTH, Y_PIXEL_LENGTH);

			// Set the ROIs for the selected sections of A and out_image (the same at the moment)
			cv::Mat original_roi = original_map(roi);
			cv::Mat clean_roi = clean_map(roi);
			cv::Mat final_roi = final_map(roi);

			//cv::Mat final_roi(final_map, roi);
			//clean_roi.copyTo(original_roi);
			// Blend the ROI of A with B into the ROI of out_image
			addWeighted(original_roi, alpha, clean_roi, 1 - alpha, 0.0, final_roi);

			//if (NPCS[row*X_PHY_LENGTH + col])
			//	display_NPC("images/png/dragon2_white.png", row*X_PHY_LENGTH + col);

			//Remove_Spot(row, col);
			col++;
		}
		row++;
		col = loc_col - distance;
	}

	// Place all NPCs onto the final map
	//this->addNPCS(final_map);

	//lastaction = nullptr;

	final_map.convertTo(image_bmp, CV_8UC3);
	cv::imwrite(PATHTOGRID, image_bmp);
}

void Display::Display_Spot(int location, int type)
{
	// Load map without NPCs to place the NPCs on top of the effects
	cv::Mat original_map = open_image(PATHTOGRID);
	cv::Mat block, channel4block, image_bmp;
	float alpha = 0.6;
	int loc_row, loc_col, row, col;

	// Filter the type of area that will be displayed
	if (type == MOVE)
		block = open_image(PATHTOGOOD);
	else if (type == ATTACK)
		block = open_image(PATHTOBAD);
	else
		return;

	// If the map has 4 channels, and the block doesnt, add a channel
	if (original_map.channels() == 4 && block.channels() != 4)
	{
		cv::Mat matChannels[4];
		cv::split(block, matChannels);

		// create alpha channel
		cv::Mat alpha2 = matChannels[0] + matChannels[1] + matChannels[2];
		matChannels[3] = alpha2;

		cv::merge(matChannels, 4, channel4block);
	}
	// Otherwise no change required
	else
	{
		channel4block = block;
	}

	// Translate location to coordinates
	loc_row = location / 30;
	loc_col = location % 30;

	// Resize block to the size of a grid space
	cv::resize(channel4block, channel4block, cv::Size(X_PIXEL_LENGTH, Y_PIXEL_LENGTH));

	// Final image after all the addition
	cv::Mat final_map = original_map.clone();

	// Region of interest on the original map to be blended with effect
	cv::Rect roi = cv::Rect(loc_col * X_PIXEL_LENGTH, loc_row * Y_PIXEL_LENGTH, X_PIXEL_LENGTH, Y_PIXEL_LENGTH);

	// Set the ROIs for the selected sections of A and out_image (the same at the moment)
	cv::Mat original_roi = original_map(roi);
	cv::Mat final_roi = final_map(roi);

	// Blend the ROI of A with B into the ROI of out_image
	addWeighted(original_roi, alpha, channel4block, 1 - alpha, 0.0, final_roi);
	
	final_map.convertTo(image_bmp, CV_8UC3);
	cv::imwrite(PATHTOGRID, image_bmp);
}

void Display::Display_Spot(int ptx, int pty, int type)
{
	// Load map without NPCs to place the NPCs on top of the effects
	cv::Mat original_map = open_image(PATHTOGRID);
	//original_map.convertTo(original_map, CV_8UC3);
	cv::Mat block, image_bmp, channel4block;
	float alpha = 0.6;
	int loc_row, loc_col, row, col, temploc;

	// Filter the type of area that will be displayed
	if (type == MOVE)
		block = open_image(PATHTOGOOD);
	else if (type == ATTACK)
		block = open_image(PATHTOBAD);
	else
		return;

	// If the map has 4 channels, and the block doesnt, add a channel
	if (original_map.channels() == 4 && block.channels() != 4)
	{
		cv::Mat matChannels[4];
		cv::split(block, matChannels);

		// create alpha channel
		cv::Mat alpha2 = matChannels[0] + matChannels[1] + matChannels[2];
		matChannels[3] = alpha2;

		cv::merge(matChannels, 4, channel4block);
	}
	// Otherwise no change required
	else
	{
		channel4block = block;
	}

	temploc = ptx / X_PIXEL_LENGTH + pty / Y_PIXEL_LENGTH * X_PHY_LENGTH;

	// Translate location to coordinates
	loc_row = temploc / 30;
	loc_col = temploc % 30;

	// Resize block to the size of a grid space
	cv::resize(channel4block, channel4block, cv::Size(X_PIXEL_LENGTH, Y_PIXEL_LENGTH));

	// Final image after all the addition
	cv::Mat final_map = original_map.clone();
	//final_map.convertTo(final_map, CV_8UC3);

	// Region of interest on the original map to be blended with effect
	cv::Rect roi = cv::Rect(loc_col * X_PIXEL_LENGTH, loc_row * Y_PIXEL_LENGTH, X_PIXEL_LENGTH, Y_PIXEL_LENGTH);

	// Set the ROIs for the selected sections of A and out_image (the same at the moment)
	cv::Mat original_roi = original_map(roi);
	cv::Mat final_roi = final_map(roi);

	// Blend the ROI of A with B into the ROI of out_image
	addWeighted(original_roi, alpha, channel4block, 1 - alpha, 0.0, final_roi);

	final_map.convertTo(image_bmp, CV_8UC3);
	cv::imwrite(PATHTOGRID, image_bmp);

}

void Display::addNPCS(cv::Mat image)
{
	// Loop over all the NPCs and place them on the passed image
	for (Player player : this->NPCS)
	{
		this->display_NPC(player.get_filename(), player.get_location(), image);
	}
}

cv::Mat Display::open_image(std::string imagePath) {
	// Read in the image
	cv::Mat image = cv::imread(imagePath, cv::IMREAD_UNCHANGED);

	// Validate image existence
	if (image.empty()) {
		return image;
	}
	return image;
}

void Display::revert_image()
{
	// Clean the image to before NPCs are on the map
	cv::Mat map; // = open_image(GRID_NAME);
	cv::Mat image_bmp;
	cv::imwrite("images/png/wilderness-map-current.png", map);

	map.convertTo(image_bmp, CV_8UC3);
	imwrite("images/bmp/wilderness-map-current.bmp", image_bmp);
	return;
}

void Display::LoadImages(std::string imgPath, HWND* hImage, HBITMAP* image)
{
	// Load bitmap for windows application
	*image = (HBITMAP)LoadImageA(NULL, imgPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

// Currently used for testing, will be an option if the user's map does not already have
// grid lines
void Display::drawGrid()
{
	//Display::convert_image("images/Current_Game_Images/dragon.png");
	cv::Mat map = open_image(PATHTOGRID);
	cv::resize(map, map, cv::Size(X_SCREEN_LENGTH, Y_SCREEN_LENGTH));
	int i;
	 //Create Grid Cols
	for (i = 0; i <= X_SCREEN_LENGTH; i += X_PIXEL_LENGTH)
		line(map, cv::Point(i, 0), cv::Point(i, Y_SCREEN_LENGTH), cv::Scalar(0, 0, 0));

	 //Create Grid Rows
	for (i = 0; i <= Y_SCREEN_LENGTH; i += Y_PIXEL_LENGTH)
		line(map, cv::Point(0, i), cv::Point(X_SCREEN_LENGTH, i), cv::Scalar(0, 0, 0));
	cv::imwrite(PATHTOGRID, map);
	return;
	

}

std::string Display::Create_Preview(std::string imagePath, std::string pathtopreview)
{
	std::string imagePath2 = imagePath;

	// Remove prefix
	int i = imagePath2.find_last_of('\\');
	imagePath2.erase(0, i + 1);

	// _grid + postfix
	i = imagePath2.find_last_of('.');
	imagePath2.erase(i, imagePath2.size());

	// Open bmp image
	cv::Mat map = open_image(imagePath);
	// Resize it
	cv::resize(map, map, cv::Size(PREVIEW_X, PREVIEW_Y));

	std::string realnewpath = pathtopreview + imagePath2 + "_preview.bmp";
	
	// Save thumbnail with new string
	cv::imwrite(realnewpath, map);
	return realnewpath;
}

std::string Display::drawGrid(std::string imagepath, std::string folderpath, std::string appdata)
{
	// Delete the postfix	
	std::string newImgPath = imagepath;
	int i = imagepath.find('.');
	newImgPath.erase(i, imagepath.length());

	// Delete the prefix
	i = newImgPath.find_last_of('\\');
	newImgPath.erase(0, i+1);

	std::string prefix = folderpath;
	prefix = prefix + newImgPath + "_grid.bmp";
	//prefix.append("_grid.bmp");

	PATHTOGRID = prefix;

	std::string clean = folderpath;
	clean = clean + newImgPath + ".bmp";
	PATHTOCLEAN = clean;


	cv::Mat map = open_image(imagepath);
	try
	{	
		cv::resize(map, map, cv::Size(X_SCREEN_LENGTH, Y_SCREEN_LENGTH));
	}
	catch (cv::Exception e)
	{
		MessageBoxA(NULL, e.what(), NULL, 0);
	}


	//Create Grid Cols
	for (i = 0; i <= X_SCREEN_LENGTH; i += X_PIXEL_LENGTH)
		line(map, cv::Point(i, 0), cv::Point(i, Y_SCREEN_LENGTH), cv::Scalar(0, 0, 0));

	float temp = X_SCREEN_LENGTH / X_PIXEL_LENGTH;

	line(map, cv::Point(1280, 0), cv::Point(1280, Y_SCREEN_LENGTH), cv::Scalar(0, 0, 0), 40);

	//Create Grid Rows
	for (i = 0; i <= Y_SCREEN_LENGTH; i += Y_PIXEL_LENGTH)
		line(map, cv::Point(0, i), cv::Point(X_SCREEN_LENGTH, i), cv::Scalar(0, 0, 0));
	
	temp = Y_SCREEN_LENGTH / Y_PIXEL_LENGTH;

	line(map, cv::Point(0, 720), cv::Point(X_SCREEN_LENGTH, 720), cv::Scalar(0, 0, 0), 32);

	// Convert map to BMP
	cv::Mat image_bmp;
	map.convertTo(image_bmp, CV_8UC3);

	// Save new grid image
	cv::imwrite(prefix, image_bmp);

	// Convert clean to BMP
	cv::Mat clean_image_bmp;
	map.convertTo(clean_image_bmp, CV_8UC3);

	// Save new grid image
	cv::imwrite(clean, clean_image_bmp);

	return prefix;
}

std::string Display::PrepareMap(wchar_t *mapname, std::string folderpath, std::string appdata)
{
	
	char teststring[MAXFILEPATHLENGTH];
	size_t outsize;
	wcstombs_s(&outsize, teststring, mapname, MAXFILEPATHLENGTH);
	OriginalFileExtension = std::string(teststring);
	std::string newstring = drawGrid(std::string(teststring), folderpath, appdata);
	return newstring;
}

void Display::move_npc(int gridspace, int prevx, int prevy)
{
	// Remove NPC at prevx prevy
	Remove_Spot(prevx, prevy);

	// Place NPC at gridspace
	display_NPC(PATHTONPC + "dragon2_white.png", gridspace);
}


// NEED TO MAKE TRANSPARENT
void Display::display_NPC(std::string filename, int location)
{
	int row, col;
	cv::Mat image = open_image(PATHTOGRID);
	cv::Mat NPC = open_image(filename);
	cv::Mat channel4block, image_bmp;
	cv::resize(NPC, NPC, cv::Size(X_PIXEL_LENGTH, Y_PIXEL_LENGTH));

	// If the map has 4 channels, and the block doesnt, add a channel
	if (image.channels() == 4)
	{
		// Remove channel
		cv::Mat matChannels[4];
		cv::split(image, matChannels);

		cv::merge(matChannels, 3, image);
	}

	if (NPC.channels() == 4)
	{
		// Remove Channel
		cv::Mat matChannels[4];
		cv::split(NPC, matChannels);

		cv::merge(matChannels, 3, NPC);
	}

	if (image.channels() == 4 && NPC.channels() != 4)
	{
		cv::Mat matChannels[4];
		cv::split(NPC, matChannels);

		// create alpha channel
		cv::Mat alpha2 = matChannels[0] + matChannels[1] + matChannels[2];
		matChannels[3] = alpha2;

		cv::merge(matChannels, 4, channel4block);
	}
	// Otherwise no change required
	else
	{
		channel4block = NPC;
	}

	// Translate location to coordinates
	int loc_row = location / 30;
	int loc_col = location % 30;

	// Resize block to the size of a grid space
	cv::resize(channel4block, channel4block, cv::Size(X_PIXEL_LENGTH, Y_PIXEL_LENGTH));

	// Final image after all the addition
	cv::Mat final_map = image.clone();

	// Region of interest on the original map to be blended with effect
	cv::Rect roi = cv::Rect(loc_col * X_PIXEL_LENGTH, loc_row * Y_PIXEL_LENGTH, X_PIXEL_LENGTH, Y_PIXEL_LENGTH);

	// Set the ROIs for the selected sections of A and out_image (the same at the moment)
	cv::Mat original_roi = image(roi);
	cv::Mat final_roi = final_map(roi);

	// Blend the ROI of A with B into the ROI of out_image
	try
	{
		cv::addWeighted(original_roi, 0, channel4block, 1 - 0, 0.0, final_roi);
	}
	catch (cv::Exception e)
	{
		MessageBoxA(NULL, e.what(), NULL, 0);
		return;
	}

	occupied[location] = true;

	final_map.convertTo(image_bmp, CV_8UC3);

	PAUSE = true;
	cv::imwrite(PATHTOGRID, image_bmp);
	PAUSE = false;
	return;
}

void Display::SaveOriginalMap(std::string imagePath, std::string pathtomaps)
{
	std::string imagePath2 = imagePath;

	// Remove prefix
	int i = imagePath2.find_last_of('\\');
	imagePath2.erase(0, i + 1);

	// Open image
	cv::Mat map = open_image(imagePath);

	std::string realnewpath = pathtomaps + imagePath2;
	OriginalFileExtension = realnewpath;

	// Save thumbnail with new string
	cv::imwrite(realnewpath, map);
	return;
}

void Display::CleanCurrentFolder(std::string mapname, std::string pathtocurrent)
{	
	std::string cleanpath, gridpath;
	
	// Create paths
	cleanpath = pathtocurrent + mapname + ".bmp";
	gridpath = pathtocurrent + mapname + "_grid.bmp";

	// Remove clean
	remove(cleanpath.c_str());

	// Remove grid
	remove(gridpath.c_str());
}

void Display::ShowActiveNPCs(std::string filepath)
{
	std::ofstream myfile;
	myfile.open(filepath, std::ofstream::app);
	myfile << "Displaying NPCs" << std::endl;

	for (ActiveNPC npc : activeNPCs)
	{
		int ptx = npc.x;
		int pty = npc.y;
		int grid_space = ptx + pty * X_PHY_LENGTH;
		Remove_Spot(grid_space);
		display_NPC(npc.filename, grid_space);
		myfile << "grid_space: " << grid_space << std::endl;
		myfile << "unique_id: " << npc.uniqueID << std::endl;
		myfile << "filename: " << npc.filename << std::endl;
		DeleteObject(*image);
		*image = (HBITMAP)LoadImageA(NULL, (PATHTOGRID).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);
	}
}

