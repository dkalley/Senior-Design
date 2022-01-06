#include "pch.h"

#include "Game.h"
#include "Player.h"
//#include <windows.storage.pickers.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <commdlg.h>
#include "Dialog.h"
#include <locale>
#include <codecvt>
#include <shellscalingapi.h>

#include <nlohmann/json.hpp>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "Shcore.lib")
// for convenience
using json = nlohmann::json;
// NameSpaces
//using namespace std;
//using namespace Gdiplus;

// Definition for call back options
#define FILE_MENU_NEW 1 
#define FILE_MENU_EXIT 2
#define OPTIONS 3
#define RETURN 4
#define ABOUT 7
#define LOGIN 8
#define TESTING 10
#define UPDATE 11
#define PLAY 12
#define REFRESH 13
#define READY 14
#define LOOKUP 15
#define DEVICE_SELECTION 16
#define SEND 17
#define CONNECT 18
#define LOAD_GAME 19
#define GM_BUTTONS 20 // - 24
#define READY_GM 25
#define REFRESH_GM 26
#define OPEN_MAP 27
#define READY_MAP 28
#define SERVER1 29
#define RESUME_GAME 30
#define CHANGE_MAP 31
#define MAIN_MENU_PAUSE 32
#define QUIT_DESKTOP 33
#define SAVE_GAME 34
#define READY_LOAD 35
#define LOAD_BUTTONS 37 // - 41
#define CLINK_BUTTONS 42 // - 46
#define CHLINK_BUTTONS 47 // - 51
#define READY_LINK 52
#define REFRESH_LINK 53
#define READY_GM_LOAD 54
#define NEXT_PAGE 55
#define PREV_PAGE 56
#define DEBUGGING 57
#define DELETE_SAVE 58
#define RETURN_OPITONS 59
#define NEXT_PAGE_DEL 60
#define PREV_PAGE_DEL 61
#define DELETE_GAME_BUTTONS 62 // - 66

#define START_UP "images/bmp/wilderness-map.bmp" // Will be a default image in the end

// Definition for current screen mode
#define MAIN_MENU 1000
#define BTH_CONNECT 1001
#define GM_SELECT 1002
#define SELECT_MAP 1003
#define GAME_VIEW 1004
#define LOAD_SCREEN 1005
#define GM_SELECT_LOAD 1006
#define SAVE_DELETE 1007
#define OPEN_FILE 1008


// Function Prototypes
// Windows required functions
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK PfnDeviceCallback(LPVOID pvParam, const BLUETOOTH_DEVICE_INFO *pDevice);

// Menu creating functions
void CreateGameView(HWND hwnd, wchar_t *mapname);
void CreateMainMenu(HWND hwnd);
void CreateBluetoothView(HWND hwnd);
void CreateConnectWindow(HWND hwnd);
void CreateChooseGMWindow(HWND hwnd);
void CreateChooseMapWindow(HWND hwnd);
void CreatePauseScreen(HWND hwnd);
void CreateLoadScreen(HWND hwnd);
void CreatePlayerLinkScreen(HWND hwnd);
void CreateGMSelectLoad(HWND hwnd);
void CreateOptionsMenu(HWND hwnd);
void CreateDeleteSave(HWND hwnd);

// Menu destroying functions
void DestroyMainMenu();
void DestroyBluetoothWindow();
void DestroyConnectWindow();
void DestroyGMWindow();
void DestroyChooseMapWindow();
void DestroyPauseScreen();
void DestroyGameView();
void DestroyLoadScreen();
void DestroyPlayerLinkScreen();
void DestroyGMSelectLoad();
void DestroyOptionsMenu();
void DestroyDeleteSave();

// Helper functions
void ConfirmationBox(wchar_t * message, wchar_t* title, UINT flags);
void AddMenus(HWND hwnd);
void GenerateDeviceList(HWND hwnd);
void GenerateGMButtons(HWND hwnd);
void GenerateLoadButtons(HWND hwnd, std::wstring filepath);
void GenerateLinkConnected(HWND hwnd);
void load_images();
void free_images();
void Add_New_Devices();
void scan();
void GetChoosenDevice(int index, HWND hwnd);
void GetLoad(int index, HWND hwnd);
HBITMAP GetThumbnail(std::wstring File);
void ListAllFiles();
void SetLoadPageNumber();
void LinkCharacter();
void NextPage(HWND hwnd);
void PrevPage(HWND hwnd);
void NextPageDel(HWND hwnd);
void PrevPageDel(HWND hwnd);
void SetDelPageNumber();
void GetDel(HWND hwnd, int index);
void UpdateSaveInfoFile(std::wstring filename);
void init_Game();
int CreateMainWindow(HINSTANCE hInstance);

//void LoadImages(string imgPath);
//void DisplayImages(HWND hwnd);
void StartGame();
void trythis2();

std::ofstream myglobalfile;
int Mode;
//char JSON_STRING[BUFFER_SIZE] = "{\"acrobatics\":true,\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"test attack, 1, 4, Fire, 5, true, con\",\"Unarmed Strike, 1, 4, Bludgeoning, 5, false, str\"],\"cha_proficiency\":false,\"character_ac_total\":6,\"character_cha\":6,\"character_cha_mod\":-2,\"character_class\":\"Fighter\",\"character_con\":5,\"character_con_mod\":-3,\"character_current_hp\":2,\"character_dex\":2,\"character_dex_mod\":-4,\"character_int\":4,\"character_int_mod\":-3,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"testing json name\",\"character_proficiency\":3,\"character_race\":\"Dwarf\",\"character_speed\":25,\"character_str\":1,\"character_str_mod\":-5,\"character_turn\":false,\"character_wis\":5,\"character_wis_mod\":-3,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"23\",\"11\",\"2\",\"1\",\"10\",\"2\",\"100\",\"Dagger\",\"Rope\",\"Heavy Armor\",\"Alert\",\"Human language\",\"Notes for character\",\"background of character\"],\"insight\":true,\"int_proficiency\":false,\"intimidation\":true,\"investigation\":true,\"medicine\":true,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":true,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":true,\"str_proficiency\":true,\"survival\":false,\"wis_proficiency\":false}";

// Global Variables
HMENU hMenu;
HWND hLogin, hPass, hWnd, hImage, title, play_button, quit_button, titlebar, refresh_button, ready_button, nodevices, lookup_button, last_button;
std::vector<HWND> device_buttons;
HBITMAP image;
LPCWSTR warning;
HFONT titleFont;
HBITMAP play_button_icon, background_image, options_button_image, quit_button_image, pair_button_image, refresh_button_image, ready_button_image, device_button_image;
HBITMAP scan_image, scan_image1, scan_image2, scan_image3, background_connect_image;
HWND background, options_button, device_button, return_button, load_button, listbox;
HWND hEdit, hEdit1, hEdit2, conn_add, conn_name, sendtext, sendbutton, textsend, receivetext, connectbutton;
HWND container, Device_Choosen, mapselectwindow, open_button;
HWND sendfunction, sendfunctiontxt, recvfunction, recvfunctiontxt;
HWND savegamebutton, pausemenu, resumebutton, changemapbutton, pausemainmenu, qtdbutton, pages, nextpage, prevpage, Load_Choosen, linkdisplay;
HWND optionsmenu, debuggingbutton, deletesavesbutton, optionsreturnbutton;
std::vector<HWND> LoadGameButtons, DeleteGameButtons, DeleteGameXs, GMButtons;
std::vector<std::string> GameNames , FileNames, DelTileSave, MapNamesSave;
std::vector<std::wstring> LoadTile, DelTile, MapNames;
std::wstring wlink;
int DelNumPages, LoadNumPages;

wchar_t allsendbuffer[BUFFER_SIZE*10];
wchar_t allrecvbuffer[BUFFER_SIZE*10];
//HICON play_button_icon;

int location = 0;
Game *game;
BOOL GM_Select_Flag, Load_Select_Flag, MAP_Select_Flag;
std::wstring ConnectDeviceNames[MAX_PLAYERS];
wchar_t *MAPNAME;
int GM_SELECTED_DEVICE;
BOOL escflag;
int LoadGamePageNumber, LoadSelected, DelGamePageNumber, DelSelected;;
int ConnectedDeviceSelected, CharacterSelected;
std::string AppDataMainPath;

