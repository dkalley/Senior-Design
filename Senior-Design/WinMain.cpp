#include "pch.h"
#include "Game.h"
#include "Player.h"

// NameSpaces
using namespace std;
//using namespace Gdiplus;

// Definition
#define FILE_MENU_NEW 1 
#define FILE_MENU_EXIT 2
#define ABOUT 7
#define LOGIN 8
#define TESTING 10
#define UPDATE 11
#define PLAY 12
#define REFRESH 13
#define READY 14
#define PAIR 15
#define DEVICE_SELECTION 16
#define START_UP "images/bmp/wilderness-map-grid.bmp" // Will be a default image in the end

// Function Prototypes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND hwnd);
void CreateGameView(HWND hwnd);
void CreateMainMenu(HWND hwnd);
void DestroyMainMenu();
void CreateConnectWindow(HWND hwnd);
void DestroyConnectWindow();
void GenerateDeviceList(HWND hwnd);
//void LoadImages(string imgPath);
//void DisplayImages(HWND hwnd);
void StartGame();
void scan();

// Global Variables
HMENU hMenu;
HWND hLogin, hPass, hWnd, hImage, title, play_button, quit_button, titlebar, refresh_button, ready_button, nodevices, pair_button, last_button;
vector<HWND> device_buttons;
HBITMAP image;
LPCWSTR warning;
HFONT titleFont;

int location = 0;
Game *game;

