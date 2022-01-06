#include "pch.h"
#include "Game.h"

char JSONSTRING2[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 3, 5, Bludgeoning, 6, false, str\"],\"bluetooth_id\":\"817b8dac-6a42-82a9-a782-98276f8c7951\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8801\",\"wis_proficiency\":false}";
char JSONSTRING3[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 3, 5, Bludgeoning, 6, false, str\"],\"bluetooth_id\":\"817b8dac-6a42-82a9-a782-98276f8c7952\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8802\",\"wis_proficiency\":false}";
char JSONSTRING4[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 3, 5, Bludgeoning, 6, false, str\"],\"bluetooth_id\":\"817b8dac-6a42-82a9-a782-98276f8c7953\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8803\",\"wis_proficiency\":false}";
char JSONSTRING5[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 3, 5, Bludgeoning, 6, false, str\"],\"bluetooth_id\":\"817b8dac-6a42-82a9-a782-98276f8c7954\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8804\",\"wis_proficiency\":false}";

// When the game is created, create instances of all necessay objects
Game::Game(HWND *hwnd, HBITMAP *image, HWND *hImage)
{	
	memset(&last_action, 0, sizeof(Action_Struct));
	last_action.mode = -1;

	size_t outsize;
	char pathbuffer[MAXFILEPATHLENGTH];
	getenv_s(&outsize, pathbuffer, MAXFILEPATHLENGTH, "appdata");
	APPDATAPATH = std::string(pathbuffer);
	SAVESINFOOLD = APPDATAPATH + GAMEDATAPATH + SAVEINFOOLDTITLE;
	SAVESINFONEW = APPDATAPATH + GAMEDATAPATH + SAVEINFONEWTITLE;
	PATHTOCONFIG = APPDATAPATH + GAMEDATAPATH + CONFIG;
	PATHTOCONFIGNEW = APPDATAPATH + GAMEDATAPATH + CONFIGNEW;
	PATHTOMAPIMAGES = APPDATAPATH + GAMEIMAGEPATH + MAPIMAGES; // ...\\Gaming Wizard\\Game Images\\Map Images\\ 

	std::ofstream myfile;
	myfile.open(APPDATAPATH + GAMEDATAPATH + "logs.txt", std::ofstream::app);
	myfile << "New Session!" << std::endl;
	myfile.close();

	this->hwnd = hwnd;
	this->hImage = hImage;
	this->image = image;

	display = new Display(hwnd, image, hImage);
	bluetooth = new Bluetooth();

	display->PATHTONPC = APPDATAPATH + GAMEIMAGEPATH + NPCIMAGES;
	display->PATHTOBAD = APPDATAPATH + GAMEIMAGEPATH + UIIMAGES + "bad.bmp";
	display->PATHTOGOOD = APPDATAPATH + GAMEIMAGEPATH + UIIMAGES + "good.bmp";

	RUN = true;
	mode = NOTLOADING;
	Mode = MAIN_MENU;
	SERVER = false;
	CLIENT = false;
	PAUSE = false;
	PAUSED = false;
	SAVE = false;
	EXIT = false;
	RETURNFLAG = false;
	FROMGM = false;
	//LOADED = false;
	Player_Count = 0;
	for (int i = 0; i < MAX_PLAYERS; i++)
		players[i] = nullptr;

	CurrentMap = "None Selected";
	SelectedEncounter["encounter_name"] = "No Selected Encounter";
	GMInfo = nullptr;
	EmptyGMInfo = json::parse("{\"action\":\"GMInfo\",\"bluetooth_id\":\"\",\"encounter_selected\":{\"encounter_name\":\"No Selected Encounter\",\"npcs_in_encounter\":[]},\"encounters_list\":[],\"info_tab_gm\":[\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"maps_list\":[],\"npcs_list\":[],\"players_list\":[],\"round_number\":0,\"turn_number\":0}");
	TurnOrder = json::parse("{\"action\":\"Update Turn Order\",\"turnOrderCharacters\":[]}");

	hSerial = OpenSerial();
	if (hSerial != NULL)
		LightsLoaded = true;
}	

void Game::TESTINGCHARS()
{
	// For testing create 4 players
	players[1] = new Player(1);
	players[2] = new Player(2);
	players[3] = new Player(3);
	players[4] = new Player(4);

	bluetooth->SocketsActive[1] = true;
	bluetooth->SocketsActive[2] = true;
	bluetooth->SocketsActive[3] = true;
	bluetooth->SocketsActive[4] = true;

	Message_Handler(JSONSTRING2, 1);
	Message_Handler(JSONSTRING3, 2);
	Message_Handler(JSONSTRING4, 3);
	Message_Handler(JSONSTRING5, 4);
}

void Game::ObjectDetection(ObjectDetector *listener)
{
	while (RUN)
	{
		if (!client->isConnected())
		{
			int oldmode = Mode;
			Mode = POP_UP;
			MessageBoxA(NULL, "Touch Not Connected. Please Restart the Game!", NULL, 0);
			Mode = oldmode;
			break;
		}

		if (listener->ToProcess.size() > 0)
		{
			// Grab most recent object
			CCVObject object_to_process = listener->ToProcess.front();
			// Remove the object from the list
			Process_Point(object_to_process.ptx, object_to_process.pty);
			listener->ToProcess.pop_front();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	client->disconnect();
}

void Game::GameMain()
{	
	std::thread bth(&Game::Bluetooth_Start_Up, this);
	std::thread autosave(&Game::autosave, this);
	//std::thread obj(&Game::ObjectDetection, this);
	
	char *buffer = NULL;
	BOOL updated_name = false;
	while (RUN)
	{
		for (int i = 0; i < MAX_CONNECTIONS; i++)
		{
			if (bluetooth->ReceiveBufferFlag[i] > -1)
			{
				wchar_t wbuffer[BUFFER_SIZE] = { 0 };
				wchar_t wrec[BUFFER_SIZE] = { 0 };
				memset(wbuffer, 0, BUFFER_SIZE);
				memset(wrec, 0, BUFFER_SIZE);

				// Read in Mailbox a
				buffer = bluetooth->GetReceiveBuffer(i, buffer);
				Message_Handler(buffer, i);

				delete[] buffer;
			}
		}
	}
	
	bth.join();
	autosave.join();
	//obj.join();
}


// Game ending protocol
void Game::stop()
{
	// Revert the current image to the base image, let main process know game is over
	//display->revert_image();
	display->CleanCurrentFolder(CurrentMap, APPDATAPATH + GAMEIMAGEPATH + MAPIMAGES + CURRENTIMAGES);
	RUN = false;
	bluetooth->ServerPromise.set_value();
}

void Game::Bluetooth_Start_Up()
{
	// Initialize Winsock
	bluetooth->Winsock_Startup();

	// Create server socket and make it non-blocking
	bluetooth->Create_Socket(&bluetooth->SocketsArray[SERVER_INDEX]);
	bluetooth->Make_Non_Blocking(&bluetooth->SocketsArray[SERVER_INDEX]);

	// Bind server socket 
	bluetooth->Bind_Socket(&bluetooth->SocketsArray[SERVER_INDEX]);

	// Listen on server socket for upto 5 devices
	bluetooth->Setup_Listen(&bluetooth->SocketsArray[SERVER_INDEX]);

	// Sets service with a GUID
	bluetooth->Broadcast_GUID();

	// Initialize thread indicator and begin loop to scan for devices
	std::future<void> futureObj = bluetooth->ServerPromise.get_future();
	asynccontrolserver(std::move(futureObj));

	// Close the sockets and then the threads
	bluetooth->Close_All_Sockets();
	bluetooth->Close_All_Threads();
}

// Should only have one instance of this for the server
// Looks for accept and close calls asynchronous
void Game::asynccontrolserver(std::future<void> futureObj)
{
	DWORD Event;
	WSANETWORKEVENTS NetworkEvents;

	bluetooth->Winsock_Startup();

	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (bluetooth->CloseThreads[i])
			{
				bluetooth->PromiseArray[i].set_value();
				bluetooth->ThreadArray[i].join();
				bluetooth->CloseThreads[i] = false;
			}
		}

		//// Check the connections
		//for (int i = 0; i < MAX_PLAYERS; i++)
		//{
		//	SOCKADDR_BTH ca;
		//	int sa_len = sizeof(ca);
		//	if (bluetooth->SocketsActive[i])
		//	{
		//		char data;
		//		int result = recv(bluetooth->SocketsArray[i], &data, 1, MSG_PEEK);
		//		if (result == 0)
		//		{
		//			bluetooth->SocketsActive[i] = false;
		//		}
		//	}
		//}

		// Wait for one of the sockets to receive I/O notification and
		if ((Event = WSAWaitForMultipleEvents(1, &bluetooth->EventArray[SERVER_INDEX], FALSE, 2, FALSE)) == WSA_WAIT_FAILED)
		{
			return;
		}

		if (WSAEnumNetworkEvents(bluetooth->SocketsArray[SERVER_INDEX], bluetooth->EventArray[SERVER_INDEX], &NetworkEvents) == SOCKET_ERROR)
		{
			return;
		}

		if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
		{
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
			{
				break;
			}
			// Accept was unsuccessful, log error
			int realindex = bluetooth->Accept_Connections(players, &bluetooth->SocketsArray[SERVER_INDEX]);
			if (realindex == -1)
			{
				break;
			}
			// Accept was succesful, create a player
			else
			{
				// If the player doesn't exist, create a new player
				if (players[realindex - 1] == nullptr)
				{
					SOCKADDR_BTH device;
					bluetooth->Get_Socket_Info(bluetooth->SocketsArray[CLIENT_START_INDEX + bluetooth->TOTALCONNECTIONS - 1], &device);
					players[realindex - 1] = new Player(device, realindex - 1);
					players[realindex - 1]->alive = true;
				}
				// The player does exist, and its SocketIndex is -1, 
				// then its SocketIndex needs to be set
				else if(players[realindex - 1]->get_index() == -1)
				{
					players[realindex - 1]->set_index(realindex - 1);
				}
				// Else, its the same game session and no action is required
			}

			if (bluetooth->EventTotal > WSA_MAXIMUM_WAIT_EVENTS)
			{
				break;
			}
		}

		if (NetworkEvents.lNetworkEvents & FD_CLOSE)
		{
			if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
			{
				break;
			}
			bluetooth->Close_Socket(bluetooth->SocketsArray[SERVER_INDEX]);
		}
	}
}

void Game::ClearEncounter()
{
	if(last_action.mode != -1)
		display->remove_area(&last_action);

	// Cleans map of NPC
	for (ActiveNPC npc : display->activeNPCs)
	{
		display->Remove_Spot(npc.x, npc.y);
		display->occupied[npc.y*display->X_PHY_LENGTH + npc.x] = false;
	}

	DeleteObject(*image);
	*image = (HBITMAP)LoadImageA(NULL, (display->PATHTOGRID).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);

	// Clears ActiveNPCs
	while (!(display->activeNPCs.empty()))
		display->activeNPCs.pop_back();
}

void Game::Message_Handler(char *message, int index)
{
	// If its not a json dont process
	if (message[0] != '{')
		return;

	// Turn message into json
	json jsonmessage = json::parse(message);
	json encounternpcs;
	
	// Grab action and use it to be the key of a case statement
	std::string RequestAllPlayers = "Request All Characters";
	std::string CreateNewPlayer = "Create New Player";
	std::string UpdatePlayer = "Update Character";
	std::string MoveCharacter = "Move Character";
	std::string UpdateCharacterXY = "Update Character XY";
	std::string MoveXY = "MoveXY";
	std::string Attack = "attack";
	std::string CharacterBeenAttacked = "Character has been attacked";
	std::string CharacterEndTurn = "Character End Turn";
	std::string GMEndTurn = "GM End Character Turn";
	std::string RequestGMInfo = "Request GM Information";
	std::string UpdateGM = "Update GM";
	std::string UpdateTurnOrder = "Update Turn Order";
	std::string encounterSelected = "Encounter Selected";
	std::string saveGameGM = "Save Game GM";
	std::string gmSelected = "GM selected";

	std::ofstream myfile;
	myfile.open(APPDATAPATH + GAMEDATAPATH + "logs.txt", std::ofstream::app);
	myfile << "Inbound Message: " << jsonmessage.dump() << std::endl;

	if (jsonmessage["action"].get<std::string>().compare(gmSelected) == 0)
	{
		GMInfo = jsonmessage;
		SelectedEncounter = GMInfo["encounter_selected"].get<json>();
	}

	// Save GM
	if (jsonmessage["action"].get<std::string>().compare(saveGameGM) == 0)
	{
		GM_Player->saved = true;
		GMInfo = jsonmessage;
	}

	// New Encounter
	if (jsonmessage["action"].get<std::string>().compare(encounterSelected) == 0)
	{
		ClearEncounter();

		GMInfo = jsonmessage;
		SelectedEncounter = GMInfo["encounter_selected"].get<json>();
	}

	// Send all players
	if (jsonmessage["action"].get<std::string>().compare(RequestAllPlayers) == 0)
	{
		Message_Responder(REQUESTALLPLAYERS, index, jsonmessage);
	}

	// Create stats
	if (jsonmessage["action"].get<std::string>().compare(CreateNewPlayer) == 0)
	{
		if (players[index]->Create_Player(jsonmessage) == WRONG_DEVICE)
		{
			// Handle the wrong device error
		}
		else Message_Responder(CREATENEWPLAYER, index, jsonmessage);
		Message_Responder(REQUESTALLPLAYERS, index, jsonmessage);
	}	

	// Update stats
	if (jsonmessage["action"].get<std::string>().compare(UpdatePlayer) == 0)
	{
		if (players[index]->initiatesave)
			players[index]->saved = true;

		if (players[index]->Update_Player(jsonmessage) == WRONG_DEVICE)
		{
			// Handle the wrong device error
		}
		else Message_Responder(UPDATEPLAYER, index, jsonmessage);
		Message_Responder(REQUESTALLPLAYERS, index, jsonmessage);
	}	
	
	// Movement turn
	if (jsonmessage["action"].get<std::string>().compare(MoveCharacter) == 0)
	{
		if (last_action.mode == MOVE)
			return;

		if (last_action.mode != -1)
		{
			display->remove_area(&last_action);
			display->ShowActiveNPCs(APPDATAPATH + GAMEDATAPATH + "logs.txt");
		}

		Action_Struct action;
		memset(&action, 0, sizeof(Action_Struct));
		action.x = -1;
		action.y = -1;
		action.speed = jsonmessage["speed"].get<int>();
		action.bth_id = jsonmessage["bluetooth_id"].get<std::string>();
		action.unique_id = jsonmessage["unique_character_id"].get<std::string>();
		action.mode = MOVE;

		// If GM, find NPC
		if (players[index]->is_GM())
		{
			encounternpcs = SelectedEncounter["npcs_in_encounter"].get<std::vector<json>>();
			//encounternpcs = TurnOrder["turnOrderCharacters"].get<std::vector<json>>();
			for (json npc : encounternpcs)
			{
				if (npc["unique_character_id"].get<std::string>().compare(action.unique_id) == 0)
				{
					action.x = npc["character_x_coordinate"].get<int>();
					action.y = npc["character_y_coordinate"].get<int>();

					if (action.x == -1 || action.y == -1)
						return;

					break;
				}
			}
		}
		// Else its the player
		else
		{
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				if (bluetooth->SocketsActive[i])
				{
					if (players[i]->is_GM())
						continue;
					if (players[i]->playerattributes["unique_character_id"].get<std::string>().compare(action.unique_id) == 0) 
					{
						action.x = players[i]->playerattributes["character_x_coordinate"].get<int>();
						action.y = players[i]->playerattributes["character_y_coordinate"].get<int>();

						if (action.x == -1 || action.y == -1)
							return;

						break;
					}
				}
			}
		}

		// No player found dont show area
		if (action.x == -1 || action.y == -1)
			return;

		// Display movement area based on X,Y and speed
		display->display_area(action);
		last_action = action;

		DeleteObject(*image);
		*image = (HBITMAP)LoadImageA(NULL, (display->PATHTOGRID).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);

		
		// Wait for physical movement (Player), or finger touch (NPC)
		CURRENT_ACTION = WAIT_MOVE;
	}	
	
	// Place new character
	if (jsonmessage["action"].get<std::string>().compare(MoveXY) == 0)
	{
		if (jsonmessage["character_x_coordinate"].get<int>() != -1 || jsonmessage["character_y_coordinate"].get<int>() != -1)
			return;

		// Build last action 
		Action_Struct action;
		action.x = jsonmessage["character_x_coordinate"].get<int>();
		action.y = jsonmessage["character_y_coordinate"].get<int>();
		action.bth_id = jsonmessage["bluetooth_id"].get<std::string>();
		action.unique_id = jsonmessage["unique_character_id"].get<std::string>();
		action.playertype = jsonmessage["character"].get<std::string>();

		action.mode = MOVEXY_MODE;

		// Save the last action
		last_action = action;

		// Put up wait for placement flag and send message back in message responder
		CURRENT_ACTION = WAIT_PLACEMENT;
	}
		
	// Attack
	if (jsonmessage["action"].get<std::string>().compare(Attack) == 0)
	{
		if (last_action.mode == ATTACK)
			return;
		
		if (last_action.mode != -1)
		{
			display->remove_area(&last_action);
			display->ShowActiveNPCs(APPDATAPATH + GAMEDATAPATH + "logs.txt");
		}

		// Create a struct for the action being done
		Action_Struct action;
		memset(&action, 0, sizeof(Action_Struct));
		action.damage_roll = jsonmessage["damage_roll"].get<int>();
		action.damage_type = jsonmessage["damage_type"].get<std::string>();
		action.range = jsonmessage["range"].get<int>();
		action.bth_id = jsonmessage["bluetooth_id"].get<std::string>();
		action.unique_id = jsonmessage["unique_character_id"].get<std::string>();
		action.mode = ATTACK;
		last_attack = jsonmessage;

		// If GM, find NPC
		if (players[index]->is_GM())
		{
			encounternpcs = SelectedEncounter["npcs_in_encounter"].get<std::vector<json>>();
			//encounternpcs = TurnOrder["turnOrderCharacters"].get<std::vector<json>>();
			for (json npc : encounternpcs)
			{
				if (npc["unique_character_id"].get<std::string>().compare(action.unique_id) == 0)
				{
					action.x = npc["character_x_coordinate"].get<int>();
					action.y = npc["character_y_coordinate"].get<int>();

					if (action.x == -1 || action.y == -1)
						return;

					break;
				}
			}
		}
		// Else its the player
		else
		{
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				if (bluetooth->SocketsActive[i])
				{
					if (players[i]->is_GM())
						continue;

					if (players[i]->playerattributes["unique_character_id"].get<std::string>().compare(action.unique_id) == 0)
					{
						action.x = players[i]->playerattributes["character_x_coordinate"].get<int>();
						action.y = players[i]->playerattributes["character_y_coordinate"].get<int>();

						if (action.x == -1 || action.y == -1)
							return;

						break;
					}
				}
			}
		}

		// Display movement area based on X,Y and speed
		display->display_area(action);

		DeleteObject(*image);
		*image = (HBITMAP)LoadImageA(NULL, (display->PATHTOGRID).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);
		
		// Save the last action
		last_action = action;

		CURRENT_ACTION = WAIT_ATTACK;
	}		

	if(jsonmessage["action"].get<std::string>().compare(RequestGMInfo) == 0)
		Message_Responder(REQUESTGM, index, jsonmessage);

	if(jsonmessage["action"].get<std::string>().compare(UpdateGM) == 0)
	{
		GMInfo = jsonmessage;
		SelectedEncounter = jsonmessage["encounter_selected"].get<json>();
		players[index]->playerattributes["bluetooth_id"] = jsonmessage["bluetooth_id"].get<std::string>();
		SAVE = true;
		FROMGM = true;
	}

	if (jsonmessage["action"].get<std::string>().compare(UpdateTurnOrder) == 0)
	{
		std::vector<json> turnorder = jsonmessage["turnOrderCharacters"].get<std::vector<json>>();
		
		if (last_action.mode != -1)
		{
			display->remove_area(&last_action);
			memset(&last_action, 0, sizeof(Action_Struct));
			last_action.mode = -1;
			CURRENT_ACTION = NONE;
		}

		// Save Turn Order
		TurnOrder = jsonmessage;
		UpdateActiveNPC(TurnOrder);
		display->ShowActiveNPCs(APPDATAPATH + GAMEDATAPATH + "logs.txt");

		DeleteObject(*image);
		*image = (HBITMAP)LoadImageA(NULL, (display->PATHTOGRID).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);

		// Send everyone reponse
		Message_Responder(TURNORDER, -1, jsonmessage);
	}

	if (jsonmessage["action"].get<std::string>().compare(CharacterEndTurn) == 0)
	{
		if (last_action.mode != -1)
		{
			display->remove_area(&last_action);
			memset(&last_action, 0, sizeof(Action_Struct));
			last_action.mode = -1;
			CURRENT_ACTION = NONE;

			DeleteObject(*image);
			*image = (HBITMAP)LoadImageA(NULL, (display->PATHTOGRID).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);
		}

		Message_Responder(ENDTURN, GM_Player->get_index(), jsonmessage);
	}

	if (myfile.is_open())
		myfile.close();
}

void Game::Message_Responder(int Response,int index, json message)
{
	json response;
	std::vector<json> encounternpcs, playerorder;
	std::string jsonstringfy;
	char sendbuffer[BUFFER_SIZE];
	int realindex;
	std::ofstream myfile;

	switch (Response)
	{
	case(SAVEGAME):
		response["action"] = "Save Game";

		// Stringfy response
		jsonstringfy = response.dump();

		// Send to everyone
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			// Fill send buffer for correct index and raise send flag
			strcpy(bluetooth->SendBuffer[i], jsonstringfy.c_str());
			bluetooth->SendBufferFlag[i] = true;
		}

		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Outbound Message: " << jsonstringfy << std::endl;
		break;
	case(TURNORDER):
		// Set action
		response["action"] = "Turn Order Has Changed";
		response["unique_character_id"] = "";

		// Find the players unique id
		playerorder = message["turnOrderCharacters"].get<std::vector<json>>();
		for (json item : playerorder)
		{
			if (item["turn"].get<bool>())
			{
				response["unique_character_id"] = item["unique_character_id"];
				break;
			}
		}

		// Stringfy response
		jsonstringfy = response.dump();
		
		// Send to everyone
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			// Fill send buffer for correct index and raise send flag
			strcpy(bluetooth->SendBuffer[i], jsonstringfy.c_str());
			bluetooth->SendBufferFlag[i] = true;
		}

		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Outbound Message: " << jsonstringfy << std::endl;
		break;
	case(ENDTURN):
		response["action"] = "GM End Character Turn";
		response["bluetooth_id"] = message["bluetooth_id"];
		response["unique_character_id"] = message["unique_character_id"];

		// Stringfy response
		jsonstringfy = response.dump();

		// Fill send buffer for correct index and raise send flag
		strcpy(bluetooth->SendBuffer[index], jsonstringfy.c_str());
		bluetooth->SendBufferFlag[index] = true;

		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Outbound Message: " << jsonstringfy << std::endl;
		break;
	case(REQUESTGM):

		if (GMInfo != nullptr)
			response = GMInfo;
		else
			response = EmptyGMInfo;

		response["action"] = "GMInfo";
		jsonstringfy = response.dump();

		// Fill send buffer for correct index and raise send flag
		strcpy(bluetooth->SendBuffer[index], jsonstringfy.c_str());
		bluetooth->SendBufferFlag[index] = true;

		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Outbound Message: " << jsonstringfy << std::endl;
		break;
	case(REQUESTALLPLAYERS):	/*{"action":"Request All Characters"}*/
		// Create json response
		response["action"] = "Player List";
		response["players"] = Get_All_Players();

		// Stringfy response
		jsonstringfy = response.dump();

		// Fill send buffer for correct index and raise send flag
		strcpy(bluetooth->SendBuffer[index], jsonstringfy.c_str());
		bluetooth->SendBufferFlag[index] = true;

		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Outbound Message: " << jsonstringfy << std::endl;
		break;
	case(CREATENEWPLAYER):		// NO RESPONSE REQUIRED
		break;
	case(UPDATEPLAYER):			// NO RESPONSE REQUIRED
		break;
		// Only for actual players
	case(MOVECHARACTER):		/*{"action":"Update Character XY","character_x_coordinate" : 8.5,"character_y_coordinate" : 38.5,"bluetooth_id" : "709bfaef-8ae2-438f-863d-cb61be639ba3","unique_character_id" : "ddfc8c0c-2771-4eeb-9cfe-d85886c4d369"}*/
		// Find the chracter and trigger the display distance
		// Wait for the player piece to move, then respond with updated XY
		// Create Json object
		response["action"] = "Update Character XY";

		if (!players[index]->is_GM())
		{
			try 
			{
				response["character_x_coordinate"] = players[index]->playerattributes["character_x_coordinate"].get<int>();
				response["character_y_coordinate"] = players[index]->playerattributes["character_y_coordinate"].get<int>();
				response["bluetooth_id"] = players[index]->playerattributes["bluetooth_id"].get<std::string>();
				response["unique_character_id"] = players[index]->playerattributes["unique_character_id"].get<std::string>();
			}
			catch (json::exception e)
			{
				MessageBoxA(NULL, e.what(), NULL, 0);
			}
		}
		else
		{
			try
			{
				response["character_x_coordinate"] = message["character_x_coordinate"];
				response["character_y_coordinate"] = message["character_y_coordinate"];
				response["bluetooth_id"] = GMInfo["bluetooth_id"].get<std::string>();
				response["unique_character_id"] = message["unique_character_id"];
			}
			catch (json::exception e)
			{
				MessageBoxA(NULL, e.what(), NULL, 0);
			}
		}

		// Stringfy
		jsonstringfy = response.dump();

		// Fill send buffer for correct index and raise send flag
		strcpy(bluetooth->SendBuffer[index], jsonstringfy.c_str());
		bluetooth->SendBufferFlag[index] = true;

		// Send to GM once
		if (GM_Player->get_index() != index)
		{
			strcpy(bluetooth->SendBuffer[GM_Player->get_index()], jsonstringfy.c_str());
			bluetooth->SendBufferFlag[GM_Player->get_index()] = true;
		}

		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Outbound Message: " << jsonstringfy << std::endl;
		break;
	case(MOVEXY):
		response["action"] = "Update Character XY";

		if (players[index]->is_GM())
		{
			try
			{
				encounternpcs = SelectedEncounter["npcs_in_encounter"].get<std::vector<json>>();
			}
			catch (json::exception e)
			{
				MessageBoxA(NULL, SelectedEncounter.dump().c_str(), NULL, 0);
				MessageBoxA(NULL, e.what(), NULL, 0);
			}
			for (json npc : encounternpcs)
				if (npc["unique_character_id"].get<std::string>().compare(message["unique_character_id"].get<std::string>()) == 0)
				{
					response["character_x_coordinate"] = npc["character_x_coordinate"].get<int>();
					response["character_y_coordinate"] = npc["character_y_coordinate"].get<int>();
					response["bluetooth_id"] = GMInfo["bluetooth_id"].get<std::string>();
					response["unique_character_id"] = npc["unique_character_id"].get<std::string>();
					break;
				}
		}
		else
		{
			response["character_x_coordinate"] = players[index]->playerattributes["character_x_coordinate"].get<int>();
			response["character_y_coordinate"] = players[index]->playerattributes["character_y_coordinate"].get<int>();
			response["bluetooth_id"] = players[index]->playerattributes["bluetooth_id"].get<std::string>();
			response["unique_character_id"] = players[index]->playerattributes["unique_character_id"].get<std::string>();
		}

		// Stringfy
		jsonstringfy = response.dump();

		// Fill send buffer for correct index and raise send flag
		strcpy(bluetooth->SendBuffer[index], jsonstringfy.c_str());
		bluetooth->SendBufferFlag[index] = true;
		
		// Send to GM once
		if (GM_Player->get_index() != index)
		{
			strcpy(bluetooth->SendBuffer[GM_Player->get_index()], jsonstringfy.c_str());
			bluetooth->SendBufferFlag[GM_Player->get_index()] = true;
		}

		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Outbound Message: " << jsonstringfy << std::endl;
		break;
	case(ATTACK_JSON):
		response["action"] = "Character has been attacked";
		response["damage_roll"] = last_action.damage_roll;

		if (index != -1)
		{
			response["bluetooth_id"] = players[index]->playerattributes["bluetooth_id"].get<std::string>();
			response["unique_character_id"] = players[index]->playerattributes["unique_character_id"].get<std::string>();
			realindex = index;
		}
		else
		{
			response["bluetooth_id"] = GMInfo["bluetooth_id"].get<std::string>();
			response["unique_character_id"] = message["unique_character_id"].get<std::string>(); // ["unique_character_id"];
			realindex = GM_Player->get_index();
		}

		// Stringfy
		jsonstringfy = response.dump();

		// Fill send buffer for correct index and raise send flag
		strcpy(bluetooth->SendBuffer[realindex], jsonstringfy.c_str());
		bluetooth->SendBufferFlag[realindex] = true;

		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Outbound Message: " << jsonstringfy << std::endl;
		break;
	}
	if(myfile.is_open())
		myfile.close();
}