char JSON_STRING[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 1, 4, Bludgeoning, 5, false, str\"],\"bluetooth_id\":\"709bfaef-8ae2-438f-863d-cb61be639ba3\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"ddfc8c0c-2771-4eeb-9cfe-d85886c4d369\",\"wis_proficiency\":false}";
//char JSON_STRING2[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 3, 5, Bludgeoning, 6, false, str\"],\"bluetooth_id\":\"0xA402B94A39DA\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8801\",\"wis_proficiency\":false}";
char MOVE_STRING3[BUFFER_SIZE] = "{\"action\":\"Move Character\",\"speed\" : 50,\"character_x_coordinate\" : 5, \"character_y_coordinate\" : 30,\"bluetooth_id\" : \"709bfaef-8ae2-438f-863d-cb61be639ba3\",\"unique_character_id\" : \"ddfc8c0c-2771-4eeb-9cfe-d85886c4d369\"}";
char ATTACK_STRING[BUFFER_SIZE] = "{\"action\":\"attack\",\"damage_roll\" : 8,\"damage_type\" : \"Bludgeoning\",\"range\" : 50,\"character_x_coordinate\" : 8,\"character_y_coordinate\" : 38,\"bluetooth_id\" : \"709bfaef-8ae2-438f-863d-cb61be639ba3\",\"unique_character_id\" : \"ddfc8c0c-2771-4eeb-9cfe-d85886c4d369\"}";
char MOVEXY_STRING[BUFFER_SIZE] = "{ \"action\":\"MoveXY\",\"character\" : \"Players\",\"character_x_coordinate\" : 5,\"character_y_coordinate\" : 30,\"bluetooth_id\" : \"709bfaef-8ae2-438f-863d-cb61be639ba3\",\"unique_character_id\" : \"ddfc8c0c-2771-4eeb-9cfe-d85886c4d369\"}";

char JSON_STRING2[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 3, 5, Bludgeoning, 6, false, str\"],\"bluetooth_id\":\"817b8dac-6a42-82a9-a782-98276f8c7951\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8801\",\"wis_proficiency\":false}";
char JSON_STRING3[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 3, 5, Bludgeoning, 6, false, str\"],\"bluetooth_id\":\"817b8dac-6a42-82a9-a782-98276f8c7952\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8802\",\"wis_proficiency\":false}";
char JSON_STRING4[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 3, 5, Bludgeoning, 6, false, str\"],\"bluetooth_id\":\"817b8dac-6a42-82a9-a782-98276f8c7953\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8803\",\"wis_proficiency\":false}";
char JSON_STRING5[BUFFER_SIZE] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 3, 5, Bludgeoning, 6, false, str\"],\"bluetooth_id\":\"817b8dac-6a42-82a9-a782-98276f8c7954\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8804\",\"wis_proficiency\":false}";


// TEST JSON STRINGS
char UPDATEGMINFO[BUFFER_SIZE] = "{\"action\":\"Update GM\",\"bluetooth_id\":\"5cca8616-2d88-4790-88d7-86c83ed1bf17\",\"encounter_selected\":{\"encounter_name\":\"encounter 2\",\"npcs_in_encounter\":[{\"ac\":19,\"cha_score\":17,\"challenge_score\":15,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":21,\"current_hp\":207,\"dex_score\":12,\"exp_given\":13000,\"hp\":207,\"initiative\":0,\"int_score\":18,\"name\":\"Adult Green Dragon\",\"npc_attack_buttons\":[\"Bite, 2, 10, piercing, 10, str\",\"Claw, 2, 6, slashing, 5, str\",\"Tail, 2, 8, bludgeoning, 15, str\"],\"player\":false,\"speed\":80,\"str_score\":23,\"turn\":true,\"unique_character_id\":\"3504ea90-413a-453b-969c-225153c4935e\",\"wis_score\":15},{\"ac\":15,\"cha_score\":8,\"challenge_score\":1,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":10,\"current_hp\":7,\"dex_score\":14,\"exp_given\":50,\"hp\":7,\"initiative\":0,\"int_score\":10,\"name\":\"Goblin\",\"npc_attack_buttons\":[\"Scimitar, 1, 6, slashing, 5, dex\",\"Shortbow, 1, 6, piercing, 80, dex\"],\"player\":false,\"speed\":30,\"str_score\":8,\"turn\":false,\"unique_character_id\":\"2191570b-249a-4150-8691-e0ac0ef6a8b4\",\"wis_score\":8},{\"ac\":0,\"cha_score\":0,\"challenge_score\":0,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":0,\"current_hp\":0,\"dex_score\":0,\"exp_given\":0,\"hp\":0,\"initiative\":0,\"int_score\":0,\"name\":\"Player 1\",\"npc_attack_buttons\":[],\"player\":true,\"speed\":0,\"str_score\":0,\"turn\":false,\"unique_character_id\":\"62af54ec-8844-4778-9f21-4efa9b2dff67\",\"wis_score\":0},{\"ac\":0,\"cha_score\":0,\"challenge_score\":0,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":0,\"current_hp\":0,\"dex_score\":0,\"exp_given\":0,\"hp\":0,\"initiative\":0,\"int_score\":0,\"name\":\"Player 2\",\"npc_attack_buttons\":[],\"player\":true,\"speed\":0,\"str_score\":0,\"turn\":false,\"unique_character_id\":\"bc34c1b4-48a7-45b5-a0bc-522085c12334\",\"wis_score\":0},{\"ac\":0,\"cha_score\":0,\"challenge_score\":0,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":0,\"current_hp\":0,\"dex_score\":0,\"exp_given\":0,\"hp\":0,\"initiative\":0,\"int_score\":0,\"name\":\"Player 3\",\"npc_attack_buttons\":[],\"player\":true,\"speed\":0,\"str_score\":0,\"turn\":false,\"unique_character_id\":\"d703bcec-e37c-4c58-8aa4-02ec769be794\",\"wis_score\":0},{\"ac\":0,\"cha_score\":0,\"challenge_score\":0,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":0,\"current_hp\":0,\"dex_score\":0,\"exp_given\":0,\"hp\":0,\"initiative\":0,\"int_score\":0,\"name\":\"Player 4\",\"npc_attack_buttons\":[],\"player\":true,\"speed\":0,\"str_score\":0,\"turn\":false,\"unique_character_id\":\"756f5a87-b618-4a58-aff4-49a57e1d3b43\",\"wis_score\":0}]},\"encounters_list\":[{\"encounter_name\":\"encounter 2\",\"npcs_in_encounter\":[{\"ac\":19,\"cha_score\":17,\"challenge_score\":15,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":21,\"current_hp\":207,\"dex_score\":12,\"exp_given\":13000,\"hp\":207,\"initiative\":0,\"int_score\":18,\"name\":\"Adult Green Dragon\",\"npc_attack_buttons\":[\"Bite, 2, 10, piercing, 10, str\",\"Claw, 2, 6, slashing, 5, str\",\"Tail, 2, 8, bludgeoning, 15, str\"],\"player\":false,\"speed\":80,\"str_score\":23,\"turn\":false,\"unique_character_id\":\"3504ea90-413a-453b-969c-225153c4935e\",\"wis_score\":15},{\"ac\":15,\"cha_score\":8,\"challenge_score\":1,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":10,\"current_hp\":7,\"dex_score\":14,\"exp_given\":50,\"hp\":7,\"initiative\":0,\"int_score\":10,\"name\":\"Goblin\",\"npc_attack_buttons\":[\"Scimitar, 1, 6, slashing, 5, dex\",\"Shortbow, 1, 6, piercing, 80, dex\"],\"player\":false,\"speed\":30,\"str_score\":8,\"turn\":false,\"unique_character_id\":\"2191570b-249a-4150-8691-e0ac0ef6a8b4\",\"wis_score\":8}]},{\"encounter_name\":\"vcvcvc\",\"npcs_in_encounter\":[{\"ac\":19,\"cha_score\":17,\"challenge_score\":15,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":21,\"current_hp\":207,\"dex_score\":12,\"exp_given\":13000,\"hp\":207,\"initiative\":0,\"int_score\":18,\"name\":\"Adult Green Dragon\",\"npc_attack_buttons\":[\"Bite, 2, 10, piercing, 10, str\",\"Claw, 2, 6, slashing, 5, str\",\"Tail, 2, 8, bludgeoning, 15, str\"],\"player\":false,\"speed\":80,\"str_score\":23,\"turn\":false,\"unique_character_id\":\"3504ea90-413a-453b-969c-225153c4935e\",\"wis_score\":15},{\"ac\":19,\"cha_score\":17,\"challenge_score\":15,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":21,\"current_hp\":207,\"dex_score\":12,\"exp_given\":13000,\"hp\":207,\"initiative\":0,\"int_score\":18,\"name\":\"Adult Green Dragon\",\"npc_attack_buttons\":[\"Bite, 2, 10, piercing, 10, str\",\"Claw, 2, 6, slashing, 5, str\",\"Tail, 2, 8, bludgeoning, 15, str\"],\"player\":false,\"speed\":80,\"str_score\":23,\"turn\":false,\"unique_character_id\":\"3504ea90-413a-453b-969c-225153c4935e\",\"wis_score\":15},{\"ac\":19,\"cha_score\":17,\"challenge_score\":15,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":21,\"current_hp\":207,\"dex_score\":12,\"exp_given\":13000,\"hp\":207,\"initiative\":0,\"int_score\":18,\"name\":\"Adult Green Dragon\",\"npc_attack_buttons\":[\"Bite, 2, 10, piercing, 10, str\",\"Claw, 2, 6, slashing, 5, str\",\"Tail, 2, 8, bludgeoning, 15, str\"],\"player\":false,\"speed\":80,\"str_score\":23,\"turn\":false,\"unique_character_id\":\"3504ea90-413a-453b-969c-225153c4935e\",\"wis_score\":15},{\"ac\":15,\"cha_score\":8,\"challenge_score\":1,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":10,\"current_hp\":7,\"dex_score\":14,\"exp_given\":50,\"hp\":7,\"initiative\":0,\"int_score\":10,\"name\":\"Goblin\",\"npc_attack_buttons\":[\"Scimitar, 1, 6, slashing, 5, dex\",\"Shortbow, 1, 6, piercing, 80, dex\"],\"player\":false,\"speed\":30,\"str_score\":8,\"turn\":false,\"unique_character_id\":\"2191570b-249a-4150-8691-e0ac0ef6a8b4\",\"wis_score\":8},{\"ac\":15,\"cha_score\":8,\"challenge_score\":1,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":10,\"current_hp\":7,\"dex_score\":14,\"exp_given\":50,\"hp\":7,\"initiative\":0,\"int_score\":10,\"name\":\"Goblin\",\"npc_attack_buttons\":[\"Scimitar, 1, 6, slashing, 5, dex\",\"Shortbow, 1, 6, piercing, 80, dex\"],\"player\":false,\"speed\":30,\"str_score\":8,\"turn\":false,\"unique_character_id\":\"2191570b-249a-4150-8691-e0ac0ef6a8b4\",\"wis_score\":8}]}],\"info_tab_gm\":[\"1\",\"2\",\"3\",\"4\",\"5\",\"6\",\"7\"],\"maps_list\":[\"Plains Outside Mordor\",\"Desolate Lands\",\"Dragon Den - Top\",\"Arthur\\u0027s Castle - Interior\",\"Deep Woods\"],\"npcs_list\":[{\"ac\":19,\"cha_score\":17,\"challenge_score\":15,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":21,\"current_hp\":207,\"dex_score\":12,\"exp_given\":13000,\"hp\":207,\"initiative\":0,\"int_score\":18,\"name\":\"Adult Green Dragon\",\"npc_attack_buttons\":[\"Bite, 2, 10, piercing, 10, str\",\"Claw, 2, 6, slashing, 5, str\",\"Tail, 2, 8, bludgeoning, 15, str\"],\"player\":false,\"speed\":80,\"str_score\":23,\"turn\":false,\"unique_character_id\":\"3504ea90-413a-453b-969c-225153c4935e\",\"wis_score\":15},{\"ac\":15,\"cha_score\":8,\"challenge_score\":1,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":10,\"current_hp\":7,\"dex_score\":14,\"exp_given\":50,\"hp\":7,\"initiative\":0,\"int_score\":10,\"name\":\"Goblin\",\"npc_attack_buttons\":[\"Scimitar, 1, 6, slashing, 5, dex\",\"Shortbow, 1, 6, piercing, 80, dex\"],\"player\":false,\"speed\":30,\"str_score\":8,\"turn\":false,\"unique_character_id\":\"2191570b-249a-4150-8691-e0ac0ef6a8b4\",\"wis_score\":8}],\"players_list\":[{\"ac\":0,\"cha_score\":0,\"challenge_score\":0,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":0,\"current_hp\":0,\"dex_score\":0,\"exp_given\":0,\"hp\":0,\"initiative\":0,\"int_score\":0,\"name\":\"Player 1\",\"npc_attack_buttons\":[],\"player\":true,\"speed\":0,\"str_score\":0,\"turn\":false,\"unique_character_id\":\"62af54ec-8844-4778-9f21-4efa9b2dff67\",\"wis_score\":0},{\"ac\":0,\"cha_score\":0,\"challenge_score\":0,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":0,\"current_hp\":0,\"dex_score\":0,\"exp_given\":0,\"hp\":0,\"initiative\":0,\"int_score\":0,\"name\":\"Player 2\",\"npc_attack_buttons\":[],\"player\":true,\"speed\":0,\"str_score\":0,\"turn\":false,\"unique_character_id\":\"bc34c1b4-48a7-45b5-a0bc-522085c12334\",\"wis_score\":0},{\"ac\":0,\"cha_score\":0,\"challenge_score\":0,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":0,\"current_hp\":0,\"dex_score\":0,\"exp_given\":0,\"hp\":0,\"initiative\":0,\"int_score\":0,\"name\":\"Player 3\",\"npc_attack_buttons\":[],\"player\":true,\"speed\":0,\"str_score\":0,\"turn\":false,\"unique_character_id\":\"d703bcec-e37c-4c58-8aa4-02ec769be794\",\"wis_score\":0},{\"ac\":0,\"cha_score\":0,\"challenge_score\":0,\"character_x_coordinate\":0.0,\"character_y_coordinate\":0.0,\"con_score\":0,\"current_hp\":0,\"dex_score\":0,\"exp_given\":0,\"hp\":0,\"initiative\":0,\"int_score\":0,\"name\":\"Player 4\",\"npc_attack_buttons\":[],\"player\":true,\"speed\":0,\"str_score\":0,\"turn\":false,\"unique_character_id\":\"756f5a87-b618-4a58-aff4-49a57e1d3b43\",\"wis_score\":0}],\"round_number\":1,\"turn_number\":0}";
char REQUESTGMJSON[100] = "{\"action\":\"Request GM Information\"}";
char TURNORDERJSON[BUFFER_SIZE] = "{\"action\":\"Update Turn Order\",\"turnOrderCharacters\":[{\"initiative\":8,\"name\":\"Player 2\",\"turn\":true,\"unique_character_id\":\"eb2d4625-d69b-490d-993c-3ed8c9ffd5ba\"},{\"initiative\":6,\"name\":\"Goblin\",\"turn\":false,\"unique_character_id\":\"aba5f3c5-f232-49c1-b3cc-4f73b2920aa6\"},{\"initiative\":6,\"name\":\"Player 4\",\"turn\":false,\"unique_character_id\":\"bac66764-03cb-4e0e-99ac-0238ff5b40a4\"},{\"initiative\":2,\"name\":\"Adult Green Dragon\",\"turn\":false,\"unique_character_id\":\"936fe7b7-05db-4143-9fc5-8befaa8ffa44\"},{\"initiative\":2,\"name\":\"Player 3\",\"turn\":false,\"unique_character_id\":\"2216e1f7-2577-4070-8d70-27b2555d1bf0\"},{\"initiative\":1,\"name\":\"Player 1\",\"turn\":false,\"unique_character_id\":\"09ec269c-63b2-4a03-b94a-e7c864d48412\"}]}";
char CHARENDTURNJSON[BUFFER_SIZE] = "{ \"action\":\"Character End Turn\",\"bluetooth_id\":\"709bfaef-8ae2-438f-863d-cb61be639ba3\",\"unique_character_id\":\"ddfc8c0c-2771-4eeb-9cfe-d85886c4d369\"}";
char ACTIONJSON[BUFFER_SIZE/4] = "{\"action\":\"attack\",\"damage_roll\":8,\"damage_type\":\"Bludgeoning\",\"range\":50,\"character_x_coordinate\":8,\"character_y_coordinate\":38,\"bluetooth_id\":\"709bfaef-8ae2-438f-863d-cb61be639ba3\",\"unique_character_id\":\"ddfc8c0c-2771-4eeb-9cfe-d85886c4d369\"}";
char RESQUEST_CHARS[38] = "{ \"action\":\"Request All Characters\" }";
char MOVEXYJSON[BUFFER_SIZE/4] = "{\"action\":\"MoveXY\",\"character\":\"Player\"\"character_x_coordinate\":5,\"character_y_coordinate\":30,\"bluetooth_id\":\"709bfaef-8ae2-438f-863d-cb61be639ba3\",\"unique_character_id\":\"ddfc8c0c-2771-4eeb-9cfe-d85886c4d369\"}";
char MOVEJSON[BUFFER_SIZE/4] = "{\"action\":\"Move Character\",\t\"speed\":50,\"character_x_coordinate\":5,\"character_y_coordinate\":30,\"bluetooth_id\":\"709bfaef-8ae2-438f-863d-cb61be639ba3\",\"unique_character_id\":\"ddfc8c0c-2771-4eeb-9cfe-d85886c4d369\"}";
char UPDATECHARJSON[BUFFER_SIZE/4] = "{\"acrobatics\":false,\"action\":\"Update Character\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 1, 4, Bludgeoning, 5, false, str\"],\"bluetooth_id\":\"817b8dac-6a42-82a9-a782-98276f8c7952\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\t\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8801\",\"wis_proficiency\":false}";
char CREATECHARJSON[BUFFER_SIZE/4] = "{\"acrobatics\":false,\"action\":\"Create New Player\",\"animal_handling\":false,\"arcana\":false,\"athletics\":false,\"attack_buttons\":[\"Unarmed Strike, 1, 4, Bludgeoning, 5, false, str\"],\"bluetooth_id\":\"null\",\"cha_proficiency\":false,\"character_ac_total\":10,\"character_cha\":8,\"character_cha_mod\":-1,\"character_class\":\"Artificer\",\"character_con\":8,\"character_con_mod\":-1,\"character_current_hp\":7,\"character_dex\":10,\"character_dex_mod\":0,\"character_int\":8,\"character_int_mod\":-1,\"character_level\":1,\"character_max_hp\":7,\"character_name\":\"no_name\",\"character_proficiency\":2,\"character_race\":\"Aarakocra\",\"character_speed\":50,\"character_str\":8,\"character_str_mod\":-1,\"character_turn\":false,\"character_wis\":9,\"character_wis_mod\":-1,\"character_x_coordinate\":0,\"character_y_coordinate\":0,\"con_proficiency\":true,\"deception\":false,\"dex_proficiency\":false,\"history\":false,\"info_tab\":[\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"0\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"insight\":false,\"int_proficiency\":true,\"intimidation\":false,\"investigation\":false,\"medicine\":false,\"nature\":false,\"perception\":false,\"performance\":false,\"persuasion\":false,\"religion\":false,\"sleight_of_hand\":false,\"stealth\":false,\"str_proficiency\":false,\"survival\":false,\"unique_character_id\":\"201b5dac-3a16-46a6-a452-61301f4c8801\",\"wis_proficiency\":false}";

std::thread game_thread;
std::thread obj_thread;
//TuioClient *client;

// Main
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	init_Game();

	if (CreateMainWindow(hInstance) == -1)
	{
		int oldmode = game->Mode;
		MessageBoxA(NULL, "Something went wrong. Please restart the Game!", NULL, 0);
		game->Mode = oldmode;
		return -1;
	}
	
	// Begin the message loop
	MSG msg = { 0 };


	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// End the game thread
	game_thread.join();
	obj_thread.join();
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char teststring[BUFFER_SIZE] = "TESTING";
	wchar_t buffer[BUFFER_SIZE];
	wchar_t sent[BUFFER_SIZE];
	POINT pt;
	int error, result;
	std::string err_str, port_str;
	wchar_t* wide_string;
	size_t outsize;
	SOCKADDR_BTH* searchadd;
	DWORD searchadd_len;
	wchar_t wtext[BUFFER_SIZE] = { 0 };
	DWORD wtext_len = sizeof(wtext);
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rec;
	PWSTR file;
	std::string imagePath, newImgPath, savename;
	std::string::size_type i;
	std::wstring widestring;
	char savenamebuffer[260];
	char *tem;
	size_t found;
	int realindex;
	int oldmode;

;	switch (uMsg)
	{
	case WM_DPICHANGED:
	{
		RECT* const prcNewWindow = (RECT*)lParam;
		SetWindowPos(hWnd,
			NULL,
			prcNewWindow->left,
			prcNewWindow->top,
			prcNewWindow->right - prcNewWindow->left,
			prcNewWindow->bottom - prcNewWindow->top,
			SWP_NOZORDER | SWP_NOACTIVATE);
		break;
	}
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			switch (game->Mode)
			{
			case GAME_VIEW:
				if (!escflag)
				{
					game->Mode = PAUSE_MENU;
					game->display->PAUSE = true;
					CreatePauseScreen(hwnd);
					escflag = true;
				}

				else
				{
					game->Mode = GAME_VIEW;
					DestroyPauseScreen();
					escflag = false;
					game->display->PAUSE = false;
				}
				break;
			}
		}

		break;
	case WM_PAINT:
		break;
	case WM_LBUTTONDOWN:
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		game->Process_Point(pt.x, pt.y);
		//game->display->LoadImages("images/bmp/wilderness-map-current.bmp", &hImage, &image);
		//SendMessageW(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
		break;
	// Event handlers
	case WM_COMMAND:
		switch (wParam)
		{
			/* BUTTON LIST BLOCK */

		case DELETE_GAME_BUTTONS:
		case DELETE_GAME_BUTTONS + 1:
		case DELETE_GAME_BUTTONS + 2:
		case DELETE_GAME_BUTTONS + 3:
		case DELETE_GAME_BUTTONS + 4:
			GetDel(hwnd, wParam);
			break;

			// Character Buttons CURRENTLY NOT USED
		case CHLINK_BUTTONS:
		case CHLINK_BUTTONS + 1:
		case CHLINK_BUTTONS + 2:
		case CHLINK_BUTTONS + 3:
		case CHLINK_BUTTONS + 4:
			CharacterSelected = wParam - CHLINK_BUTTONS;
			if (ConnectedDeviceSelected != -1)
			{
				// Link
				LinkCharacter();
			}

			break;

			// Connected Device Buttons  CURRENTLY NOT USED
		case CLINK_BUTTONS:
		case CLINK_BUTTONS + 1:
		case CLINK_BUTTONS + 2:
		case CLINK_BUTTONS + 3:
		case CLINK_BUTTONS + 4:
			ConnectedDeviceSelected = wParam - CLINK_BUTTONS;
			if (CharacterSelected != -1)
			{
				// Link
				LinkCharacter();
			}

			break;

			// Load Game Buttons
		case LOAD_BUTTONS:
		case LOAD_BUTTONS + 1:
		case LOAD_BUTTONS + 2:
		case LOAD_BUTTONS + 3:
		case LOAD_BUTTONS + 4:
			// Check to see if button exists
			realindex = wParam - LOAD_BUTTONS + 5 * (DelGamePageNumber - 1);

			if (realindex + 1 > DelTile.size())
				break;
			// Signal that a saved game has been selected
			Load_Select_Flag = true;

			// Display the saved game 
			GetLoad(wParam, hwnd);
			break;

			// GM Select Buttons
		case GM_BUTTONS:
		case GM_BUTTONS + 1:
		case GM_BUTTONS + 2:
		case GM_BUTTONS + 3:
		case GM_BUTTONS + 4:
			// Check to see if button exists
			realindex = wParam - GM_BUTTONS;
			if (realindex + 1 > GMButtons.size())
				break;
			// Signal that a device has been selected as a GM
			GM_Select_Flag = true;

			// Display the choosen Device
			GetChoosenDevice(wParam, hwnd);
			break;

			/* PAUSE MENU  BLOCK */

			// Resume Game
		case RESUME_GAME:
			// Destroy pause menu
			DestroyPauseScreen();
			game->Mode = GAME_VIEW;
			// Reset the esc flag
			escflag = false;
			break;

			// Change map
		case CHANGE_MAP:
			// Display confimation dialog box
			oldmode = game->Mode;
			result = MessageBox(NULL, L"Are you sure you want to change the Map?", L"Change Map", MB_YESNO);
			game->Mode = oldmode;
			// If yes go to map selection screen else do nothing
			if (result == IDYES)
			{
				// Clean the current folder
				game->display->CleanCurrentFolder(game->CurrentMap, AppDataMainPath + GAMEIMAGEPATH + MAPIMAGES + CURRENTIMAGES);

				// Destroy old window
				DestroyGameView();

				// Destroy pause menu
				DestroyPauseScreen();

				// Create new window
				CreateChooseMapWindow(hwnd);

				// Change Mode to SELECT_MAP
				game->Mode = SELECT_MAP;

				// Reset the esc flag
				escflag = false;
			}
			else if (result == IDNO)
			{
				// Do nothing
			}

			break;

			// Return to Main Menu
		case MAIN_MENU_PAUSE:
			// Display confimation dialog box
			oldmode = game->Mode;
			result = MessageBox(NULL, L"Are you sure you want to return to the Main Menu?", L"", MB_YESNO);
			game->Mode = oldmode;
			// If yes
			if (result == IDYES)
			{
				// Ask to save
				oldmode = game->Mode;
				result = MessageBox(NULL, L"Would you like to save the game before you return to the Main Menu?", L"", MB_YESNOCANCEL);
				game->Mode = oldmode;

				// Only check for yes
				if (result == IDYES)
				{		
					game->mtx.lock();
					game->SAVE = true;
					game->RETURNFLAG = true;
					game->mtx.unlock();	

				}
				else if (result == IDCANCEL)
				{
					// If cancel, abort action
					break;
				}
				else if (result == IDNO)
				{
					// Dont save
					SendMessageW(hwnd, WM_COMMAND, RETURN, NULL);
				}
			}
			break;

			// Quit the Game to Desktop
		case QUIT_DESKTOP:
			// Display confimation dialog box
			oldmode = game->Mode;
			result = MessageBox(NULL, L"Are you sure you want to quit?", L"", MB_YESNO);
			game->Mode = oldmode;

			// If yes
			if (result == IDYES)
			{
				// Ask to save
				oldmode = game->Mode;
				result = MessageBox(NULL, L"Would you like to save the game before you quit?", L"", MB_YESNOCANCEL);
				game->Mode = oldmode;

				// Only check for yes
				if (result == IDYES)
				{
					// Save Game
					game->SAVE = true;
					game->EXIT = true;
				}
				else if (result == IDCANCEL)
				{
					// If cancel, abort action
					break;
				}
				else if (result == IDNO)
				{
					// Dont save
					SendMessageW(hwnd, WM_COMMAND, FILE_MENU_EXIT, NULL);
				}

			}
			break;

			/* REFRESH BLOCK */

			// Refresh for connected link devices
		case REFRESH_LINK:
			GenerateLinkConnected(hwnd);
			break;
			// Refresh for connected GM devices
		case REFRESH_GM:
			GenerateGMButtons(hwnd);
			break;
			// Refresh for already paired devices
		case REFRESH:
			DestroyWindow(nodevices);
			GenerateDeviceList(hwnd);
			break;

		/* HELPER BLOCK */

		case DEBUGGING:
			/*
				CURRENTLY USED FOR TESTIN
			*/
			DestroyOptionsMenu();
			DestroyMainMenu();
			CreateBluetoothView(hwnd);
			game->bluetooth->sendfunction = &sendfunction;
			game->bluetooth->sendfunctiontxt = &sendfunctiontxt;
			game->bluetooth->recvfunction = &recvfunction;
			game->bluetooth->recvfunctiontxt = &recvfunctiontxt;
			break;
		case DELETE_SAVE:
			//Mode = SAVE_DELETE;
			//DestroyMainMenu();
			//DestroyOptionsMenu();
			//CreateDeleteSave(hwnd);
			break;
		case RETURN_OPITONS:
			DestroyOptionsMenu();
			break;
		case NEXT_PAGE_DEL:
			//NextPageDel(hwnd);
			break;
		case PREV_PAGE_DEL:
			//PrevPageDel(hwnd);
			break;
		case NEXT_PAGE:
			NextPage(hwnd);
			break;
		case PREV_PAGE:
			PrevPage(hwnd);
			break;
		case SAVE_GAME:
			// Ask to save
			oldmode = game->Mode;
			result = MessageBox(NULL, L"Would you like to save the game?", L"", MB_YESNOCANCEL);
			game->Mode = oldmode;

			// Only check for yes
			if (result == IDYES)
			{
				game->SAVE = true;
			}
			else if (result == IDCANCEL)
			{
				// If cancel, abort action
				break;
			}
			else if (result == IDNO)
			{
				// Dont save
			}

			// Display notification that game was saved
			break;

		case OPEN_MAP:
			// Grab the path to the image selected
			game->Mode = OPEN_FILE;
			imagePath = std::string(OpenDialog2(game->PATHTOMAPIMAGES, hwnd));
			game->Mode = SELECT_MAP;

			// If the path is empty send error and break
			if (imagePath.compare("") == 0)
			{
				//result = MessageBox(NULL, L"No image was selected.", L"", MB_OK);

				// Explicilty set the flag to false
				MAP_Select_Flag = false;
				break;
			}

			found = imagePath.find(".");
			//MessageBoxA(NULL, imagePath.c_str(), NULL, 0);
			if (found == std::string::npos)
			{
				oldmode = game->Mode;
				result = MessageBox(NULL, L"Try selecting the map again.", L"", MB_OK);
				game->Mode = oldmode;

				// Explicilty set the flag to false
				MAP_Select_Flag = false;
				break;
			}

			// Signal that a map was selected
			MAP_Select_Flag = true;

			// Save original map to maps folder
			game->display->SaveOriginalMap(imagePath, game->APPDATAPATH + GAMEIMAGEPATH + MAPIMAGES + MAPS);

			// Create the preview of the map to show
			newImgPath = game->display->Create_Preview(imagePath, game->APPDATAPATH + GAMEIMAGEPATH + MAPIMAGES + PREVIEWIMAGES);

			// Display the preview
			image = (HBITMAP)LoadImageA(NULL, newImgPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			SendMessageW(mapselectwindow, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

			// convert the path to a wchar_t* to be saved
			widestring = std::wstring(imagePath.begin(), imagePath.end());
			MAPNAME = (wchar_t*)widestring.c_str();
			break;

		case LOAD_GAME:
			// Destroy the old window
			DestroyMainMenu();

			// Create the new window
			CreateLoadScreen(hwnd);

			// Change Mode to LOAD_SCREEN
			game->Mode = LOAD_SCREEN;
			break;

		case RETURN:
			// Clean the current folder
			game->display->CleanCurrentFolder(game->CurrentMap, AppDataMainPath + GAMEIMAGEPATH + MAPIMAGES + CURRENTIMAGES);
			//DestroyDeleteSave();
			DestroyPauseScreen();
			if (escflag)
				escflag = false;
			DestroyWindow(Load_Choosen);
			DestroyGameView();
			DestroyConnectWindow();
			DestroyBluetoothWindow();
			DestroyGMWindow();
			DestroyChooseMapWindow();
			DestroyLoadScreen();
			DestroyPlayerLinkScreen();
			CreateMainMenu(hwnd);
			game->mode = NOTLOADING;
			game->Mode = MAIN_MENU;
			break;

		case LOOKUP:
			Add_New_Devices();
			break;

			/* READY BUTTON BLOCK */

			// Play button on Main Menu
		case PLAY:
			// Set Game Name
			game->SetGameName();

			// Destroy the old window
			DestroyMainMenu();

			// Create the Pair Window
			CreateConnectWindow(hwnd);

			// Change the Mode to BTH_CONNECT
			game->Mode = BTH_CONNECT;
			break;

			// Ready on the Pair Screen
		case READY:
			// Destroy the old window
			DestroyConnectWindow();

			// Create the Choose GM window
			CreateChooseGMWindow(hwnd);

			// Change the Mode to GM_SELECT
			game->Mode = GM_SELECT;
			break;

			// Ready on the GM Select Screen
		case READY_GM:
			// Check if GM selected
			if (GM_Select_Flag)
			{
				// Set correct player to GM and continue
				game->players[GM_SELECTED_DEVICE]->set_GM();
				game->GM_Player = game->players[GM_SELECTED_DEVICE];
				//game->TESTINGCHARS();
			}
			// If GM is not selected send error and break
			else
			{
				oldmode = game->Mode;
				MessageBox(NULL, L"You must select a GM to continue!", L"", 0);
				game->Mode = oldmode;
				break;
			}

			// Destroy old window
			DestroyGMWindow();

			// Create select map window
			CreateChooseMapWindow(hwnd);

			// Change the Mode to SELECT_MAP
			game->Mode = SELECT_MAP;
			break;

			// Ready on Map Select
		case READY_MAP:
			// If no map is selected send error and break
			if (!MAP_Select_Flag)
			{
				oldmode = game->Mode;
				MessageBox(NULL, L"You must select a map to continue!", L"", 0);
				game->Mode = oldmode;
				break;
			}

			// Destroy old window
			DestroyChooseMapWindow();

			// Create Map View
			CreateGameView(hwnd, MAPNAME);

			// Change the Mode to GAME_VIEW
			game->Mode = GAME_VIEW;

			// Reset MAP_Select_Flag to avoid issues when changing map
			MAP_Select_Flag = false;
			break;

		// Ready on Load Screen
		case READY_LOAD:
			// If a save isnt selected, send an error and break
			if (!Load_Select_Flag)
			{
				oldmode = game->Mode;
				MessageBox(NULL, L"You must select a save file to continue!", L"", 0);
				game->Mode = oldmode;
				break;
			}

			// Determine the Save Game File Path
			savename = GameNames.at(LoadSelected);
			savename.copy(savenamebuffer, savename.size(), 11);

			// Load the Game
			game->Load_Game(savenamebuffer);

			// Destroy the old window
			DestroyLoadScreen();

			CreateGMSelectLoad(hwnd);

			game->Mode = GM_SELECT_LOAD;
			game->mode = LOADING;
			break;

		case READY_GM_LOAD:
			// Check if GM selected
			if (GM_Select_Flag)
			{
				// Set correct player to GM and continue
				game->players[GM_SELECTED_DEVICE]->set_GM();
				game->GM_Player = game->players[GM_SELECTED_DEVICE];
			}
			// If GM is not selected send error and break
			else
			{
				oldmode = game->Mode;
				MessageBox(NULL, L"You must select a GM to continue!", L"", 0);
				game->Mode = oldmode;
				break;
			}

			DestroyGMSelectLoad();

			// Create the new window
			if (MapNames.at(LoadSelected).compare((wchar_t *const)"No Map") == 0)
			{
				CreateChooseMapWindow(hwnd);
				
				// Change the Mode to GAME_VIEW
				game->Mode = SELECT_MAP;
			}				
			else
			{
				// Create the gameview 
				CreateGameView(hwnd, (wchar_t*)MapNames.at(LoadSelected).c_str());
				
				// Show activeNPCs
				game->display->ShowActiveNPCs(AppDataMainPath + GAMEDATAPATH + "logs.txt");

				// Change the Mode to GAME_VIEW
				game->Mode = GAME_VIEW;
			}

			break;
		// On exit, end the game and destroy the window
		case FILE_MENU_EXIT:
			// Clean the current folder
			game->display->CleanCurrentFolder(game->CurrentMap, AppDataMainPath + GAMEIMAGEPATH + MAPIMAGES + CURRENTIMAGES);
			game->stop();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			DestroyWindow(hwnd);
			free_images();
			WSACleanup();
			break;

		/* TESTING BLOCK */

		case FILE_MENU_NEW:
			MessageBox(NULL, L"FILE POPUP", L"File", 0);
			break;
		case ABOUT:
			MessageBox(NULL, L"Version 1.0", L"About", 0);
			break;
		case LOGIN:
			break;
		case SEND:
			memset(buffer, 0, BUFFER_SIZE);
			memset(sent, 0, BUFFER_SIZE);
			GetWindowText(hEdit, buffer, BUFFER_SIZE);
			wcstombs_s(&outsize, teststring, buffer, BUFFER_SIZE);
			game->bluetooth->SetSendBuffer(0, teststring);
			/*wcscat_s(sent, L"Sent: ");
			wcscat_s(sent, buffer);
			wcscat_s(sent, L"\r\n");
			wcscat_s(allsendbuffer, sent);
			SetWindowText(hEdit1, allsendbuffer);
			SetWindowText(hEdit, L"");*/
			break;
		case OPTIONS:
			//CreateOptionsMenu(hwnd);
			break;
		case TESTING:
			//game->display->display_NPC("C:Users//theka//AppData//Roaming//Gaming Wizard//Game Images//NPC Images//dragon2_white.png", 0);
			//// Create 1 NPC
			//game->Message_Handler(JSON_STRING, 0);
			//game->players[1] = new Player(1);
			//game->bluetooth->SocketsActive[1] = true;
			//game->Message_Handler(JSON_STRING2, 1);

			//// Place NPC
			//game->Message_Handler(MOVEXY_STRING, 0);

			//// See updated location
			//game->Message_Handler(RESQUEST_CHARS, 0);
			break;
		case UPDATE:	
			game->players[1] = new Player(1);
			game->bluetooth->SocketsActive[1] = true;
			game->Message_Handler(JSON_STRING2, 1);
			game->players[2] = new Player(2);
			game->bluetooth->SocketsActive[2] = true;
			game->Message_Handler(JSON_STRING3, 2);
			game->players[3] = new Player(3);
			game->bluetooth->SocketsActive[3] = true;
			game->Message_Handler(JSON_STRING4, 3);
			game->players[4] = new Player(4);
			game->bluetooth->SocketsActive[4] = true;
			game->Message_Handler(JSON_STRING5, 4);
			break;
		case SERVER1:
			game->SERVER = true;
			break;
		case CONNECT:
			game->CLIENT = true;
			break;

		}
		break;

	// On window creation
	case WM_CREATE:
		// On initial create, create the Main Menu
		CreateMainMenu(hwnd);

		// Set the Mode to Main Menu
		//game->Mode = MAIN_MENU;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;

	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

void init_Game()
{
	size_t outsize;
	char pathbuffer[MAXFILEPATHLENGTH];
	getenv_s(&outsize, pathbuffer, MAXFILEPATHLENGTH, "appdata");
	AppDataMainPath = std::string(pathbuffer);

	GM_Select_Flag = false;
	escflag = false;
	MAP_Select_Flag = false;

	game = new Game(&hWnd, &image, &hImage);
	game->bluetooth->scanDevices();

	ObjectDetector *listener = new ObjectDetector();
	game->client = new TuioClient(3333);
	game->client->addTuioListener(listener);
	game->client->connect();

	obj_thread = std::thread(&Game::ObjectDetection, game, listener);
	game_thread = std::thread(&Game::GameMain, game);	
	load_images();
}

int CreateMainWindow(HINSTANCE hInstance)
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

	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	int xCtr = (screenX / 2) - (1280 / 2);
	int yCtr = (screenY / 2) - (720 / 2);

	// Create a fullscreen window
	//hWnd = CreateWindowEx(NULL, wc.lpszClassName, L"Gaming Wizard", WS_POPUP | WS_VISIBLE, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, NULL, NULL, NULL, NULL);
	hWnd = CreateWindowEx(NULL, wc.lpszClassName, L"Gaming Wizard", WS_POPUP | WS_VISIBLE, xCtr, yCtr, 1280, 720, NULL, NULL, NULL, NULL);
	
	ChangeDisplaySettings(NULL, CDS_FULLSCREEN);

	return 0;
}

void CreateMainMenu(HWND hwnd)
{
	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());
	

	background = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	background_image = (HBITMAP)LoadImage(NULL, (wide + L"MainMenu.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)background_image);
	
	// Play Button
	play_button = CreateWindowEx(NULL, L"button", L"New Game", WS_VISIBLE | WS_CHILD | BS_FLAT | WS_BORDER, 90, 290, 300, 50, hwnd, HMENU(PLAY), NULL, NULL);
	//play_button = CreateWindowEx(NULL, L"button", NULL, WS_VISIBLE | WS_CHILD | BS_FLAT | BS_BITMAP | WS_BORDER, 95, 340, 300, 50, hwnd, HMENU(PLAY), NULL, NULL);
	//play_button_icon = (HBITMAP)LoadImage(NULL, L"images/game_images/play_button4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//SendMessageW(play_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)play_button_icon);

	load_button = CreateWindowEx(NULL, L"button", L"Load Game", WS_VISIBLE | WS_CHILD | BS_FLAT | WS_BORDER, 90, 350, 300, 50, hwnd, HMENU(LOAD_GAME), NULL, NULL);

	//ListBox_AddItemData(load_button, (LPARAM)play_button);

	//options_button = CreateWindowEx(NULL, L"button", L"Options", WS_VISIBLE | WS_CHILD | BS_FLAT | WS_BORDER, 90, 380, 300, 50, hwnd, HMENU(OPTIONS), NULL, NULL);

	// Quit Button
	quit_button = CreateWindowEx(NULL, L"button", L"Quit", WS_VISIBLE | WS_CHILD | BS_FLAT | WS_BORDER, 90, 410, 300, 50, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
	//quit_button = CreateWindowEx(NULL, L"button", NULL, WS_VISIBLE | WS_CHILD | BS_FLAT | BS_BITMAP | WS_BORDER, 95, 460, 300, 50, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
	//quit_button_image = (HBITMAP)LoadImage(NULL, L"images/game_images/quit_button.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//SendMessageW(quit_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)quit_button_image);
}

// Clear main menu window
void DestroyMainMenu()
{
	DestroyWindow(background);
	DestroyWindow(play_button);
	DestroyWindow(load_button);
	DestroyWindow(options_button);
	DestroyWindow(quit_button);
}

void CreateConnectWindow(HWND hwnd)
{
	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());

	background = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	background_connect_image = (HBITMAP)LoadImage(NULL, (wide + L"PairScreen.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)background_connect_image);
	
	//device_button = CreateWindowEx(NULL, L"button", L"Your Devices", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 145, 500, 50, hwnd, NULL, NULL, NULL);
	//device_button = CreateWindowEx(NULL, L"button", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | BS_BITMAP, 20, 145, 500, 50, hwnd, NULL, NULL, NULL);
	//SendMessageW(device_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)device_button_image);
	
	// Refresh button
	refresh_button = CreateWindowEx(NULL, L"button", L"Refresh", WS_VISIBLE | WS_CHILD | WS_BORDER, 980, 220, 260, 50, hwnd, HMENU(REFRESH), NULL, NULL);
	//refresh_button = CreateWindowEx(NULL, L"button", L"Refresh", WS_VISIBLE | WS_CHILD | WS_BORDER | BS_BITMAP, 960, 145, 300, 50, hwnd, HMENU(REFRESH), NULL, NULL);
	//SendMessageW(refresh_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)refresh_button_image);

	// Ready Button
	ready_button = CreateWindowEx(NULL, L"button", L"Ready", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 630, 260, 50, hwnd, HMENU(READY), NULL, NULL);
	//ready_button = CreateWindowEx(NULL, L"button", L"Ready", WS_VISIBLE | WS_CHILD | WS_BORDER | BS_BITMAP, 660, 655, 300, 50, hwnd, HMENU(READY), NULL, NULL);
	//SendMessageW(ready_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ready_button_image);

	// Quit Button
	//quit_button = CreateWindowEx(NULL, L"button", L"Quit", WS_VISIBLE | WS_CHILD | WS_BORDER, 960, 630, 300, 50, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
	//quit_button = CreateWindowEx(NULL, L"button", L"Quit", WS_VISIBLE | WS_CHILD | BS_FLAT | BS_BITMAP | WS_BORDER, 960, 655, 300, 50, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
	//SendMessageW(quit_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)quit_button_image);

	// Look-up button
	lookup_button = CreateWindowEx(NULL, L"button", L"Add New Device", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 220, 260, 50, hwnd, HMENU(LOOKUP), NULL, NULL);
	//lookup_button = CreateWindowEx(NULL, L"button", L"Add New Device", WS_VISIBLE | WS_CHILD | BS_BITMAP | WS_BORDER, 650, 145, 300, 50, hwnd, HMENU(LOOKUP), NULL, NULL);
	//SendMessageW(lookup_button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)pair_button_image);

	// Return to main menu
	return_button = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 980, 630, 260, 50, hwnd, HMENU(RETURN), NULL, NULL);
	//return_button = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 655, 300, 50, hwnd, HMENU(RETURN), NULL, NULL);
	
	// Look for and display devices in bluetooth range
	GenerateDeviceList(hwnd);
}

void DestroyConnectWindow()
{
	DestroyWindow(background);
	//background_image = nullptr;
	DestroyWindow(refresh_button);
	//refresh_button_image = nullptr;
	DestroyWindow(ready_button);
	//ready_button_image = nullptr;
	DestroyWindow(lookup_button);
	//pair_button_image = nullptr;
	DestroyWindow(device_button);
	DestroyWindow(return_button);
	DestroyWindow(quit_button);
	//device_button_image = nullptr;
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
	//HWND scanloading = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 490, 310, 300, 100, hwnd, NULL, NULL, NULL);
	//SendMessageW(scanloading, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)scan_image);

	//// Scan for devices
	//std::thread scan(&scan);
	//
	//// While the game is scanning for devices display a scanning window
	//while (game->bluetooth->scanning_status == SCANNING_STARTED)
	//{
	//	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	//	SendMessageW(scanloading, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)scan_image1);
	//	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	//	SendMessageW(scanloading, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)scan_image2);
	//	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	//	SendMessageW(scanloading, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)scan_image3);
	//	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	//	SendMessageW(scanloading, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)scan_image);
	//}

	// After all devices have been found, destroy scanning window and display devices
	//DestroyWindow(scanloading);
	//60, 75 + i * 121, 560, 104,
	int i = 0;
	if (game->bluetooth->device_list.empty())
	{
		nodevices = CreateWindowEx(NULL, L"static", L"\nNo devices found. Enable Bluetooth on your device and refresh.", WS_VISIBLE | WS_CHILD | SS_LEFT, 60, 75, 560, 64, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
	}
	else
	{
		for (BLUETOOTH_DEVICE_INFO device : game->bluetooth->device_list)
		{
			std::wstring device_name = device.szName;
			//ConnectDeviceNames[i] = device_name;
			SYSTEMTIME time = device.stLastUsed;
			wchar_t timestring[20];
			wchar_t datestring[20];
			GetTimeFormatEx(nullptr, 0, &time, L"hh':'mm':'ss tt", timestring, 20);
			GetDateFormatEx(nullptr, 0, &time, L"MM'/'dd'/'yy' ", datestring, 20, nullptr);
			std::wstring button_string = L"\n\tDevice Name: " + device_name + L"\n\tLast Seen: " + datestring + timestring;

			device_buttons.insert(device_buttons.begin(), CreateWindowExA(NULL, "static", std::string(button_string.begin(), button_string.end()).c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 60, 75 + i * 75, 560, 64, hwnd, NULL, NULL, NULL));
			i++;
		}
	}
	//scan.join();
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
void CreateGameView(HWND hwnd, wchar_t *mapname)
{
	std::string preparemap = game->display->PrepareMap(mapname, AppDataMainPath + GAMEIMAGEPATH + MAPIMAGES + CURRENTIMAGES, AppDataMainPath);
	game->Set_Map_Name(preparemap);
	hImage = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	image = (HBITMAP)LoadImageA(NULL, preparemap.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

	//CreateWindowEx(NULL, L"button", L"Exit", WS_VISIBLE | WS_CHILD | WS_BORDER, 1820, 980, 100, 100, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);
	//CreateWindowEx(NULL, L"button", L"Move NPC", WS_VISIBLE | WS_CHILD | WS_BORDER, 1620, 980, 100, 100, hwnd, HMENU(TESTING), NULL, NULL);
	//CreateWindowEx(NULL, L"button", L"Display New", WS_VISIBLE | WS_CHILD | WS_BORDER, 1720, 980, 100, 100, hwnd, HMENU(UPDATE), NULL, NULL);
}

void DestroyGameView()
{
	DestroyWindow(hImage);
}

void CreateBluetoothView(HWND hwnd)
{
	// Create window for send tasks

	// Create window to type in for send
	wchar_t connected_name[1024] = L"Connected Device Name: ";
	wchar_t connected_add[1024] = L"Connected Device Address: ";


	// Get device socket
	SOCKADDR_BTH device;
	int device_len = sizeof(device);
	wchar_t wtext[512];
	DWORD buff_len = sizeof(wtext);
	game->bluetooth->Get_Socket_Info(game->bluetooth->SocketsArray[CLIENT_START_INDEX], &device);
	WSAAddressToString((LPSOCKADDR)&device, (DWORD)device_len, NULL, wtext, &buff_len);
	std::wstring device_name = L"";
	// Find matching device and get name
	for (BLUETOOTH_DEVICE_INFO device1 : game->bluetooth->device_list)
	{
		if (device.btAddr == device1.Address.ullLong)
			device_name = device1.szName;
	}

	// Create strings
	if (device_name != L"")
	{
		wcscat_s(connected_name, device_name.c_str());
		wcscat_s(connected_add, wtext);
	}
	conn_name = CreateWindowEx(NULL, L"Static", connected_name, WS_VISIBLE | WS_CHILD, 20, 50, 400, 20, hwnd, NULL, NULL, NULL);
	conn_add = CreateWindowEx(NULL, L"Static", connected_add, WS_VISIBLE | WS_CHILD, 20, 70, 400, 20, hwnd, NULL, NULL, NULL);

	sendtext = CreateWindowEx(NULL, L"Static", L"Enter text to send", WS_VISIBLE | WS_CHILD, 20, 100, 400, 15, hwnd, NULL, NULL, NULL);
	hEdit = CreateWindowEx(NULL, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 120, 400, 50, hwnd, NULL, NULL, NULL);
	sendbutton = CreateWindowEx(NULL, L"button", L"Send", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 175, 400, 25, hwnd, HMENU(SEND), NULL, NULL);

	// Create window for recieve tasks
	textsend = CreateWindowEx(NULL, L"Static", L"Text Sent", WS_VISIBLE | WS_CHILD, 440, 100, 400, 15, hwnd, NULL, NULL, NULL);
	hEdit1 = CreateWindowEx(NULL, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 440, 120, 400, 500, hwnd, NULL, NULL, NULL);
	
	receivetext = CreateWindowEx(NULL, L"Static", L"Text Received", WS_VISIBLE | WS_CHILD, 860, 100, 400, 15, hwnd, NULL, NULL, NULL);
	hEdit2 = CreateWindowEx(NULL, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 860, 120, 400, 500, hwnd, NULL, NULL, NULL);
	//SetWindowText();
	// Create status window

	game->bluetooth->ERRORFLAG = true;
	// Create window for recieve tasks
	sendfunction = CreateWindowEx(NULL, L"Static", L"Send Function", WS_VISIBLE | WS_CHILD, 1280, 100, 400, 15, hwnd, NULL, NULL, NULL);
	sendfunctiontxt = CreateWindowEx(NULL, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 1280, 120, 400, 200, hwnd, NULL, NULL, NULL);

	recvfunction = CreateWindowEx(NULL, L"Static", L"Recv Function", WS_VISIBLE | WS_CHILD, 1280, 330, 400, 15, hwnd, NULL, NULL, NULL);
	recvfunctiontxt = CreateWindowEx(NULL, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 1280, 350, 400, 200, hwnd, NULL, NULL, NULL);


	// Quit Button
	quit_button = CreateWindowEx(NULL, L"button", L"Quit", WS_VISIBLE | WS_CHILD | WS_BORDER, 960, 655, 300, 50, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);

	// Return to main menu
	return_button = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 655, 300, 50, hwnd, HMENU(RETURN), NULL, NULL);

	// Return to main menu
	//connectbutton = CreateWindowEx(NULL, L"button", L"Connect", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 210, 400, 25, hwnd, HMENU(CONNECT), NULL, NULL);

	// Return to main menu
	//HWND serverbutton = CreateWindowEx(NULL, L"button", L"Be Server", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 245, 400, 25, hwnd, HMENU(SERVER1), NULL, NULL);
}

void DestroyBluetoothWindow() 
{
	DestroyWindow(conn_name);
	DestroyWindow(conn_add);
	DestroyWindow(sendtext);
	DestroyWindow(hEdit);
	DestroyWindow(sendbutton);
	DestroyWindow(textsend);
	DestroyWindow(hEdit1);
	DestroyWindow(receivetext);
	DestroyWindow(hEdit2);
	DestroyWindow(quit_button);
	DestroyWindow(return_button);
	//DestroyWindow(connectbutton);
}

void StartGame()
{
	game->bluetooth->scanDevices();

	//game->bluetooth->listen_test();
	//game->bluetooth->Bluetooth_Start_Up();
	//game->GameMain(&hEdit2, allrecvbuffer, &conn_add, &conn_name);
	return;
}

void load_images()
{
	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());
}

void free_images()
{
	background_image = nullptr;
	play_button_icon = nullptr;
	options_button_image = nullptr;
	quit_button_image = nullptr;
	background_image = nullptr;
	device_button_image = nullptr;
	refresh_button_image = nullptr;
	ready_button_image = nullptr;
	scan_image = nullptr;
	scan_image1 = nullptr;
	scan_image2 = nullptr;
	scan_image3 = nullptr;
}

void Add_New_Devices()
{
	
	game->bluetooth->devices = new BLUETOOTH_DEVICE_INFO[game->bluetooth->device_list.size()];
	int i = 0;
	for (i = 0; i < game->bluetooth->device_list.size(); i++)
		game->bluetooth->devices[i] = game->bluetooth->device_list.at(i);

	BLUETOOTH_SELECT_DEVICE_PARAMS params;
	params.dwSize = sizeof(params);
	params.cNumOfClasses = 0;
	params.fForceAuthentication = true;
	params.fShowAuthenticated = true;
	params.fShowRemembered = true;
	params.fShowUnknown = true;
	params.fAddNewDeviceWizard = true;
	params.fSkipServicesPage = false;
	params.pfnDeviceCallback = &PfnDeviceCallback;
	params.hwndParent = hWnd;
	params.pvParam = NULL;
	params.cNumDevices = 0;
	params.pDevices = game->bluetooth->devices;

	bool result;
	result = BluetoothSelectDevices(&params);
	std::ofstream myfile;
	myfile.open("trythis.txt");
	if (result)
		myfile << result << std::endl;
	else
		myfile << GetLastError() << std::endl;
	myfile.close();
}

BOOL CALLBACK PfnDeviceCallback(LPVOID pvParam, const BLUETOOTH_DEVICE_INFO *pDevice)
{
	return true;
}

void GenerateGMButtons(HWND hwnd)
{
	// Clear old buttons
	if (!GMButtons.empty())
	{
		for (int i = 0; i < GMButtons.size(); i++)
		{
			DestroyWindow(GMButtons.at(i));
		}
	}

	while (!GMButtons.empty())
		GMButtons.pop_back();

	// Create new buttons
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		// If the socket is active, create a button
		if (game->bluetooth->SocketsActive[i])
		{
			// Get strings needed for button
			SOCKADDR_BTH device;
			int device_len = sizeof(device);
			wchar_t wtext[1024];
			DWORD buff_len = sizeof(wtext);
			game->bluetooth->Get_Socket_Info(game->bluetooth->SocketsArray[CLIENT_START_INDEX+i], &device);
			WSAAddressToString((LPSOCKADDR)&device, (DWORD)device_len, NULL, wtext, &buff_len);
			std::wstring device_name;
			BLUETOOTH_DEVICE_INFO active_device;
			for (BLUETOOTH_DEVICE_INFO device1 : game->bluetooth->device_list)
			{
				if (device.btAddr == device1.Address.ullLong)
				{
					active_device = device1;
					break;
				}
			}
			device_name = active_device.szName;
			ConnectDeviceNames[i] = device_name;
			SYSTEMTIME time = active_device.stLastUsed;
			wchar_t timestring[20];
			GetTimeFormatEx(nullptr, 0, &time, L"hh':'mm':'ss tt\n", timestring, 20);
			std::wstring button_string = L"Device Name: " + device_name; // +L"\nLast Seen: " + timestring;
			// Create the string
			GMButtons.push_back(CreateWindowEx(NULL, L"button", button_string.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_LEFT | BS_MULTILINE, 60, 75 + i * 121, 560, 104, hwnd, HMENU(GM_BUTTONS + i), NULL, NULL));
		}
		// Used for testing
		//GMButtons[i] = CreateWindowEx(NULL, L"button", L"Device Name: Alpha\nLast Seen: 1:29 PM", WS_VISIBLE | WS_CHILD | WS_BORDER | BS_LEFT | BS_MULTILINE, 60, 75 + i * 121, 560, 104, hwnd, HMENU(GM_BUTTONS + i), NULL, NULL);
	}
}

void CreateGMSelectLoad(HWND hwnd)
{
	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());

	background = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	background_image = (HBITMAP)LoadImage(NULL, (wide + L"GMScreen.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)background_image);

	container = CreateWindowEx(NULL, L"static", L"", WS_CHILD | WS_BORDER, 40, 40, 600, 640, hwnd, NULL, NULL, NULL);
	//HWND Title = CreateWindowEx(NULL, L"static", L"Choose a Game Master", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 40, 560, 70, hwnd, NULL, NULL, NULL);
	//HWND Instructions = CreateWindowEx(NULL, L"static", L"Select GM from connected devices.\nIf you don't see your device, connect and refresh", WS_VISIBLE | WS_CHILD, 680, 110, 560, 70, hwnd, NULL, NULL, NULL);
	//HWND Device_Choosen = CreateWindowEx(NULL, L"static", L"Device Choosen", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 180, 560, 100, hwnd, NULL, NULL, NULL);

	GenerateGMButtons(hwnd);

	// How to dynamically change button text -- Need BS_MULTILINE to use '\n' 
	//SetWindowText(but1, L"TESTING\nTESTING2");

	// How to disable the button
	//SetWindowLongPtrA(but3, GWL_STYLE, WS_DISABLED);

	// Ready Button
	ready_button = CreateWindowEx(NULL, L"button", L"Ready", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 630, 170, 50, hwnd, HMENU(READY_GM_LOAD), NULL, NULL);

	// Refresh Connected Device List
	refresh_button = CreateWindowEx(NULL, L"button", L"Refresh", WS_VISIBLE | WS_CHILD | WS_BORDER, 875, 630, 170, 50, hwnd, HMENU(REFRESH_GM), NULL, NULL);

	// Return to main menu
	return_button = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 1070, 630, 170, 50, hwnd, HMENU(RETURN), NULL, NULL);

	// Quit Button
	//quit_button = CreateWindowEx(NULL, L"button", L"Quit", WS_VISIBLE | WS_CHILD | WS_BORDER, 1070, 630, 170, 50, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);

	// Create a list from connected devices, should update on new connections
	// On button select, make all other buttons unclickable
	// Click ready to select the device, set that device's player as GM
}

void CreateChooseGMWindow(HWND hwnd)
{
	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());

	background = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	background_image = (HBITMAP)LoadImage(NULL, (wide + L"GMScreen.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)background_image);

	container = CreateWindowEx(NULL, L"static", L"", WS_CHILD | WS_BORDER, 40, 40, 600, 640, hwnd, NULL, NULL, NULL);
	//HWND Title = CreateWindowEx(NULL, L"static", L"Choose a Game Master", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 40, 560, 70, hwnd, NULL, NULL, NULL);
	//HWND Instructions = CreateWindowEx(NULL, L"static", L"Select GM from connected devices.\nIf you don't see your device, connect and refresh", WS_VISIBLE | WS_CHILD, 680, 110, 560, 70, hwnd, NULL, NULL, NULL);
	//HWND Device_Choosen = CreateWindowEx(NULL, L"static", L"Device Choosen", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 180, 560, 100, hwnd, NULL, NULL, NULL);

	GenerateGMButtons(hwnd);

	// How to dynamically change button text -- Need BS_MULTILINE to use '\n' 
	//SetWindowText(but1, L"TESTING\nTESTING2");

	// How to disable the button
	//SetWindowLongPtrA(but3, GWL_STYLE, WS_DISABLED);

	// Ready Button
	ready_button = CreateWindowEx(NULL, L"button", L"Ready", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 630, 170, 50, hwnd, HMENU(READY_GM), NULL, NULL);

	// Refresh Connected Device List
	refresh_button = CreateWindowEx(NULL, L"button", L"Refresh", WS_VISIBLE | WS_CHILD | WS_BORDER, 875, 630, 170, 50, hwnd, HMENU(REFRESH_GM), NULL, NULL);

	// Return to main menu
	return_button = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 1070, 630, 170, 50, hwnd, HMENU(RETURN), NULL, NULL);

	// Quit Button
	//quit_button = CreateWindowEx(NULL, L"button", L"Quit", WS_VISIBLE | WS_CHILD | WS_BORDER, 1070, 630, 170, 50, hwnd, HMENU(FILE_MENU_EXIT), NULL, NULL);

	// Create a list from connected devices, should update on new connections
	// On button select, make all other buttons unclickable
	// Click ready to select the device, set that device's player as GM
}

void GetChoosenDevice(int index, HWND hwnd)
{
	int realindex = index - GM_BUTTONS;
	GM_SELECTED_DEVICE = realindex;
	DestroyWindow(Device_Choosen);
	// Create the string
	Device_Choosen = CreateWindowEx(NULL, L"static", ConnectDeviceNames[realindex].c_str(), WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE, 860, 272, 200, 30, hwnd, NULL, NULL, NULL);
}

void DestroyChooseMapWindow()
{
	DestroyWindow(background);
	DestroyWindow(mapselectwindow);
	DestroyWindow(open_button);
	DestroyWindow(ready_button);
	DestroyWindow(return_button);
}

void DestroyGMSelectLoad()
{
	DestroyWindow(background);
	DestroyWindow(container);
	DestroyWindow(ready_button);
	DestroyWindow(refresh_button);
	DestroyWindow(return_button);
	DestroyWindow(Device_Choosen);
	for (int i = 0; i < MAX_PLAYERS; i++)
		DestroyWindow(GMButtons[i]);
}

void CreateChooseMapWindow(HWND hwnd)
{
	game->CurrentMap = "None Selected";
	game->display->OriginalFileExtension = "No Map";

	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());

	background = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	background_image = (HBITMAP)LoadImage(NULL, (wide + L"MapPreview.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)background_image);

	// Map Preview
	mapselectwindow = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 40, 191, 600, 338, hwnd, NULL, NULL, NULL);

	// Ready Button
	ready_button = CreateWindowEx(NULL, L"button", L"Ready", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 630, 160, 50, hwnd, HMENU(READY_MAP), NULL, NULL);

	// Quit Button
	open_button = CreateWindowEx(NULL, L"button", L"Open Map", WS_VISIBLE | WS_CHILD | WS_BORDER, 880, 630, 160, 50, hwnd, HMENU(OPEN_MAP), NULL, NULL);

	// Return to main menu
	return_button = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 1080, 630, 160, 50, hwnd, HMENU(RETURN), NULL, NULL);
}

void DestroyGMWindow()
{
	DestroyWindow(background);
	DestroyWindow(container);
	DestroyWindow(ready_button);
	DestroyWindow(refresh_button);
	DestroyWindow(return_button);
	DestroyWindow(Device_Choosen);
	if(!GMButtons.empty())
		for (int i = 0; i < MAX_PLAYERS; i++)
			DestroyWindow(GMButtons[i]);
}

void CreatePauseScreen(HWND hwnd)
{
	// Create small window center of visible display
	pausemenu  = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 585, 270, 170, 300, hwnd, NULL, NULL, NULL);

	// Resume game button
	resumebutton = CreateWindowEx(NULL, L"button", L"Resume Game", WS_VISIBLE | WS_CHILD | WS_BORDER, 590, 275, 160, 50, hwnd, HMENU(RESUME_GAME), NULL, NULL);

	// Save game button
	savegamebutton = CreateWindowEx(NULL, L"button", L"Save Game", WS_VISIBLE | WS_CHILD | WS_BORDER, 590, 335, 160, 50, hwnd, HMENU(SAVE_GAME), NULL, NULL);

	// Change map button
	changemapbutton = CreateWindowEx(NULL, L"button", L"Change Map", WS_VISIBLE | WS_CHILD | WS_BORDER, 590, 395, 160, 50, hwnd, HMENU(CHANGE_MAP), NULL, NULL);

	// Main Menu button
	pausemainmenu = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 590, 455, 160, 50, hwnd, HMENU(MAIN_MENU_PAUSE), NULL, NULL);

	// Quit button
	qtdbutton = CreateWindowEx(NULL, L"button", L"Quit To Desktop", WS_VISIBLE | WS_CHILD | WS_BORDER, 590, 515, 160, 50, hwnd, HMENU(QUIT_DESKTOP), NULL, NULL);
}

void DestroyPauseScreen()
{
	DestroyWindow(pausemenu);
	DestroyWindow(resumebutton);
	DestroyWindow(savegamebutton);
	DestroyWindow(changemapbutton);
	DestroyWindow(pausemainmenu);
	DestroyWindow(qtdbutton);
}

void GenerateLoadButtons2(HWND hwnd)
{
	while (!MapNames.empty())
		MapNames.pop_back();

	// Open file with info
	std::ifstream Savesfile;
	Savesfile.open(game->SAVESINFOOLD, std::ifstream::in);

	std::string name, time, players, encounter, mapname, mapurl, button_string;


	// Generate all buttons
	for(int i = 0; i < 6; i++)
	{
		// Pseudo Mod function
		if (i == 5)
			i = 0;

		// Grab the current 
		if (!std::getline(Savesfile, name))
		{
			break;
		}
		
		std::getline(Savesfile, time);
		std::getline(Savesfile, players);
		std::getline(Savesfile, encounter);
		std::getline(Savesfile, mapname);
		std::getline(Savesfile, mapurl);

		// Create button string
		button_string = name + "\n" + time + "\n" + players + "\n" + encounter + "\n" + mapname;

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(button_string);

		// Only create a max of 5 buttons
		if(LoadGameButtons.size() < 5)
			LoadGameButtons.push_back(CreateWindowEx(NULL, L"static", wide.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_LEFT | BS_MULTILINE, 60, 75 + i * 115, 560, 100, hwnd, HMENU(LOAD_BUTTONS + i), NULL, NULL));
		
		GameNames.push_back(name);
		MapNames.push_back(converter.from_bytes(mapurl));
		LoadTile.push_back(wide);
	}
}

void CreateLoadScreen2(HWND hwnd)
{
	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());

	background = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	background_image = (HBITMAP)LoadImage(NULL, (wide + L"LoadScreen.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)background_image);

	container = CreateWindowEx(NULL, L"static", L"", WS_CHILD | WS_BORDER, 40, 40, 600, 640, hwnd, NULL, NULL, NULL);
	//HWND Title = CreateWindowEx(NULL, L"static", L"Choose a Game Master", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 40, 560, 70, hwnd, NULL, NULL, NULL);
	//HWND Instructions = CreateWindowEx(NULL, L"static", L"Select GM from connected devices.\nIf you don't see your device, connect and refresh", WS_VISIBLE | WS_CHILD, 680, 110, 560, 70, hwnd, NULL, NULL, NULL);
	//HWND Device_Choosen = CreateWindowEx(NULL, L"static", L"Device Choosen", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 180, 560, 100, hwnd, NULL, NULL, NULL);

	//GenerateLoadButtons(hwnd);
	
	// If no save games, 0/0 else default to 1/x
	LoadGamePageNumber = (LoadGameButtons.size() == 0) ? 0 : 1;

	nextpage = CreateWindowEx(NULL, L"static", L"Next\nPage", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 370, 640, 80, 35, hwnd, NULL, NULL, NULL);
	pages = CreateWindowEx(NULL, L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE, 325, 640, 40, 35, hwnd, NULL, NULL, NULL);
	prevpage = CreateWindowEx(NULL, L"static", L"Previous\nPage", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 240, 640, 80, 35, hwnd, NULL, NULL, NULL);	

	// Set the text for the pages
	SetLoadPageNumber();

	// How to dynamically change button text -- Need BS_MULTILINE to use '\n' 
	//SetWindowText(but1, L"TESTING\nTESTING2");

	// How to disable the button.
	//SetWindowLongPtrA(but3, GWL_STYLE, WS_DISABLED);

	// Ready Button
	ready_button = CreateWindowEx(NULL, L"button", L"Ready", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 630, 270, 50, hwnd, HMENU(READY_LOAD), NULL, NULL);

	// Return to main menu
	return_button = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 970, 630, 270, 50, hwnd, HMENU(RETURN), NULL, NULL);
}

void SetLoadPageNumber2()
{
	// Determine the number of pages
	if (LoadTile.size() == 0)
		LoadNumPages = 0;
	else
	{
		if (LoadTile.size() % 5 == 0)
			LoadNumPages = LoadTile.size() / 5;
		else
			LoadNumPages = LoadTile.size() / 5 + 1;
	}

	// Create the wchar_t* for the number of pages
	wchar_t widepages[256];
	swprintf_s(widepages, L"%d/%d", LoadGamePageNumber, LoadNumPages);

	SetWindowText(pages, widepages);
}

void DestroyLoadScreen2()
{
	// Clear lists first
	while (!LoadTile.empty())
		LoadTile.pop_back();

	while (!GameNames.empty())
		GameNames.pop_back();

	DestroyWindow(background);
	DestroyWindow(container);
	DestroyWindow(nextpage);
	DestroyWindow(pages);
	DestroyWindow(prevpage);
	DestroyWindow(ready_button);
	DestroyWindow(refresh_button);
	DestroyWindow(return_button);
	DestroyWindow(Load_Choosen);
	for (HWND button : LoadGameButtons)
	{
		DestroyWindow(button);
	}

	while (LoadGameButtons.size() > 0)
		LoadGameButtons.pop_back();

}

void GetLoad(int index, HWND hwnd)
{
	LoadSelected = index - LOAD_BUTTONS + 5 * (DelGamePageNumber - 1);
	DestroyWindow(Load_Choosen);
	Load_Choosen = CreateWindowEx(NULL, L"static", DelTile.at(LoadSelected).c_str(), WS_VISIBLE | WS_CHILD, 780, 163, 360, 66, hwnd, NULL, NULL, NULL);
}

void GenerateLinkConnected(HWND hwnd)
{
	// Get all the connected devices
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		// If the socket is active, create a button
		if (game->bluetooth->SocketsActive[i])
		{
			// Get strings needed for button
			SOCKADDR_BTH device;
			int device_len = sizeof(device);
			wchar_t wtext[1024];
			DWORD buff_len = sizeof(wtext);
			game->bluetooth->Get_Socket_Info(game->bluetooth->SocketsArray[CLIENT_START_INDEX + i], &device);
			WSAAddressToString((LPSOCKADDR)&device, (DWORD)device_len, NULL, wtext, &buff_len);
			std::wstring device_name;
			BLUETOOTH_DEVICE_INFO active_device;
			for (BLUETOOTH_DEVICE_INFO device1 : game->bluetooth->device_list)
			{
				if (device.btAddr == device1.Address.ullLong)
				{
					active_device = device1;
					break;
				}
			}
			device_name = active_device.szName;
			ConnectDeviceNames[i] = device_name;
			SYSTEMTIME time = active_device.stLastUsed;
			wchar_t timestring[20];
			GetTimeFormatEx(nullptr, 0, &time, L"hh':'mm':'ss tt\n", timestring, 20);
			std::wstring button_string = L"Device Name: " + device_name; // +L"\nLast Seen: " + timestring;
			// Create the string
			GMButtons[i] = CreateWindowEx(NULL, L"button", button_string.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_LEFT | BS_MULTILINE, 50, 75 + i * 115, 260, 100, hwnd, HMENU(CLINK_BUTTONS + i), NULL, NULL);
		}
	}
}

void CreatePlayerLinkScreen(HWND hwnd)
{
	ConnectedDeviceSelected = -1;
	CharacterSelected = -1;

	LoadGameButtons.push_back(CreateWindowEx(NULL, L"button", L"GM", WS_VISIBLE | WS_CHILD | WS_BORDER | BS_LEFT | BS_MULTILINE, 370, 75, 260, 100, hwnd, HMENU(CHLINK_BUTTONS), NULL, NULL));
	GenerateLinkConnected(hwnd);

	int i = 1;
	for (json player : game->LoadedPlayers)
	{
		// Create button string
		std::string characterinfo = "Character Name: " + player["character_name"].get<std::string>() + "\n" + "Character Race: " + player["character_race"].get<std::string>() + "\n" + "Current HP: " + std::to_string(player["character_current_hp"].get<int>());

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(characterinfo);

		// Create buttons for this
		LoadGameButtons.push_back(CreateWindowEx(NULL, L"button", wide.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | BS_LEFT | BS_MULTILINE, 370, 75 + i * 115, 260, 100, hwnd, HMENU(CHLINK_BUTTONS + i), NULL, NULL));
		i++;
	}

	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());

	background = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	background_image = (HBITMAP)LoadImage(NULL, (wide + L"LinkScreen.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)background_image);

	container = CreateWindowEx(NULL, L"static", L"", WS_CHILD | WS_BORDER, 40, 40, 600, 640, hwnd, NULL, NULL, NULL);

	// Ready Button
	ready_button = CreateWindowEx(NULL, L"button", L"Ready", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 630, 170, 50, hwnd, HMENU(READY_LINK), NULL, NULL);

	// Refresh Connected Device List
	refresh_button = CreateWindowEx(NULL, L"button", L"Refresh", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 640, 80, 35, hwnd, HMENU(REFRESH_LINK), NULL, NULL);

	// Return to main menu
	return_button = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 1070, 630, 170, 50, hwnd, HMENU(RETURN), NULL, NULL);

	// Link display
	linkdisplay = CreateWindowEx(NULL, L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 690, 224, 540, 85, hwnd, NULL, NULL, NULL);

}

void DestroyPlayerLinkScreen()
{
	DestroyWindow(background);
	DestroyWindow(container);
	DestroyWindow(ready_button);
	DestroyWindow(refresh_button);
	DestroyWindow(return_button);
	DestroyWindow(linkdisplay);
	
	// Clear link display and reset values to default
	wlink = L"";
	ConnectedDeviceSelected = -1;
	CharacterSelected = -1;

	for (HWND button : LoadGameButtons)
	{
		DestroyWindow(button);
	}

	while (LoadGameButtons.size() > 0)
		LoadGameButtons.pop_back();
}

void LinkCharacter()
{
	std::string links;

	// Link players
	// If the option selected is GM
	if (CharacterSelected == 0)
	{
		game->players[ConnectedDeviceSelected]->set_GM();
		links = " Playing as GM";
	}
	// Else normal player
	else
	{
		game->players[ConnectedDeviceSelected]->playerattributes = game->LoadedPlayers[CharacterSelected];
		links = " Playing as " + game->LoadedPlayers[CharacterSelected]["character_name"].get<std::string>();
	}

	wlink = wlink + L"\n" + ConnectDeviceNames[ConnectedDeviceSelected];

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes(links);

	wlink = wlink + wide;

	// Display Link
	SetWindowText(linkdisplay, wlink.c_str());

	// Disable buttons
	SetWindowLongPtrA(GMButtons[ConnectedDeviceSelected], GWL_STYLE, WS_DISABLED);
	SetWindowLongPtrA(LoadGameButtons.at(CharacterSelected), GWL_STYLE, WS_DISABLED);

	// Reset the selected values
	ConnectedDeviceSelected = -1;
	CharacterSelected = -1;
}

void NextPage2(HWND hwnd)
{
	// Can not go beyond the max page
	if (LoadGamePageNumber + 1 > LoadNumPages)
		return;

	// Change the page number
	LoadGamePageNumber++;
	SetLoadPageNumber();

	// Grab the next 5 or less tiles
	for (int i = 0; i < 5; i++)
	{
		if (((LoadGamePageNumber - 1) * 5 + i) < LoadTile.size())
			SetWindowText(LoadGameButtons.at(i), LoadTile.at((LoadGamePageNumber - 1) * 5 + i).c_str());
		else
			ShowWindow(LoadGameButtons.at(i), SW_HIDE);
	}

	UpdateWindow(hwnd);
}

void PrevPage2(HWND hwnd)
{
	// Can not go to page 0
	if (LoadGamePageNumber <= 1)
		return;

	// Change the page number
	LoadGamePageNumber = LoadGamePageNumber - 1;
	SetLoadPageNumber();

	// Grab the previous 5 tiles
	for (int i = 0; i < 5; i++)
	{
		if (((LoadGamePageNumber - 1) * 5 + i) < LoadTile.size())
		{
			// Set Window Text
			SetWindowText(LoadGameButtons.at(i), LoadTile.at((LoadGamePageNumber - 1) * 5 + i).c_str());

			// Guarentee that the button is visible
			ShowWindow(LoadGameButtons.at(i), SW_SHOW);
		}

	}

	UpdateWindow(hwnd);
}

//void GenerateDeleteSaveTiles(HWND hwnd, std::wstring filepath)
void GenerateLoadButtons(HWND hwnd, std::wstring filepath)
{
	// Clear lists first
	while (!DelTile.empty())
		DelTile.pop_back();

	while (!DelTileSave.empty())
		DelTileSave.pop_back();

	while (!MapNames.empty())
		MapNames.pop_back();

	while (!MapNamesSave.empty())
		MapNamesSave.pop_back();

	while (!FileNames.empty())
		FileNames.pop_back();

	while (!DeleteGameButtons.empty())
		DeleteGameButtons.pop_back();

	while (!DeleteGameXs.empty())
		DeleteGameXs.pop_back();

	// Open file with info
	std::ifstream Savesfile;
	Savesfile.open(game->SAVESINFOOLD, std::ifstream::in);

	std::string name, time, players, encounter, mapname, mapurl, button_string;
	HBITMAP textx_image = (HBITMAP)LoadImage(NULL, (filepath + L"redx.bmp").c_str(), IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);

	// Generate all buttons
	for (int i = 0; i < 6; i++)
	{
		// Pseudo Mod function
		if (i == 5)
			i = 0;

		// Grab the current 
		if (!std::getline(Savesfile, name))
		{
			break;
		}

		std::getline(Savesfile, time);
		std::getline(Savesfile, players);
		std::getline(Savesfile, encounter);
		std::getline(Savesfile, mapname);
		std::getline(Savesfile, mapurl);

		// Create button string
		button_string = name + "\n" + time + "\n" + players + "\n" + encounter + "\n" + mapname;

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(button_string);

		// Only create a max of 5 buttons
		if (DeleteGameButtons.size() < 5)
		{
			DeleteGameButtons.push_back(CreateWindowEx(NULL, L"static", wide.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER, 60, 75 + i * 115, 560, 100, hwnd, HMENU(LOAD_BUTTONS + i), NULL, NULL));
			DeleteGameXs.push_back(CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 500, 30, 40, 40, DeleteGameButtons.at(i), NULL, NULL, NULL));
			SendMessageW(DeleteGameXs.at(i), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)textx_image);

			BringWindowToTop(DeleteGameXs.at(i));
			// Guarentee that the button is visible		
			ShowWindow(DeleteGameXs.at(i), SW_SHOW);
			ShowWindow(DeleteGameButtons.at(i), SW_SHOW);
			UpdateWindow(hwnd);
		}
		DelTileSave.push_back(button_string);
		DelTile.push_back(wide);
		GameNames.push_back(name);
		MapNames.push_back(converter.from_bytes(mapurl));
		MapNamesSave.push_back(mapurl);
		FileNames.push_back(name);
	}
	UpdateWindow(hwnd);
}

void CreateOptionsMenu(HWND hwnd)
{
	// Create small window center of visible display
	optionsmenu = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 585, 270, 170, 300, hwnd, NULL, NULL, NULL);

	// Create button for debugging
	debuggingbutton = CreateWindowEx(NULL, L"button", L"Debugging", WS_VISIBLE | WS_CHILD | WS_BORDER, 590, 275, 160, 50, hwnd, HMENU(DEBUGGING), NULL, NULL);

	// Create button to delete save games
	deletesavesbutton = CreateWindowEx(NULL, L"button", L"Manage Saves", WS_VISIBLE | WS_CHILD | WS_BORDER, 590, 335, 160, 50, hwnd, HMENU(DELETE_SAVE), NULL, NULL);

	// Main Menu button
	optionsreturnbutton = CreateWindowEx(NULL, L"button", L"Return", WS_VISIBLE | WS_CHILD | WS_BORDER, 590, 455, 160, 50, hwnd, HMENU(RETURN_OPITONS), NULL, NULL);
}

