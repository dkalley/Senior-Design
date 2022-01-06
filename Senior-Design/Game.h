#pragma once
#include "pch.h"
#include "Display.h"
#include "ObjectDetector.h"
#include "Bluetooth.h"
#include "Player.h"
#include <ctime>
#include <mutex>
#include "ProcessPoint.h"
#include "Serial.h"
#include "MyListener.h"

#define MAX_PLAYERS 5
#define RETURN 4
#define FILE_MENU_EXIT 2

#define REQUESTALLPLAYERS 30
#define CREATENEWPLAYER 31
#define UPDATEPLAYER 32
#define MOVECHARACTER 33
#define MOVEXY 34
#define ATTACK_JSON 35
#define REQUESTGM 36
#define ENDTURN 37
#define TURNORDER 38
#define SAVEGAME 39
#define ENCOUNTERSELECTED 40

#define NONE 20
#define WAIT_ATTACK 21
#define WAIT_MOVE 22
#define WAIT_PLACEMENT 23

#define COMPLETED 500
#define NOTCOMPLETED 501

#define GAMEDATAPATH "\\Gaming Wizard\\Game Data\\"
#define GAMESOUNDS "Game Sounds\\"
#define GAMELOGSPATH "\\Gaming Wizard\\Game Logs\\"
#define GAMEIMAGEPATH "\\Gaming Wizard\\Game Images\\"
#define UIIMAGES "UI Images\\"
#define NPCIMAGES "NPC Images\\"
#define MAPIMAGES "Map Images\\"
#define MAPS "Maps\\"
#define CURRENTIMAGES "Current Images\\"
#define PREVIEWIMAGES "Preview Images\\"
#define SAVEINFONEWTITLE "SaveInfoNew.info"
#define SAVEINFOOLDTITLE "SaveInfo.info"
#define CONFIG "config.config"
#define CONFIGNEW "confignew.config"
#define MAXFILEPATHLENGTH 260

#define LOADING 10000
#define NOTLOADING 10001

#define NEXT_PAGE 55
#define PREV_PAGE 56
#define NEXT_PAGE_DEL 60
#define PREV_PAGE_DEL 61
#define DELETE_GAME_BUTTONS 62 // - 66


class Game
{
public:
	std::mutex mtx;

	std::string APPDATAPATH;
	std::string CURRENTGAMEPATH;
	std::string SAVESINFOOLD;
	std::string SAVESINFONEW;
	std::string PATHTOMAPIMAGES;
	std::string PATHTOCONFIG;
	std::string PATHTOCONFIGNEW;

	std::string GameName;
	std::string LastSaved;
	std::string NumberOfPlayers;
	std::string CurrentEncounter;
	std::string CurrentMap;

	HANDLE hSerial;
	bool LightsLoaded;

	TuioClient *client;

	std::vector<json> LoadedPlayers;
	int Mode, mode;
	BOOL SERVER, CLIENT, RUN, PAUSE, PAUSED, SAVE, EXIT, RETURNFLAG, FROMGM, LOADED;
	Game(HWND *hwnd, HBITMAP *image, HWND *hImage);
	Display *display;
	ObjectDetector *detector;
	Bluetooth *bluetooth;

	// Players and NPCs
	Player *players[MAX_PLAYERS];
	Player *GM_Player;
	std::vector<Player*> NPCs;
	json GMInfo;
	json EmptyGMInfo;
	json SelectedEncounter;
	json TurnOrder;

	int Player_Count;
	Action_Struct last_action;
	json last_attack;
	int CURRENT_ACTION;
	void TESTINGCHARS();
	void UpdateGMInfo(json updateNPC);
	//void Bluetooth_init(Bluetooth *bth);
	void ObjectDetection(ObjectDetector *listener);
	void GameMain();
	void stop();
	void Bluetooth_Start_Up();
	void Message_Handler(char *message, int index);
	void Message_Responder(int Response,int index, json message);
	json Get_All_Players();
	int HandleLastAction(LONG ptx, LONG pty);

	void Process_Point(LONG ptx, LONG pty);

	void Load_Game(std::string LoadGameName);
	void Save_Game();
	void Update_Saves_File();
	void Set_Map_Name(std::string preparemap);
	void autosave();
	void SaveGameInitiate();
	void SetGameName();
	void UpdateTurnOrder(json message);
	void UpdateActiveNPC(json message);
	void UpdateActiveNPCXY(json message);
	void ResetGame();
	void CreateActiveNPCs();
	void ClearEncounter();
	std::string GetFileName(std::string name);

	// Process point functions


private:
	HWND *hwnd, *hImage;
	HBITMAP *image;

	void asynccontrolserver(std::future<void> futureObj);
	BOOL VerifyLocation(int index, int x, int y, std::string bth_id, std::string unique_id);

};

