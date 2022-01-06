#include "pch.h"

#include <nlohmann/json.hpp>

#include <ws2bth.h>
#include <bthsdpdef.h>
#include <BluetoothAPIs.h>

#pragma comment(lib, "bthprops.lib")

// for convenience
using json = nlohmann::json;

#define WRONG_DEVICE 0
#define PLAYER_ATTRIBUTES_SET 1

typedef struct _Attacked {
	int damage_roll;
	std::string damage_type;
	std::string bth_id;
	std::string unique_id;
	BOOL used;
} Attacked, *LPAttacked;

typedef struct _Encounter {
	std::string EncounterName;
} Encounter, *LPEncounter;

typedef struct _NPC {
	int character_x_coordinate;
	int character_y_coordinate;
	std::string unique_character_id;
} NPC_STRUCT, *LPNPC_STRUCT;

#pragma once
class Player
{
private:
	int location;
	std::string filename;
	BOOL GM;
	SOCKADDR_BTH BTH_ID;
	std::string ID; // BT Address
	int SocketIndex; 

	// Player, NPC Attributes
	int current_hp;
	std::string unique_character_id;
	int character_x_coordinate, character_y_coordinate;
	
	// Player only attributes
	std::string character_name, character_race, character_class,  bluetooth_id;
	int character_level, character_ac_total, character_max_hp, character_current_hp, character_proficiency;
	int character_str, character_str_mod, character_dex, character_dex_mod, character_con, character_con_mod;
	int character_int, character_int_mod, character_wis, character_wis_mod, character_cha, character_cha_mod;
	int character_speed;
	BOOL str_proficiency, dex_proficiency, con_proficiency, int_proficiency, wis_proficiency, cha_proficiency, acrobatics;
	BOOL animal_handling, arcana, athletics, deception, history, insight, intimidation, investigation, medicine, nature;
	BOOL perception, performance, persuasion, religion, sleight_of_hand, stealth, survival, character_turn;
	std::vector<std::string> attack_buttons, info_tab;


	// NPC only attributes
	std::string name;
	int hp;
	int ac;
	int speed;
	int str_score;
	int dex_score;
	int con_score;
	int int_score;
	int wis_score;
	int cha_score;
	int challenge_score;
	int exp_given;
	std::vector<std::string> npc_attack_buttons;
	BOOL player;
	int initiative;
	BOOL turn;
	
	// GM attributes
	std::string action;
	int turn_number, round_number;
	Encounter encounter_selected;
	std::vector<std::string> maps_list, info_tab_gm;
	std::vector<Player *> npcs_list, players_list;
	std::vector<Encounter> encounters_list;


public:
	bool initiatesave;
	bool saved;
	bool alive;

	json playerattributes;

	Player();
	Player(int index);
	Player(int location, std::string filename);
	Player(SOCKADDR_BTH ID, int index);
	Player(std::string ID, int index, SOCKADDR_BTH BID);
	int get_location();
	void set_location(int newLocation);
	std::string get_filename();
	void set_filename(std::string newFilename);
	BOOL set_GM();
	BOOL is_GM();
	std::string get_ID();
	int get_index();
	void set_index(int index);
	int Create_Player(json attributes);
	int Update_Player(json attributes);
	static json Dump_Player_Attributes(Player *player);
	SOCKADDR_BTH get_bth_id();
	void UpdateNPC(json attributes);


	// Getters and Setters

	void set_name(std::string name);
	std::string get_name();
	void set_hp (int hp);
	int get_hp();
	void set_ac(int ac);
	int get_ac();
	void set_speed(int speed);
	int get_speed();
	void set_str_score(int str_score);
	int get_str_score();
	void set_dex_score(int dex_score);
	int get_dex_score();
	void set_con_score(int con_score);
	int get_con_score();
	void set_int_score(int int_score);
	int get_int_score();
	void set_wis_score(int wis_score);
	int get_wis_score();
	void set_cha_score(int cha_score);
	int get_cha_score();
	void set_challenge_score(int challenge_score);
	int get_challenge_score();
	void set_exp_given(int exp_given);
	int get_exp_given();
	void set_npc_attack_buttons(std::vector<std::string> npc_attack_buttons);
	std::vector<std::string> get_npc_attack_buttons();
	void set_player(BOOL player);
	BOOL get_player();
	void set_initiative(int initiative);
	int get_initiative();
	void set_turn(BOOL turn);
	BOOL get_turn();