void DestroyOptionsMenu()
{
	DestroyWindow(optionsmenu);
	DestroyWindow(debuggingbutton);
	DestroyWindow(deletesavesbutton);
	DestroyWindow(optionsreturnbutton);
}

//void CreateDeleteSave(HWND hwnd)
void CreateLoadScreen(HWND hwnd)
{
	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());

	container = CreateWindowEx(NULL, L"static", L"", WS_CHILD | WS_BORDER, 40, 40, 600, 640, hwnd, NULL, NULL, NULL);
	//HWND Title = CreateWindowEx(NULL, L"static", L"Choose a Game Master", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 40, 560, 70, hwnd, NULL, NULL, NULL);
	//HWND Instructions = CreateWindowEx(NULL, L"static", L"Select GM from connected devices.\nIf you don't see your device, connect and refresh", WS_VISIBLE | WS_CHILD, 680, 110, 560, 70, hwnd, NULL, NULL, NULL);
	//HWND Device_Choosen = CreateWindowEx(NULL, L"static", L"Device Choosen", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 180, 560, 100, hwnd, NULL, NULL, NULL);

	//GenerateDeleteSaveTiles(hwnd, wide);
	GenerateLoadButtons(hwnd, wide);

	// If no save games, 0/0 else default to 1/x
	DelGamePageNumber = (DeleteGameButtons.size() == 0) ? 0 : 1;

	nextpage = CreateWindowEx(NULL, L"static", L"Next\nPage", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 370, 640, 80, 35, hwnd, NULL, NULL, NULL);
	pages = CreateWindowEx(NULL, L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE, 325, 640, 40, 35, hwnd, NULL, NULL, NULL);
	prevpage = CreateWindowEx(NULL, L"static", L"Previous\nPage", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 240, 640, 80, 35, hwnd, NULL, NULL, NULL);

	// Set the text for the pages
	//SetDelPageNumber();
	SetLoadPageNumber();

	// How to dynamically change button text -- Need BS_MULTILINE to use '\n' 
	//SetWindowText(but1, L"TESTING\nTESTING2");

	// How to disable the button.
	//SetWindowLongPtrA(but3, GWL_STYLE, WS_DISABLED);

	// Ready Button
	ready_button = CreateWindowEx(NULL, L"button", L"Ready", WS_VISIBLE | WS_CHILD | WS_BORDER, 680, 630, 270, 50, hwnd, HMENU(READY_LOAD), NULL, NULL);

	// Return to main menu
	return_button = CreateWindowEx(NULL, L"button", L"Main Menu", WS_VISIBLE | WS_CHILD | WS_BORDER, 970, 630, 270, 50, hwnd, HMENU(RETURN), NULL, NULL);

	background = CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 1280, 720, hwnd, NULL, NULL, NULL);
	background_image = (HBITMAP)LoadImage(NULL, (wide + L"LoadScreen.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SendMessageW(background, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)background_image);
}

//void DestroyDeleteSave()
void DestroyLoadScreen()
{
	// Clear lists first
	while (!DelTile.empty())
		DelTile.pop_back();

	while (!DelTileSave.empty())
		DelTileSave.pop_back();

	while (!MapNamesSave.empty())
		MapNamesSave.pop_back();

	while (!FileNames.empty())
		FileNames.pop_back();

	for (int i = 0; i < DeleteGameButtons.size(); i++)
		DestroyWindow(DeleteGameButtons.at(i));

	while (!DeleteGameButtons.empty())
		DeleteGameButtons.pop_back();

	for (int i = 0; i < DeleteGameButtons.size(); i++)
		DestroyWindow(DeleteGameButtons.at(i));

	while (!DeleteGameXs.empty())
		DeleteGameXs.pop_back();

	DestroyWindow(ready_button);
	DestroyWindow(Load_Choosen);
	DestroyWindow(background);
	DestroyWindow(return_button);
	DestroyWindow(prevpage);
	DestroyWindow(pages);
	DestroyWindow(nextpage);
	DestroyWindow(container);
}

//void NextPageDel(HWND hwnd)
void NextPage(HWND hwnd)
{
	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());
	HBITMAP textx_image = (HBITMAP)LoadImage(NULL, (wide + L"redx.bmp").c_str(), IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);

	// Can not go beyond the max page
	if (DelGamePageNumber + 1 > DelNumPages)
		return;

	while(!DeleteGameXs.empty())
		DeleteGameXs.pop_back();

	// Change the page number
	DelGamePageNumber++;
	//SetDelPageNumber();
	SetLoadPageNumber();

	// Grab the next 5 or less tiles
	for (int i = 0; i < 5; i++)
	{
		if (((DelGamePageNumber - 1) * 5 + i) < DelTile.size())
		{
			SetWindowText(DeleteGameButtons.at(i), DelTile.at((DelGamePageNumber - 1) * 5 + i).c_str());

			DeleteGameXs.push_back(CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 500, 30, 40, 40, DeleteGameButtons.at(i), NULL, NULL, NULL));
			SendMessageW(DeleteGameXs.at(i), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)textx_image);

			ShowWindow(DeleteGameXs.at(i), SW_SHOW);
		}
		else
			ShowWindow(DeleteGameButtons.at(i), SW_HIDE);
	}

	UpdateWindow(hwnd);
}