json Game::Get_All_Players()
{
	std::vector<json> array_players;
	if (mode == LOADING)
	{
		for (int i = 0; i < LoadedPlayers.size(); i++)
			array_players.push_back(LoadedPlayers[i]);
	}
	else
	{
		for (int i = 0; i < MAX_CONNECTIONS; i++)
		{
			if (bluetooth->SocketsActive[i])
			{
				json attributes = Player::Dump_Player_Attributes(players[i]);
				try
				{
					//std::string temp = attributes["action"].get<std::string>();
					if(attributes != nullptr)
						array_players.push_back(attributes);
				}
				catch (json::exception e)
				{
					// It shouldnt add
				}
			}
		}
	}
	json j_vec(array_players);

	return j_vec;
}

void Game::Process_Point(LONG ptx, LONG pty)
{
	int grid_space, complete;
	switch (Mode)
	{
	case MAIN_MENU:
		DetermineMainMenuFunction(ptx, pty, hwnd);
		break;
	case BTH_CONNECT:
		DeterminePairFunction(ptx, pty, hwnd);
		break;
	case GM_SELECT:
		DetermineGMSelectFunction(ptx, pty, hwnd);
		break;
	case GAME_VIEW:
		switch (CURRENT_ACTION)
		{
		case(NONE):
			// Do nothing
			break;
		case(WAIT_ATTACK):
			complete = HandleLastAction(ptx, pty);
			if (complete == COMPLETED) CURRENT_ACTION = NONE;
			break;
		case(WAIT_MOVE):
			complete = HandleLastAction(ptx, pty);
			if (complete == COMPLETED) CURRENT_ACTION = NONE;
			break;	
		case(WAIT_PLACEMENT):
			complete = HandleLastAction(ptx, pty);
			if(complete == COMPLETED) CURRENT_ACTION = NONE;
			break;
		}	
		break;
	case LOAD_SCREEN:
		DetermineLoadFunction(ptx, pty, hwnd);
		break;
	case SAVE_DELETE:
		DetermineDeleteFunction(ptx, pty, hwnd);
		break;
	case GM_SELECT_LOAD:
		DetermineGMSelectLoadFunction(ptx, pty, hwnd);
		break;
	case SELECT_MAP:
		DetermineMapSelectFunction(ptx, pty, hwnd);
		break;
	case POP_UP:
		DeterminePopUpFunction(ptx, pty, hwnd);
		break;
	case PAUSE_MENU:
		DeterminePauseFunction(ptx, pty, hwnd);
		break;
	}
}