	std::string get_action();
	void set_action(std::string action);
	std::string get_character_name();
	void set_character_name(std::string charcter_name);
	std::string	get_character_race();
	void set_character_race(std::string character_race);
	std::string	get_character_class();
	void set_character_class(std::string	character_class);
	std::string	get_unique_character_id();
	void set_unique_character_id(std::string unique_character_id);
	std::string	get_bluetooth_id();
	void set_bluetooth_id(std::string bluetooth_id);
	int get_character_level();
	void set_character_level(int character_level);
	int	get_character_ac_total();
	void set_character_ac_total(int character_ac_total);
	int get_character_max_hp();
	void set_character_max_hp(int character_max_hp);
	int get_character_current_hp();
	void set_character_current_hp(int current_hp);
	int get_character_proficiency();
	void set_character_proficiency(int character_proficiency);
	int get_character_str();
	void set_character_str(int character_str);
	int get_character_str_mod();
	void set_character_str_mod(int character_str_mod);
	int get_character_dex();
	void set_character_dex(int character_dex);
	int get_character_dex_mod();
	void set_character_dex_mod(int character_dex_mod);
	int get_character_con();
	void set_character_con(int character_con);
	int get_character_con_mod();
	void set_character_con_mod(int character_con_mod);
	int get_character_int();
	void set_character_int(int character_int);
	int get_character_int_mod();
	void set_character_int_mod(int character_int_mod);
	int get_character_wis();
	void set_character_wis(int character_wis);
	int get_character_wis_mod();
	void set_character_wis_mod(int character_wis_mod);
	int get_character_cha();
	void set_character_cha(int character_cha);
	int get_character_cha_mod();
	void set_character_cha_mod(int character_cha_mod);
	int get_character_speed();
	void set_character_speed(int character_speed);
	int get_current_hp();
	void set_current_hp(int current_hp);
	BOOL get_str_proficiency();
	void set_str_proficiency(BOOL str_proficiency);
	BOOL get_dex_proficiency();
	void set_dex_proficiency(BOOL dex_proficiency);
	BOOL get_con_proficiency();
	void set_con_proficiency(BOOL con_proficiency);
	BOOL get_int_proficiency();
	void set_int_proficiency(BOOL int_proficiency);
	BOOL get_wis_proficiency();
	void set_wis_proficiency(BOOL wis_proficiency);
	BOOL get_cha_proficiency();
	void set_cha_proficiency(BOOL cha_proficiency);
	BOOL get_acrobatics();
	void set_acrobatics(BOOL acrobatics);
	BOOL get_animal_handling();
	void set_animal_handling(BOOL animal_handling);
	BOOL get_arcana();
	void set_arcana(BOOL arcana);
	BOOL get_athletics();
	void set_athletics(BOOL athletics);
	BOOL get_deception();
	void set_deception(BOOL deception);
	BOOL get_history();
	void set_history(BOOL history);
	BOOL get_insight();
	void set_insight(BOOL insight);
	BOOL get_intimidation();
	void set_intimidation(BOOL intimidation);
	BOOL get_investigation();
	void set_investigation(BOOL investigation);
	BOOL get_medicine();
	void set_medicine(BOOL medicine);
	BOOL get_nature();
	void set_nature(BOOL nature);
	BOOL get_perception();
	void set_perception(BOOL perception);
	BOOL get_performance();
	void set_performance(BOOL performance);
	BOOL get_persuasion();
	void set_persuasion(BOOL persuasion);
	BOOL get_religion();
	void set_religion(BOOL religion);
	BOOL get_sleight_of_hand();
	void set_sleight_of_hand(BOOL sleight_of_hand);
	BOOL get_stealth();
	void set_stealth(BOOL stealth);
	BOOL get_survival();
	void set_survival(BOOL survival);
	BOOL get_character_turn();
	void set_character_turn(BOOL character_turn);
	std::vector<std::string> get_attack_buttons();
	void set_attack_buttons(std::vector<std::string> attack_buttons);
	std::vector<std::string> get_info_tab();
	void set_info_tab(std::vector<std::string> info_tab);
	int get_character_x_coordinate();
	void set_character_x_coordinate(int character_x_coordinate);
	int get_character_y_coordinate();
	void set_character_y_coordinate(int character_y_coordinate);
};