//void PrevPageDel(HWND hwnd)
void PrevPage(HWND hwnd)
{
	std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
	std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());
	HBITMAP textx_image = (HBITMAP)LoadImage(NULL, (wide + L"redx.bmp").c_str(), IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);

	// Can not go to page 0
	if (DelGamePageNumber <= 1)
		return;

	while (!DeleteGameXs.empty())
		DeleteGameXs.pop_back();

	// Change the page number
	DelGamePageNumber = DelGamePageNumber - 1;
	//SetDelPageNumber();
	SetLoadPageNumber();
	
	// Grab the previous 5 tiles
	for (int i = 0; i < 5; i++)
	{
		if (((DelGamePageNumber - 1) * 5 + i) < DelTile.size())
		{
			// Set Window Text
			SetWindowText(DeleteGameButtons.at(i), DelTile.at((DelGamePageNumber - 1) * 5 + i).c_str());

			DeleteGameXs.push_back(CreateWindowEx(NULL, L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 500, 30, 40, 40, DeleteGameButtons.at(i), NULL, NULL, NULL));
			SendMessageW(DeleteGameXs.at(i), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)textx_image);

			// Guarentee that the button is visible		
			ShowWindow(DeleteGameXs.at(i), SW_SHOW);
			ShowWindow(DeleteGameButtons.at(i), SW_SHOW);
		}
	}

	UpdateWindow(hwnd);
}

