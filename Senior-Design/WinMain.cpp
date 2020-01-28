#include "pch.h"
#include "Game.h"

// NameSpaces
using namespace std;

// Definition
#define FILE_MENU_NEW 1 
#define FILE_MENU_EXIT 2
#define ABOUT 7
#define LOGIN 8
#define TESTING 10
#define DISPLAY_IMAGE "images/Current_Game_Images/shown.bmp"
//#define DISPLAY_IMAGE "images/Current_Game_Images/map_with_grid.bmp"

// Function Prototypes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND hwnd);
void AddControls(HWND hwnd);
void LoadImages(string imgPath);
void DisplayImages(HWND hwnd);
void GameThread();

// Global Variables
HMENU hMenu;
HWND hLogin, hPass, hImage, hWnd;
HBITMAP image;
LPCWSTR warning;
int location = 0;
Game *game;

// Main
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Default Windows Class
	WNDCLASSW wc = { 0 };

	// Set important parameters
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInstance;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProc;

	if (!RegisterClassW(&wc))
		return -1;

	// Determine monitor dimensions
	HMONITOR hmon = MonitorFromWindow(NULL, MONITOR_DEFAULTTONEAREST);
	MONITORINFO mi = { sizeof(mi) };
	if (!GetMonitorInfo(hmon, &mi)) return -1;

	// Create a fullscreen window
	hWnd = CreateWindowEx(NULL, wc.lpszClassName, L"Gaming Wizard", WS_POPUP | WS_VISIBLE, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, NULL, NULL, NULL, NULL);
	
	game = new Game();
	thread thread1(&GameThread);
	
	// Begin the message loop
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	thread1.join();
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case FILE_MENU_NEW:
			MessageBox(NULL, L"FILE POPUP", L"File", 0);
			break;
		case ABOUT:
			MessageBox(NULL, L"Version 1.0", L"About", 0);
			break;
		case LOGIN:
			break;
		case TESTING:
			location++;
			game->display->display_NPC("images/Current_Game_Images/testing.bmp", location);
			break;
		case FILE_MENU_EXIT:
			game->stop();
			DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_CREATE:
		LoadImages(DISPLAY_IMAGE);
		//AddMenus(hwnd);
		AddControls(hwnd);
		break;
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;

	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

void AddMenus(HWND hwnd)
{
	HMENU hFileMenu = CreateMenu();
	HMENU hSubNew = CreateMenu();
	hMenu = CreateMenu();

	// Setup Main Menu
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	AppendMenu(hMenu, MF_STRING, NULL, L"Options");
	AppendMenu(hMenu, MF_STRING, ABOUT, L"About");

	// Setup File Menu
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubNew, L"New");
	AppendMenu(hFileMenu, MF_STRING, NULL, L"Open");
	AppendMenu(hFileMenu, MF_STRING, NULL, L"Save");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

	// Setup New Menu
	AppendMenu(hSubNew, MF_STRING, LOGIN, L"Login");

	SetMenu(hwnd, hMenu);
}

void AddControls(HWND hwnd)
{
	hImage = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1080, 716, hwnd, NULL, NULL, NULL);
	SendMessageW(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

	CreateWindowEx(NULL, L"button", L"Exit", WS_VISIBLE | WS_CHILD | WS_BORDER, 1820, 980, 100, 100, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
	CreateWindowEx(NULL, L"button", L"Should be working", WS_VISIBLE | WS_CHILD | WS_BORDER, 1600, 800, 100, 100, hwnd, HMENU(TESTING), NULL, NULL);
}

void DisplayImages(HWND hwnd)
{
	DestroyWindow(hImage);
	hImage = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1080, 716, hwnd, NULL, NULL, NULL);
	SendMessageW(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
}

void LoadImages(string imgPath)
{
	image = (HBITMAP)LoadImageA(NULL, imgPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

}


void GameThread()
{	
	waitKey(1000);
	game->detector->connect();
	while (game->Running()) 
	{
		waitKey(1000);
		if (game->display->update_image)
		{
			LoadImages(DISPLAY_IMAGE);
			SendMessageW(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
			game->display->update_image = false;
		}
		/*
		if (flag)
		{
			game->display->display_NPC("images/Current_Game_Images/testing.bmp", 10);
			flag = false;
			warning = L"made it here";
		}*/		
	}
}