int Game::HandleLastAction(LONG ptx, LONG pty)
{
	// Determine grid space
	int grid_space = (ptx / display->X_PIXEL_LENGTH) + ((pty / display->Y_PIXEL_LENGTH) * display->X_PHY_LENGTH);

	Player *new_placement = nullptr;

	std::ofstream myfile;
	myfile.open(APPDATAPATH + GAMEDATAPATH + "logs.txt", std::ofstream::app);

	if (last_action.mode == MOVEXY_MODE)
	{
		std::ofstream myfile;
		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Dumping Placement Action" << std::endl;
		myfile << "bluetooth_id: " << last_action.bth_id << std::endl;
		myfile << "ptx: " << last_action.x << std::endl;
		myfile << "pty: " << last_action.y << std::endl;

		// If placing on an already occupied spot
		if (display->occupied[grid_space])
		{
			Mode = POP_UP;
			MessageBox(NULL, L"Spot already taken!", L"", 0);
			Mode = GAME_VIEW;
			return NOTCOMPLETED;
		}

		// Translate location to coordinates
		int x = grid_space % 30;
		int y = grid_space / 30;

		// If player highlight gridspace
		if (GMInfo["bluetooth_id"].get<std::string>().compare(last_action.bth_id) != 0)
		{
			// Find the player and update the x,y
			// Find player and update their location	
			myfile << "Looking for player..." << std::endl;
			bool found = false;
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				if (bluetooth->SocketsActive[i])
				{
					try
					{
						if (players[i]->is_GM())
							continue;
						if (players[i]->playerattributes["unique_character_id"].get<std::string>().compare(last_action.unique_id) == 0)
						{
							myfile << "Found and updating Player attributes" << std::endl;
							myfile << "Player bluetooth_id: " << players[i]->playerattributes["bluetooth_id"].get<std::string>() << std::endl;
							players[i]->playerattributes["character_x_coordinate"] = x;
							players[i]->playerattributes["character_y_coordinate"] = y;
							UpdateTurnOrder(players[i]->playerattributes);
							new_placement = players[i];
							found = true;
							break;
						}
					}
					catch (json::exception e)
					{
						MessageBoxA(NULL, e.what(), "INNER", 0);
					}
				}
			}
			if (found)
			{
				// Send Responce
				Message_Responder(MOVEXY, new_placement->get_index(), NULL);
			}
			else
			{
				myfile << "No player found when player should have existed" << std::endl;
			}

		}

		// Else display NPC
		else
		{			
			json encounternpcs;
			try
			{
				encounternpcs = SelectedEncounter["npcs_in_encounter"].get<std::vector<json>>();
			}
			catch (json::exception e)
			{
				Mode = POP_UP;
				MessageBoxA(NULL, SelectedEncounter.dump().c_str(), NULL, 0);
				MessageBoxA(NULL, e.what(), NULL, 0);
				Mode = GAME_VIEW;
			}
			//encounternpcs = TurnOrder["turnOrderCharacters"].get<std::vector<json>>();
			json movednpc;
			bool found = false;
			myfile << "Searching for NPC..." << std::endl;
			for (int i = 0; i < encounternpcs.size(); i++)
			{
				if (encounternpcs.at(i)["unique_character_id"].get<std::string>().compare(last_action.unique_id) == 0)
				{
					found = true;

					myfile << "Found NPC and updating NPC" << std::endl;

					// Update npc in encounter
					encounternpcs.at(i)["character_x_coordinate"] = x;
					encounternpcs.at(i)["character_y_coordinate"] = y;

					ActiveNPC newnpc;
					memset(&newnpc, 0, sizeof(ActiveNPC));
					newnpc.active = true;
					newnpc.uniqueID = encounternpcs.at(i)["unique_character_id"].get<std::string>();
					newnpc.x = x;
					newnpc.y = y;
					newnpc.filename = GetFileName(encounternpcs.at(i)["name"].get<std::string>());
					myfile << "IN MOVEXY :: Creating an ActiveNPC with unique_id: " << newnpc.uniqueID << std::endl;
					display->activeNPCs.push_back(newnpc);

					/* From here to responder*/
					UpdateGMInfo(encounternpcs.at(i));
					UpdateTurnOrder(encounternpcs.at(i));

					movednpc = encounternpcs.at(i);
					break;
				}
			}

			SelectedEncounter["npcs_in_encounter"] = encounternpcs;

			display->ShowActiveNPCs(APPDATAPATH + GAMEDATAPATH + "logs.txt");

			if (!found)
				return NOTCOMPLETED;

			// Send reponse
			Message_Responder(MOVEXY, GM_Player->get_index(), movednpc);
		}

		display->occupied[grid_space] = true;

		// Reset the last action
		memset(&last_action, 0, sizeof(Action_Struct));
		last_action.mode = -1;

		DeleteObject(*image);
		*image = (HBITMAP)LoadImageA(NULL, (display->PATHTOGRID).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);

		return COMPLETED;
	}
	
	if (!display->grid[grid_space])
	{
		Mode = POP_UP;
		// Display Error
		MessageBox(NULL, L"You must select a space within the highlighted region.", L"", 0);
		Mode = GAME_VIEW;
		return NOTCOMPLETED;
	}
	// Determine if the touch was or movmement was in the highlight spaces and on a location not occupied

	// Update player
	if (last_action.mode == MOVE)
	{
		std::ofstream myfile;
		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Dumping Move Action" << std::endl;
		myfile << "bluetooth_id: " << last_action.bth_id << std::endl;
		myfile << "ptx: " << last_action.x << std::endl;
		myfile << "pty: " << last_action.y << std::endl;
		myfile << "mode: " << last_action.mode << std::endl;
		myfile << "speed: " << last_action.speed << std::endl;
		if (display->occupied[grid_space])
		{
			Mode = POP_UP;
			MessageBox(NULL, L"Spot already taken!", L"", 0);
			Mode = GAME_VIEW;
			return NOTCOMPLETED;
		}

		Player *moving_player = nullptr;
		bool playerflag = false;

		// Translate location to coordinates
		int x = grid_space % 30;
		int y = grid_space / 30;

		int index;
		json movednpc;
		if (GMInfo["bluetooth_id"].get<std::string>().compare(last_action.bth_id) != 0)
		{
			myfile << "Searching for Player..." << std::endl;
			// Find player and update their location
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				if (bluetooth->SocketsActive[i])
					if (!players[i]->is_GM() && players[i]->playerattributes["unique_character_id"].get<std::string>().compare(last_action.unique_id) == 0)
					{
						myfile << "Player found" << std::endl;
						myfile << "Player bluetooth_id: " << players[i]->playerattributes["bluetooth_id"].get<std::string>() << std::endl;
						moving_player = players[i];
						index = moving_player->get_index();
						playerflag = true;
						break;
					}
			}
		}	
		else
		{
			json encounternpcs = SelectedEncounter["npcs_in_encounter"].get<std::vector<json>>();
			//json encounternpcs = TurnOrder["turnOrderCharacters"].get<std::vector<json>>();
	
			for (json npc : encounternpcs)
			{
				myfile << "Current NPC being checked" << std::endl;
				myfile << npc["unique_character_id"].get<std::string>() << std::endl;
				myfile << last_action.unique_id << std::endl;
				if (npc["unique_character_id"].get<std::string>().compare(last_action.unique_id) == 0)
				{
					movednpc = npc;
					index = GM_Player->get_index();
					break;
				}
			}
		}
		// Previous points
		int prevx;
		int prevy;

		if (playerflag)
		{
			myfile << "Updating Player" << std::endl;
			prevx = moving_player->playerattributes["character_x_coordinate"].get<int>();
			prevy = moving_player->playerattributes["character_y_coordinate"].get<int>();

			// Update the x,y location
			moving_player->playerattributes["character_x_coordinate"] = x;
			moving_player->playerattributes["character_y_coordinate"] = y;
			UpdateTurnOrder(moving_player->playerattributes);
		}
		else
		{
			myfile << "Found and updating NPC" << std::endl;
			prevx = movednpc["character_x_coordinate"].get<int>();
			prevy = movednpc["character_y_coordinate"].get<int>();
			
			movednpc["character_x_coordinate"] = x;
			movednpc["character_y_coordinate"] = y;

			UpdateTurnOrder(movednpc);
			UpdateGMInfo(movednpc);
			UpdateActiveNPCXY(movednpc);
		}

		// Update occupied
		display->occupied[grid_space] = true;
		display->occupied[prevy*display->X_PHY_LENGTH + prevx] = false;

		// Send reponse
		Message_Responder(MOVECHARACTER, index, movednpc);

		display->remove_area(&last_action);
		display->ShowActiveNPCs(APPDATAPATH + GAMEDATAPATH + "logs.txt");

		// Delete last_action
		memset(&last_action, 0, sizeof(Action_Struct));
		last_action.mode = -1;

		// if player is an NPC do this
		//display->move_npc(grid_space, prevx, prevy);
		display->Remove_Spot(prevx, prevy);

		DeleteObject(*image);
		*image = (HBITMAP)LoadImageA(NULL, (display->PATHTOGRID).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);
	}
	else if (last_action.mode == ATTACK)
	{
		std::ofstream myfile;
		myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
		myfile << "Dumping Attack Action" << std::endl;
		myfile << "bluetooth_id: " << last_action.bth_id << std::endl;
		myfile << "ptx: " << last_action.x << std::endl;
		myfile << "pty: " << last_action.y << std::endl;
		myfile << "mode: " << last_action.mode << std::endl;
		myfile << "type: " << last_action.damage_type << std::endl;
		myfile << "range: " << last_action.range << std::endl;

		if (!display->occupied[grid_space])
		{
			Mode = POP_UP;
			MessageBox(NULL, L"There is no player at that location.", L"", 0);
			Mode = GAME_VIEW;
			return NOTCOMPLETED;
		}

		HandleEffects(hSerial, APPDATAPATH + GAMEDATAPATH + GAMESOUNDS,last_attack["damage_type"].get<std::string>(), LightsLoaded);
		last_attack = nullptr;

		// Translate location to coordinates
		int y = grid_space / 30;
		int x = grid_space % 30;
		json attacked;
		Player *attacked_player = nullptr;
		int index;
		bool found = false;

		myfile << "Searching for Player..." << std::endl;
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (bluetooth->SocketsActive[i])
			{
				if (players[i]->is_GM())
					continue;
				if (players[i]->playerattributes["character_x_coordinate"].get<int>() == x && players[i]->playerattributes["character_y_coordinate"].get<int>() == y)
				{
					myfile << "Attacking Player" << std::endl;
					attacked_player = players[i];
					index = attacked_player->get_index();
					attacked = players[i]->playerattributes;
					found = true;
					break;
				}
			}
		}
	
		// If not a player check NPCs
		if (!found)
		{
			json encounternpcs = SelectedEncounter["npcs_in_encounter"].get<std::vector<json>>();
			//json encounternpcs = TurnOrder["turnOrderCharacters"].get<std::vector<json>>();

			for (json npc : encounternpcs)
			{
				if (npc["character_x_coordinate"].get<int>() == x && npc["character_y_coordinate"].get<int>() == y)
				{
					myfile << "Attacking NPC" << std::endl;
					attacked = npc;
					index = -1;
					found = true;
					break;
				}
			}
		}

		// If still not found shouldnt be a thing
		if (!found)
		{
			// Error that shouldnt occur
		}

		//Send reponse
		Message_Responder(ATTACK_JSON, index, attacked);

		display->remove_area(&last_action);
		display->ShowActiveNPCs(APPDATAPATH + GAMEDATAPATH + "logs.txt");

		// Reset the last action
		memset(&last_action, 0, sizeof(Action_Struct));
		last_action.mode = -1;

		DeleteObject(*image);
		*image = (HBITMAP)LoadImageA(NULL, (display->PATHTOGRID).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessageW(*hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)*image);
	}
	return COMPLETED;
}