//void SetDelPageNumber()
void SetLoadPageNumber()
{
	// Determine the number of pages
	if (DelTile.size() == 0)
		DelNumPages = 0;
	else
	{
		if (DelTile.size() % 5 == 0)
			DelNumPages = DelTile.size() / 5;
		else
			DelNumPages = DelTile.size() / 5 + 1;
	}

	// Create the wchar_t* for the number of pages
	wchar_t widepages[256];
	swprintf_s(widepages, L"%d/%d", DelGamePageNumber, DelNumPages);

	SetWindowText(pages, widepages);
}

void GetDel(HWND hwnd, int index)
{
	DelSelected = index - DELETE_GAME_BUTTONS + 5 * (DelGamePageNumber - 1);

	if (DelSelected + 1 > DelTile.size())
		return;

	int oldmode = game->Mode;
	int result = MessageBoxA(NULL, "Are you sure you want to delete this save file?", "", MB_YESNO);
	Mode = oldmode;

	if (result == IDYES)
	{
		std::string UIBASEPATH = AppDataMainPath + GAMEIMAGEPATH + UIIMAGES;
		std::wstring wide = std::wstring(UIBASEPATH.begin(), UIBASEPATH.end());

		// Delete the tile
		DelTile.erase(DelTile.begin() + DelSelected);
		DelTileSave.erase(DelTileSave.begin() + DelSelected);
		MapNames.erase(MapNames.begin() + DelSelected);
		MapNamesSave.erase(MapNamesSave.begin() + DelSelected);

		char savenamebuffer[100];
		FileNames.at(DelSelected).copy(savenamebuffer, FileNames.at(DelSelected).size(), 11);

		// Delete the file
		remove((AppDataMainPath + GAMEDATAPATH + savenamebuffer + ".game").c_str());

		// Update the save info file
		UpdateSaveInfoFile(wide);

		// Refresh the list
		//GenerateDeleteSaveTiles(hwnd, wide);
		DestroyLoadScreen();
		DestroyWindow(Load_Choosen);
		CreateLoadScreen(hwnd);
		//DestroyDeleteSave();
		//CreateDeleteSave(hwnd);
	}
	else if (result == IDNO)
	{
		// Do nothing
	}

	return;
}

void UpdateSaveInfoFile(std::wstring filename)
{
	// Open file with info
	std::ofstream Savesfile;
	Savesfile.open(game->SAVESINFONEW.c_str(), std::ofstream::out);

	// Loop over DelTile and save to save info
	for (int i = 0; i < DelTileSave.size(); i++)
	{
		Savesfile << DelTileSave.at(i).c_str() << "\n" << MapNamesSave.at(i).c_str() << std::endl;
	}

	Savesfile.close();

	remove(game->SAVESINFOOLD.c_str());
	rename(game->SAVESINFONEW.c_str(), game->SAVESINFOOLD.c_str());
}