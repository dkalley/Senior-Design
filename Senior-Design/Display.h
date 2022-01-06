#pragma once
#include "pch.h"
#include "Player.h"

#include <shlwapi.h>

// OpenCV headers
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#pragma comment(lib, "Shlwapi.lib")

using namespace cv;
//using namespace std;


#define MAIN_MENU 1000
#define BTH_CONNECT 1001
#define GM_SELECT 1002
#define SELECT_MAP 1003
#define GAME_VIEW 1004
#define LOAD_SCREEN 1005
#define GM_SELECT_LOAD 1006
#define SAVE_DELETE 1007
#define POP_UP 1008
#define PAUSE_MENU 1009

#define MOVE 0
#define ATTACK 1
#define MOVEXY_MODE 2
#define MAXFILEPATHLENGTH 260

#define GAMEDATAPATH "\\Gaming Wizard\\Game Data\\"
#define GAMELOGSPATH "\\Gaming Wizard\\Game Logs\\"
#define GAMEIMAGEPATH "\\Gaming Wizard\\Game Images\\"
#define UIIMAGES "UI Images\\"
#define NPCIMAGES "NPC Images\\"
#define MAPIMAGES "Map Images\\"
#define MAPS "Maps\\"
#define CURRENTIMAGES "Current Images\\"
#define PREVIEWIMAGES "Preview Images\\"

typedef struct _Action_Struct {
	int x;
	int y;
	int speed;
	int mode;
	int damage_roll;
	int range;
	std::string damage_type;
	std::string bth_id;
	std::string unique_id;
	std::string playertype;
} Action_Struct, *LPAction_Struct;

typedef struct _ActiveNPC {
	std::string filename;
	int x;
	int y;
	std::string uniqueID;
	bool active;
} ActiveNPC, *LPActiveNPC;

class Display
{

private:
	HWND *hwnd, *hImage;
	HBITMAP *image;

public:
	std::string PATHTONPC;
	std::string PATHTOGOOD;
	std::string PATHTOBAD;
	std::string PATHTOCLEAN;
	std::string PATHTOGRID;
	std::string OriginalFileExtension;

	BOOL PAUSE;
	std::vector<ActiveNPC> activeNPCs;

	// Grid space dimensions
	int PREVIEW_X, PREVIEW_Y;
	// Grid space dimensions
	int X_PIXEL_LENGTH, Y_PIXEL_LENGTH;
	// Screen Dimensions
	int X_SCREEN_LENGTH, Y_SCREEN_LENGTH;
	// Physical Screen Dimensions in inches
	int X_PHY_LENGTH, Y_PHY_LENGTH;
	// Physical Screen Dimensions in inches
	int NUM_COL, NUM_ROW;
	// Grid spaces clicked
	BOOL grid[660];
	BOOL occupied[660];
	BOOL NPCS[660];
	BOOL actionflag;
	//LPAction_Struct lastaction;

	void Remove_Spot(int location);
	void Remove_Spot(int row, int col);
	void Display_Spot(int location, int type);
	void Display_Spot(int ptx, int pty, int type);
	void Display_NPC(std::vector<Player *> NPCs, int x, int y);
	void LoadImages(std::string imgPath, HWND* hImage, HBITMAP* image);
	void drawGrid();
	cv::Mat drawTransparency(Mat frame, Mat transp, int xPos, int yPos);
	void display_area(int distance, int location, int ptx, int pty, int type);
	void display_area(Action_Struct action);
	void remove_area(int distance, int location, int ptx, int pty, int type);
	void remove_area(LPAction_Struct action);
	void addNPCS(Mat image);

	void move_npc(int gridspace, int prevx, int prevy);
	void Process_Point(LONG ptx, LONG pty, int Mode);
	void TestMouse();
	Mat grid_image;
	//std::vector<Player> NPCS;
	std::string display_pipeline;
	bool update_image;
	void display_NPC(std::string filename, int location, Mat image);
	void display_NPC(std::string filename, int location);
	Display(HWND *hwnd, HBITMAP *image, HWND *hImage);
	Mat open_image(std::string imagePath);
	void convert_image(std::string imgPath);
	void revert_image();
	std::string Create_Preview(std::string imagePath, std::string pathtopreview);
	std::string PrepareMap(wchar_t *mapname, std::string folderpath, std::string appdata);
	std::string drawGrid(std::string imagepath, std::string folderpath, std::string appdata);
	void SaveOriginalMap(std::string imagePath, std::string pathtomaps);
	void CleanCurrentFolder(std::string mapname, std::string pathtocurrent);
	void ShowActiveNPCs(std::string filepath);
};