std::string Game::GetFileName(std::string name)
{
	std::string filename = APPDATAPATH + GAMEIMAGEPATH + NPCIMAGES;
	if (name.compare("Adult White Dragon") == 0)
		filename += "Adult_White_Dragon.png";
	else if (name.compare("Pirate Captain") == 0)
		filename += "Pirate_Captain.png";
	else if (name.compare("Alpha Wolf") == 0)
		filename += "Alpha_Wolf.png";
	else
		filename += "Alpha_Wolf.png";

	return filename;
}

void Game::UpdateGMInfo(json updateNPC)
{
	// Grab components
	std::string name = SelectedEncounter["encounter_name"].get<std::string>();
	std::vector<json> npcsencounter = SelectedEncounter["npcs_in_encounter"].get<json>();
	std::vector<json> newnpcsencounter;

	// Find old NPC and replace NPC
	for (json npc : npcsencounter)
	{
		if (npc["unique_character_id"].get<std::string>().compare(updateNPC["unique_character_id"].get<std::string>()) == 0)
			newnpcsencounter.push_back(updateNPC);
			
		else newnpcsencounter.push_back(npc);

	}

	// Rebuild
	json NewSelectedEncounter;
	NewSelectedEncounter["encounter_name"] = name;
	NewSelectedEncounter["npcs_in_encounter"] = newnpcsencounter;

	// Save
	GMInfo["encounter_selected"] = NewSelectedEncounter;
	SelectedEncounter = NewSelectedEncounter;

	return;
}