// Main
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	// Start the game in its own thread
	game = new Game();
	thread game_thread(&StartGame);

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
	
	// Begin the message loop
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// End the game thread
	game_thread.join();
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	// Event handlers
	case WM_COMMAND:
		switch (wParam)
		{
		// When the play button is pressed load bluetooth menu
		case PLAY:
			DestroyMainMenu();
			CreateConnectWindow(hwnd);
			break;
		// When refresh is pressed, reload bluetooth devices
		case REFRESH:
			DestroyWindow(nodevices);
			GenerateDeviceList(hwnd);
			break;
		// When devices are pressed display map
		/* NEED TO ADD A CHOOSE MAP OPTION BEFORE DISPLAYING THE MAP */
		case READY:
			DestroyConnectWindow();
			CreateGameView(hwnd);
			break;
		case PAIR:
			game->bluetooth->Pair_Device(game->bluetooth->device_list.at(0));
			break;
		case FILE_MENU_NEW:
			MessageBox(NULL, L"FILE POPUP", L"File", 0);
			break;
		case ABOUT:
			MessageBox(NULL, L"Version 1.0", L"About", 0);
			break;
		case LOGIN:
			break;
		case TESTING:
			// For testing purposes
			game->display->NPCS.push_back(Player::Player(1, "images/png/dragon.png"));
			game->display->NPCS.push_back(Player::Player(100, "images/png/dragon.png"));
			game->display->NPCS.push_back(Player::Player(500, "images/png/dragon.png"));
			game->display->display_NPC("images/png/dragon.png", 1, game->display->grid_image);
			game->display->display_NPC("images/png/dragon.png", 100, game->display->grid_image);
			game->display->display_NPC("images/png/dragon.png", 500, game->display->grid_image);
			game->display->LoadImages("images/bmp/wilderness-map-current.bmp", &hImage, &image);
			SendMessageW(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
			break;
		case UPDATE:
			// For testing purposes
			game->display->display_area(3, 100, ATTACK);
			game->display->display_area(5, 500, MOVE);
			SendMessageW(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
			game->display->LoadImages("images/bmp/wilderness-map-current.bmp", &hImage, &image);
			SendMessageW(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
			break;
		// On exit, end the game and destroy the window
		case FILE_MENU_EXIT:
			game->stop();
			DestroyWindow(hwnd);
			break;
		}
		break;
	// On window creation
	case WM_CREATE:
		CreateMainMenu(hwnd);
		game->display->LoadImages(START_UP, &hImage, &image);
		//AddMenus(hwnd);
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

void CreateMainMenu(HWND hwnd)
{
	// Logo
	//CreateWindowEx(NULL, L"button", L"Exit", WS_VISIBLE | WS_CHILD | WS_BORDER, 1820, 980, 100, 100, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
	// Title
	title = CreateWindowEx(NULL, L"static", L"Gaming Wizard", WS_VISIBLE | WS_CHILD | SS_CENTER, 440, 300, 400, 25, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);

	// Play Button
	play_button = CreateWindowEx(NULL, L"button", L"Play", WS_VISIBLE | WS_CHILD | WS_BORDER, 440, 400, 400, 25, hwnd, HMENU(PLAY), NULL, NULL);
	// Quit Button
	quit_button = CreateWindowEx(NULL, L"button", L"Quit", WS_VISIBLE | WS_CHILD | WS_BORDER, 440, 430, 400, 25, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
}

// Clear main menu window
void DestroyMainMenu()
{
	DestroyWindow(title);
	DestroyWindow(play_button);
	DestroyWindow(quit_button);
}

void CreateConnectWindow(HWND hwnd)
{
	// Device Name Indicator
	titlebar = CreateWindowEx(NULL, L"static", L"Device Name", WS_VISIBLE | WS_CHILD | SS_LEFT, 50, 100, 400, 25, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);

	// Refresh button
	refresh_button = CreateWindowEx(NULL, L"button", L"Refresh", WS_VISIBLE | WS_CHILD | WS_BORDER, 1000, 100, 100, 25, hwnd, HMENU(REFRESH), NULL, NULL);
	// Quit Button
	ready_button = CreateWindowEx(NULL, L"button", L"Ready", WS_VISIBLE | WS_CHILD | WS_BORDER, 1180, 695, 100, 25, hwnd, HMENU(READY), NULL, NULL);
	// Look for and display devices in bluetooth range
	GenerateDeviceList(hwnd);
}

void DestroyConnectWindow()
{
	DestroyWindow(titlebar);
	DestroyWindow(refresh_button);
	DestroyWindow(ready_button);
	DestroyWindow(pair_button);
	if(nodevices) 
		DestroyWindow(nodevices);
	while (!device_buttons.empty())
	{
		DestroyWindow(device_buttons.back());
		device_buttons.pop_back();
	}
}

void GenerateDeviceList(HWND hwnd)
{
	// Scan for devices
	thread scan(&scan);

	HWND scanloading = CreateWindowEx(NULL, L"static", L"Scanning...", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 540, 335, 200, 50, hwnd, NULL, NULL, NULL);
	
	// While the game is scanning for devices display a scanning window
	while (game->bluetooth->scanning_status == SCANNING_STARTED)
	{
		waitKey(10); // Reduce CPU load
	}

	// After all devices have been found, destroy scanning window and display devices
	DestroyWindow(scanloading);

	int length = 0, y = 130;
	if (game->bluetooth->device_list.empty())
	{
		nodevices = CreateWindowEx(NULL, L"static", L"No devices found. Enable Bluetooth on your device and refresh.", WS_VISIBLE | WS_CHILD | SS_LEFT, 50, 130, 500, 25, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);

	}
	else
	{
		pair_button = CreateWindowExA(NULL, "button", "Pair", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 875, 100, 100, 25, hwnd, HMENU(PAIR), NULL, NULL);
		for (BLUETOOTH_DEVICE_INFO device : game->bluetooth->device_list)
		{
			wstring device_name = device.szName;
			device_buttons.insert(device_buttons.begin(), CreateWindowExA(NULL, "button", string(device_name.begin(), device_name.end()).c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT | BS_PUSHBUTTON, 50, y, 400, 25, hwnd, HMENU(PAIR), NULL, NULL));
			y = y + 30;
			length++;
		}
	}
	scan.join();
}

void scan()
{
	game->bluetooth->scanDevices();
}

// A top file menu if needed
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

// Create the map screen
void CreateGameView(HWND hwnd)
{
	hImage = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	SendMessageW(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

	CreateWindowEx(NULL, L"button", L"Exit", WS_VISIBLE | WS_CHILD | WS_BORDER, 1820, 980, 100, 100, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
	CreateWindowEx(NULL, L"button", L"Move NPC", WS_VISIBLE | WS_CHILD | WS_BORDER, 1620, 980, 100, 100, hwnd, HMENU(TESTING), NULL, NULL);
	CreateWindowEx(NULL, L"button", L"Display New", WS_VISIBLE | WS_CHILD | WS_BORDER, 1720, 980, 100, 100, hwnd, HMENU(UPDATE), NULL, NULL);
}


void StartGame()
{
	ofstream myfile;
	int last = -1;
	myfile.open("example.txt");
	myfile.close();
	return;
}