void Game::Load_Game(std::string LoadGameName)
{
	// Variables
	std::ifstream LoadFile;
	std::string line;
	bool TurnOrderFlag = false;

	// Grab GameName
	std::string LoadFilePath;
	LoadFilePath = APPDATAPATH + GAMEDATAPATH + LoadGameName + ".game";
	CURRENTGAMEPATH = LoadFilePath;
	SAVESINFONEW = APPDATAPATH + GAMEDATAPATH + LoadGameName + "New.game";
	GameName = LoadGameName;

	// Open given save file
	LoadFile.open(LoadFilePath);

	// Load GMInfo
	std::getline(LoadFile, line);
	try
	{
		GMInfo = json::parse(line.c_str());
		SelectedEncounter = GMInfo["encounter_selected"].get<json>();
	}
	catch (json::exception e)
	{
		Mode = POP_UP;
		MessageBoxA(NULL, e.what(), NULL, 0);
		Mode = LOAD_GAME;
	}

	// Load each player
	for (int i = 0; i < MAX_PLAYERS - 1; i++)
	{
		std::getline(LoadFile, line);
		// No more Players saved
		if (line.size() == 0)
		{
			TurnOrderFlag = true;
			break;
		}
		
		// Create a vector of loaded players
		try
		{
			LoadedPlayers.push_back(json::parse(line.c_str()));
		}
		catch (json::exception e)
		{
			Mode = POP_UP;
			MessageBoxA(NULL, e.what(), NULL, 0);
			Mode = LOAD_GAME;
		}
	}

	// If the flag is raised, then skip
	if(!TurnOrderFlag)
		std::getline(LoadFile, line);

	// Turn order
	std::getline(LoadFile, line);
	TurnOrder = json::parse(line.c_str());

	// Create the activeNPCs
	CreateActiveNPCs();

	// Close the file
	LoadFile.close();

	return;
}

void Game::CreateActiveNPCs()
{
	std::vector<json> turns = TurnOrder["turnOrderCharacters"];
	std::ofstream myfile;
	myfile.open(APPDATAPATH + GAMEDATAPATH "logs.txt", std::ofstream::app);
	for (json turn : turns)
	{
		// If not a player, then an active NPC
		if (!turn["player"].get<bool>())
		{
			if (turn["character_x_coordinate"].get<int>() != -1 && turn["character_y_coordinate"].get<int>() != -1)
			{
				ActiveNPC newnpc;
				memset(&newnpc, 0, sizeof(ActiveNPC));
				newnpc.active = true;
				newnpc.filename = GetFileName(turn["name"].get<std::string>());
				newnpc.uniqueID = turn["unique_character_id"];
				newnpc.x = turn["character_x_coordinate"];
				newnpc.y = turn["character_y_coordinate"];
				myfile << "IN CREATEACTIVENPCS :: Creating an ActiveNPC with unique_id: " << newnpc.uniqueID << std::endl;
				display->activeNPCs.push_back(newnpc);
			}
		}
	}
}

void Game::SetGameName()
{
	std::ifstream config;

	config.open(PATHTOCONFIG);
	
	std::string line;
	std::getline(config, line);

	size_t found = line.find(":");
	std::string num = line.substr(found + 1);
	GameName = "Game_" + num;

	CURRENTGAMEPATH = APPDATAPATH + GAMEDATAPATH + GameName + ".game";
}

// Save info about the game
/***********************************
	LAST SAVE TIME
	Number of Players
	Name of the selected encounter
	Current Map name
***********************************/
void Game::Update_Saves_File()
{
	std::ifstream oldfile;
	std::ofstream newfile;

	oldfile.open(SAVESINFOOLD);
	newfile.open(SAVESINFONEW, std::ofstream::out);

	std::string line;
	std::string tempNameString = "Game Name: " + GameName;

	bool flag = false;

	while (std::getline(oldfile, line))
	{
		if (line.compare(tempNameString) == 0)
		{
			// Name doesnt change
			newfile << line << std::endl;
			// Variables
			char datebuf[128], timebuf[128];

			// Display operating system-style date and time.
			_strtime_s(timebuf, 128);
			_strdate_s(datebuf, 128);

			// Format time for just hour and minute
			timebuf[5] = '\0';
			char time[100];
			sprintf_s(time, "Last Saved: %s %s", datebuf, timebuf);
			newfile << time << std::endl;

			// Save the number of players
			int count = 0;
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				if (bluetooth->SocketsActive[i])
					count++;
			}
			newfile << "Number of Players: " << count << std::endl;

			// Save the current encounter name
			newfile << "Current Encounter Name: " << SelectedEncounter["encounter_name"].get<std::string>() << std::endl;
						
			// Save the current map name
			if (CurrentMap.compare("None Selected") == 0)
			{
				newfile << "Current Map Name: No Map Selected" << std::endl;
			}
			else
				newfile << "Current Map Name: " << CurrentMap << std::endl;

	
			newfile << display->OriginalFileExtension << std::endl;


			flag = true;
			// skip the next 4 lines because we just replaced them
			std::getline(oldfile, line);
			std::getline(oldfile, line);
			std::getline(oldfile, line);			
			std::getline(oldfile, line);
			std::getline(oldfile, line);
			continue;
		}

		// If name doesnt match, copy all info to new file
		newfile << line << std::endl;
		std::getline(oldfile, line);
		newfile << line << std::endl;
		std::getline(oldfile, line);
		newfile << line << std::endl;
		std::getline(oldfile, line);
		newfile << line << std::endl;
		std::getline(oldfile, line);
		newfile << line << std::endl;		
		std::getline(oldfile, line);
		newfile << line << std::endl;
	}

	// If not found append
	if (!flag)
	{
		// Append
		newfile << "Game Name: " << GameName << std::endl;
		// Variables
		char datebuf[128], timebuf[128];

		// Display operating system-style date and time.
		_strtime_s(timebuf, 128);
		_strdate_s(datebuf, 128);

		// Format time for just hour and minute
		timebuf[5] = '\0';
		char time[100];
		sprintf_s(time, "Last Saved: %s %s", datebuf, timebuf);
		newfile << time << std::endl;

		// Save the number of players
		int count = 0;
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (bluetooth->SocketsActive[i])
				count++;
		}
		newfile << "Number of Players: " << count << std::endl;

		// Save the current encounter name
		newfile << "Current Encounter Name: " << SelectedEncounter["encounter_name"].get<std::string>() << std::endl;

		// Save the current map name
		newfile << "Current Map Name: " << CurrentMap << std::endl;

		newfile << display->OriginalFileExtension << std::endl;
	}

	oldfile.close();
	newfile.close();

	remove(SAVESINFOOLD.c_str());
	rename(SAVESINFONEW.c_str(), SAVESINFOOLD.c_str());
}

void Game::SaveGameInitiate()
{
	json savegameGM;
	json savegame;
	savegameGM["action"] = "Save Game GM Info";
	savegame["action"] = "Save Game";
	std::string jsonstringfy = savegame.dump();
	std::string jsonstringfy2 = savegameGM.dump();
	
	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		if (bluetooth->SocketsActive[i])
		{
			if (GM_Player->get_index() == i)
			{
				players[i]->initiatesave = true;
				strcpy(bluetooth->SendBuffer[i], jsonstringfy2.c_str());
				bluetooth->SendBufferFlag[i] = true;
			}
			else
			{
				players[i]->initiatesave = true;
				strcpy(bluetooth->SendBuffer[i], jsonstringfy.c_str());
				bluetooth->SendBufferFlag[i] = true;
			}
		}
	}
}

void Game::Save_Game()
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (bluetooth->SocketsActive[i])
		{
			players[i]->initiatesave = false;
			players[i]->saved = false;
		}
	}

	// Update config if needed
	std::ifstream config;

	config.open(PATHTOCONFIG);

	std::string line;
	std::getline(config, line);

	size_t found = line.find(":");
	std::string num = line.substr(found + 1);
	config.close();

	found = GameName.find("_");
	std::string curnum = GameName.substr(found + 1);

	// The game number can only ever be equal or less. If equal then num games needs to increase
	if (num.compare(curnum) == 0)
	{
		std::ofstream newconfig;
		newconfig.open(PATHTOCONFIG);
		newconfig << "Number of game:" + std::to_string(std::stoi(num) + 1);
	}

	// Create/Update entry of save games
	Update_Saves_File();

	// Open current games save file if it exists to overwrite
	std::string SaveFilePath = CURRENTGAMEPATH;
	std::ofstream SaveFile;
	
	SaveFile.open(SaveFilePath);

	// Save GMInfo
	SaveFile << GMInfo.dump() << std::endl;

	// Save each player
	for (Player* player : players)
	{
		if (player == NULL)
			break;

		if (player->get_index() == GM_Player->get_index())
			continue;

		// Make sure player has player data
		if (player->playerattributes == nullptr)
			continue;

		// Save the Player
		SaveFile << player->playerattributes.dump() << std::endl;
	}

	// Newline between GM+players and turn order
	SaveFile << std::endl;

	// Save last Turn order
	SaveFile << TurnOrder.dump() << std::endl;

	// Close the file
	SaveFile.close();

	SAVE = false;

	if(EXIT)				
		SendMessageW(*hwnd, WM_COMMAND, FILE_MENU_EXIT, NULL);
	if (RETURNFLAG)
	{
		ResetGame();
		SendMessageW(*hwnd, WM_COMMAND, RETURN, NULL);
		RETURNFLAG = false;
	}

	return;
}

void Game::ResetGame()
{
	// Clear current folder
	display->CleanCurrentFolder(CurrentMap, APPDATAPATH + GAMEIMAGEPATH + MAPIMAGES + CURRENTIMAGES);

	// Reset map name
	CurrentMap.clear();

	// Reset variables
	CurrentMap = "None Selected";
	SelectedEncounter["encounter_name"] = "No Selected Encounter";
	GMInfo = nullptr;
	EmptyGMInfo = json::parse("{\"action\":\"GMInfo\",\"bluetooth_id\":\"\",\"encounter_selected\":{\"encounter_name\":\"No Selected Encounter\",\"npcs_in_encounter\":[]},\"encounters_list\":[],\"info_tab_gm\":[\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"maps_list\":[],\"npcs_list\":[],\"players_list\":[],\"round_number\":0,\"turn_number\":0}");
	TurnOrder = json::parse("{\"action\":\"Update Turn Order\",\"turnOrderCharacters\":[]}");

	// Clear Loaded Players
	while (!LoadedPlayers.empty())
		LoadedPlayers.pop_back();

	for (int i = 0; i < MAX_PLAYERS; i++)
		if(bluetooth->SocketsActive[i])
			players[i]->playerattributes = nullptr;

	while (!display->activeNPCs.empty())
		display->activeNPCs.pop_back();
}


// Save the text string for the map name ...\\map_grid.png => map
void Game::Set_Map_Name(std::string preparemap)
{
	// Remove prefix
	int i = preparemap.find_last_of('\\');
	preparemap.erase(0, i + 1);

	// _grid + postfix
	i = preparemap.find_last_of('_');
	preparemap.erase(i, preparemap.size());

	// Set map
	CurrentMap = preparemap;
}

void Game::autosave()
{
	auto start = std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> end;
	
	while (RUN)
	{
		end = std::chrono::steady_clock::now();

		// Every 5 Minutes save
		if (std::chrono::duration_cast<std::chrono::seconds>(end - start).count() >= 600)
		{
			// Save Game
			SaveGameInitiate();
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				if (!RUN)
					return;

				if (bluetooth->SocketsActive[i])
				{
					if (!players[i]->saved)
					{
						i = -1;
						continue;
					}
				}
			}
			Save_Game();

			// Restart timer
			start = std::chrono::steady_clock::now();
		}

		if (SAVE)
		{
			// Save Game
			SaveGameInitiate();
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				if (!RUN)
					return;

				if (bluetooth->SocketsActive[i])
				{
					if (!players[i]->saved)
					{
						i = -1;
						continue;
					}
				}
			}
			Save_Game();

			// Restart timer
			start = std::chrono::steady_clock::now();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}


void Game::UpdateTurnOrder(json message)
{
	try
	{
		std::vector<json> turns = TurnOrder["turnOrderCharacters"].get<std::vector<json>>();

		for (int i = 0; i < turns.size(); i++)
		{
			if (turns.at(i)["unique_character_id"].get<std::string>().compare(message["unique_character_id"].get<std::string>()) == 0)
			{
				turns.at(i)["character_x_coordinate"] = message["character_x_coordinate"].get<int>();
				turns.at(i)["character_y_coordinate"] = message["character_y_coordinate"].get<int>();
				break;
			}
		}
		TurnOrder["turnOrderCharacters"] = turns;
	}
	catch (json::exception e)
	{
		int oldmode = Mode;
		Mode = POP_UP;
		MessageBoxA(NULL, e.what(), NULL, 0);
		Mode = oldmode;
	}
}

void Game::UpdateActiveNPC(json message)
{
	std::vector<json> turns = message["turnOrderCharacters"].get<std::vector<json>>();

	for (int i = 0; i < display->activeNPCs.size(); i++)
		display->Remove_Spot(display->activeNPCs.at(i).x, display->activeNPCs.at(i).y);

	// Clear all the NPCs
	while (!display->activeNPCs.empty())
		display->activeNPCs.pop_back();

	// Loop over the turns and place any NPCs that have a location
	for (json turn : turns)
	{
		// Only look for NPCs
		if (turn["player"].get<bool>() == false)
		{
			// If the player has a valid location create an active npc
			if (turn["character_x_coordinate"].get<int>() != -1 && turn["character_y_coordinate"].get<int>() != -1)
			{
				ActiveNPC npc;
				memset(&npc, 0, sizeof(ActiveNPC));
				npc.active = true;
				npc.uniqueID = turn["unique_character_id"].get<std::string>();
				npc.x = turn["character_x_coordinate"].get<int>();
				npc.y = turn["character_y_coordinate"].get<int>();
				npc.filename = GetFileName(turn["name"].get<std::string>());

				display->activeNPCs.push_back(npc);
			}
		}
	}
}

void Game::UpdateActiveNPCXY(json message)
{
	for (int i = 0; i < display->activeNPCs.size(); i++)
	{
		if (display->activeNPCs.at(i).uniqueID.compare(message["unique_character_id"].get<std::string>()) == 0)
		{
			display->activeNPCs.at(i).x = message["character_x_coordinate"].get<int>();
			display->activeNPCs.at(i).y = message["character_y_coordinate"].get<int>();
		}
	}
}