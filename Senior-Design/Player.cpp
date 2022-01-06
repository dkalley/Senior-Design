#include "pch.h"
#include "Player.h"

Player::Player()
{
	this->GM = false;
	this->initiatesave = false;
	this->saved = false;
}

Player::Player(int index)
{
	this->GM = false;
	this->SocketIndex = index;
	this->initiatesave = false;
	this->saved = false;
}

// Constructor for NPC
Player::Player(int location, std::string filename)
{
	this->location = location;
	this->filename = filename;
	this->GM = false;
	this->initiatesave = false;
	this->saved = false;
}

// Constructor for Player
Player::Player(SOCKADDR_BTH ID, int index)
{
	this->BTH_ID = ID;
	this->SocketIndex = index;
	// Initialize, will be chosen later
	this->GM = false;
	this->initiatesave = false;
	this->saved = false;
}

// Constructor for Player
Player::Player(std::string ID, int index, SOCKADDR_BTH BID)
{
	this->BTH_ID = BID;
	this->ID = ID;
	this->SocketIndex = index;
	// Initialize, will be chosen later
	this->GM = false;
	this->initiatesave = false;
	this->saved = false;
}
SOCKADDR_BTH Player::get_bth_id()
{
	return this->BTH_ID;
}

std::string Player::get_action()
{
	return this->action;
}
void  Player::set_action(std::string action)
{
	this->action = action;
}
int Player::get_location()
{
	return this->location;
}
void Player::set_location(int newLocation)
{
	this->location = newLocation;
}
std::string Player::get_filename()
{
	return this->filename;
}
void Player::set_filename(std::string newFilename)
{
	this->filename = newFilename;
}
BOOL Player::set_GM()
{
	this->GM = true;
	return this->GM;
}
BOOL Player::is_GM()
{
	return this->GM;
}
std::string Player::get_ID()
{
	return this->ID;
}
int Player::get_index()
{
	return this->SocketIndex;
}
void Player::set_index(int index)
{
	this->SocketIndex = index;
	return;
}

int Player::Create_Player(json attributes)
{
	this->playerattributes = attributes;
	return PLAYER_ATTRIBUTES_SET;
}

int Player::Update_Player(json attributes)
{
	this->playerattributes = nullptr;
	this->playerattributes = attributes;
	return PLAYER_ATTRIBUTES_SET;
}

json Player::Dump_Player_Attributes(Player *player)
{
	return player->playerattributes;
}

void Player::UpdateNPC(json attributes)
{
	this->set_ac(attributes["ac"].get<int>());
	this->set_cha_score(attributes["cha_score"].get<int>());
	this->set_challenge_score(attributes["challenge_score"].get<int>());
	this->set_character_x_coordinate(attributes["character_x_coordinate"].get<int>());
	this->set_character_y_coordinate(attributes["character_y_coordinate"].get<int>());
	this->set_con_score(attributes["con_score"].get<int>());
	this->set_current_hp(attributes["current_hp"].get<int>());
	this->set_dex_score(attributes["dex_score"].get<int>());
	this->set_exp_given(attributes["exp_given"].get<int>());
	this->set_hp(attributes["hp"].get<int>());
	this->set_initiative(attributes["initiative"].get<int>());
	this->set_int_score(attributes["int_score"].get<int>());
	this->set_name(attributes["name"].get<std::string>());
	this->set_npc_attack_buttons(attributes["npc_attack_buttons"].get<std::vector<std::string>>());
	this->set_player(attributes["player"].get<BOOL>());
	this->set_speed(attributes["speed"].get<int>());
	this->set_str_score(attributes["str_score"].get<int>());
	this->set_turn(attributes["turn"].get<BOOL>());
	this->set_unique_character_id(attributes["unique_character_id"].get<std::string>());
	this->set_wis_score(attributes["wis_score"].get<int>());
	return;
}

void Player::set_name(std::string name)
{
	this->name = name;
}
std::string Player::get_name()
{
	return this->name;
}
void Player::set_hp(int hp)
{
	this->hp = hp;
}
int Player::get_hp()
{
	return this->hp;
}
void Player::set_ac(int ac)
{
	this->ac = ac;
}
int Player::get_ac()
{
	return this->ac;
}
void Player::set_speed(int speed)
{
	this->speed = speed;
}
int Player::get_speed()
{
	return this->speed;
}
void Player::set_str_score(int str_score)
{
	this->str_score = str_score;
}
int Player::get_str_score()
{
	return this->str_score;
}
void Player::set_dex_score(int dex_score)
{
	this->dex_score = dex_score;
}
int Player::get_dex_score()
{
	return this->dex_score;
}
void Player::set_con_score(int con_score)
{
	this->con_score = con_score;
}
int Player::get_con_score()
{
	return this->con_score;
}
void Player::set_int_score(int int_score)
{
	this->int_score = int_score;
}
int Player::get_int_score()
{
	return this->int_score;
}
void Player::set_wis_score(int wis_score)
{
	this->wis_score = wis_score;
}
int Player::get_wis_score()
{
	return this->wis_score;
}
void Player::set_cha_score(int cha_score)
{
	this->cha_score = cha_score;
}
int Player::get_cha_score()
{
	return this->cha_score;
}
void Player::set_challenge_score(int challenge_score)
{
	this->challenge_score = challenge_score;
}
int Player::get_challenge_score()
{
	return this->challenge_score;
}
void Player::set_exp_given(int exp_given)
{
	this->exp_given = exp_given;
}
int Player::get_exp_given()
{
	return this->exp_given;
}
void Player::set_npc_attack_buttons(std::vector<std::string> npc_attack_buttons)
{
	this->npc_attack_buttons = npc_attack_buttons;
}
std::vector<std::string> Player::get_npc_attack_buttons()
{
	return this->npc_attack_buttons;
}
void Player::set_player(BOOL player)
{
	this->player = player;
}
BOOL Player::get_player()
{
	return this->player;
}
void Player::set_initiative(int initiative)
{
	this->initiative = initiative;
}
int Player::get_initiative()
{
	return this->initiative;
}
void Player::set_turn(BOOL turn)
{
	this->turn = turn;
}
BOOL Player::get_turn()
{
	return this->turn;
}


std::string Player::get_character_name()
{
	return this->character_name;
}
void Player::set_character_name(std::string character_name)
{
	this->character_name = character_name;
}
std::string	Player::get_character_race()
{
	return this->character_race;
}
void Player::set_character_race(std::string character_race)
{
	this->character_race = character_race;
}
std::string	Player::get_character_class()
{
	return this->character_class;
}
void Player::set_character_class(std::string	character_class)
{
	this->character_class = character_class;
}
std::string	Player::get_unique_character_id()
{
	return this->unique_character_id;
}
void Player::set_unique_character_id(std::string unique_character_id)
{
	this->unique_character_id = unique_character_id;
}
std::string	Player::get_bluetooth_id()
{
	return this->bluetooth_id;
}
void Player::set_bluetooth_id(std::string bluetooth_id)
{
	this->bluetooth_id = bluetooth_id;
}
int Player::get_character_level()
{
	return this->character_level;
}
void Player::set_character_level(int character_level)
{
	this->character_level = character_level;
}
int	Player::get_character_ac_total()
{
	return this->character_ac_total;
}
void Player::set_character_ac_total(int character_ac_total)
{
	this->character_ac_total = character_ac_total;
}
int Player::get_character_max_hp()
{
	return this->character_max_hp;
}
void Player::set_character_max_hp(int character_max_hp)
{
	this->character_max_hp = character_max_hp;
}
int Player::get_character_current_hp()
{
	return this->character_current_hp;
}
void Player::set_character_current_hp(int current_hp)
{
	this->character_current_hp = current_hp;
}
int Player::get_character_proficiency()
{
	return this->character_proficiency;
}
void Player::set_character_proficiency(int character_proficiency)
{
	this->character_proficiency = character_proficiency;
}
int Player::get_character_str()
{
	return this->character_str;
}
void Player::set_character_str(int character_str)
{
	this->character_str = character_str;
}
int Player::get_character_str_mod()
{
	return this->character_str_mod;
}
void Player::set_character_str_mod(int character_str_mod)
{
	this->character_str_mod = character_str_mod;
}
int Player::get_character_dex()
{
	return this->character_dex;
}
void Player::set_character_dex(int character_dex)
{
	this->character_dex = character_dex;
}
int Player::get_character_dex_mod()
{
	return this->character_dex_mod;
}
void Player::set_character_dex_mod(int character_dex_mod)
{
	this->character_dex_mod = character_dex_mod;
}
int Player::get_character_con()
{
	return this->character_con;
}
void Player::set_character_con(int character_con)
{
	this->character_con = character_con;
}
int Player::get_character_con_mod()
{
	return this->character_con_mod;
}
void Player::set_character_con_mod(int character_con_mod)
{
	this->character_con_mod = character_con_mod;
}
int Player::get_character_int()
{
	return this->character_int;
}
void Player::set_character_int(int character_int)
{
	this->character_int = character_int;
}
int Player::get_character_int_mod()
{
	return this->character_int_mod;
}
void Player::set_character_int_mod(int character_int_mod)
{
	this->character_int_mod = character_int_mod;
}
int Player::get_character_wis()
{
	return this->character_wis;
}
void Player::set_character_wis(int character_wis)
{
	this->character_wis = character_wis;
}
int Player::get_character_wis_mod()
{
	return this->character_wis_mod;
}
void Player::set_character_wis_mod(int character_wis_mod)
{
	this->character_wis_mod = character_wis_mod;
}
int Player::get_character_cha()
{
	return this->character_cha;
}
void Player::set_character_cha(int character_cha)
{
	this->character_cha = character_cha;
}
int Player::get_character_cha_mod()
{
	return this->character_cha_mod;
}
void Player::set_character_cha_mod(int character_cha_mod)
{
	this->character_cha_mod = character_cha_mod;
}
int Player::get_character_speed()
{
	return this->character_speed;
}
void Player::set_character_speed(int character_speed)
{
	this->character_speed = character_speed;
}
int Player::get_current_hp()
{
	return this->current_hp;
}
void Player::set_current_hp(int current_hp)
{
	this->current_hp = current_hp;
}
BOOL Player::get_str_proficiency()
{
	return this->str_proficiency;
}
void Player::set_str_proficiency(BOOL str_proficiency)
{
	this->str_proficiency = str_proficiency;
}
BOOL Player::get_dex_proficiency()
{
	return this->dex_proficiency;
}
void Player::set_dex_proficiency(BOOL dex_proficiency)
{
	this->dex_proficiency = dex_proficiency;
}
BOOL Player::get_con_proficiency()
{
	return this->con_proficiency;
}
void Player::set_con_proficiency(BOOL con_proficiency) 
{
	this->con_proficiency = con_proficiency;
}
BOOL Player::get_int_proficiency()
{
	return this->int_proficiency;
}
void Player::set_int_proficiency(BOOL int_proficiency)
{
	this->int_proficiency = int_proficiency;
}
BOOL Player::get_wis_proficiency()
{
	return this->wis_proficiency;
}
void Player::set_wis_proficiency(BOOL wis_proficiency)
{
	this->wis_proficiency = wis_proficiency;
}
BOOL Player::get_cha_proficiency()
{
	return this->cha_proficiency;
}
void Player::set_cha_proficiency(BOOL cha_proficiency)
{
	this->cha_proficiency = cha_proficiency;
}
BOOL Player::get_acrobatics()
{
	return this->acrobatics;
}
void Player::set_acrobatics(BOOL acrobatics)
{
	this->acrobatics = acrobatics;
}
BOOL Player::get_animal_handling()
{
	return this->animal_handling;
}
void Player::set_animal_handling(BOOL animal_handling)
{
	this->animal_handling = animal_handling;
}
BOOL Player::get_arcana()
{
	return this->arcana;
}
void Player::set_arcana(BOOL arcana)
{
	this->arcana = arcana;
}
BOOL Player::get_athletics()
{
	return this->athletics;
}
void Player::set_athletics(BOOL athletics)
{
	this->athletics = athletics;
}
BOOL Player::get_deception()
{
	return this->deception;
}
void Player::set_deception(BOOL deception)
{
	this->deception = deception;
}
BOOL Player::get_history()
{
	return this->history;
}
void Player::set_history(BOOL history)
{
	this->history = history;
}
BOOL Player::get_insight()
{
	return this->insight;
}
void Player::set_insight(BOOL insight)
{
	this->insight = insight;
}
BOOL Player::get_intimidation()
{
	return this->intimidation;
}
void Player::set_intimidation(BOOL intimidation)
{
	this->intimidation = intimidation;
}
BOOL Player::get_investigation()
{
	return this->investigation;
}
void Player::set_investigation(BOOL investigation)
{
	this->investigation = investigation;
}
BOOL Player::get_medicine()
{
	return this->medicine;
}
void Player::set_medicine(BOOL medicine)
{
	this->medicine = medicine;
}
BOOL Player::get_nature()
{
	return this->nature;
}
void Player::set_nature(BOOL nature)
{
	this->nature = nature;
}
BOOL Player::get_perception()
{
	return this->perception;
}
void Player::set_perception(BOOL perception)
{
	this->perception = perception;
}
BOOL Player::get_performance()
{
	return this->performance;
}
void Player::set_performance(BOOL performance)
{
	this->performance = performance;
}
BOOL Player::get_persuasion()
{
	return this->persuasion;
}
void Player::set_persuasion(BOOL persuasion)
{
	this->persuasion = persuasion;
}
BOOL Player::get_religion()
{
	return this->religion;
}
void Player::set_religion(BOOL religion)
{
	this->religion = religion;
}
BOOL Player::get_sleight_of_hand()
{
	return this->sleight_of_hand;
}
void Player::set_sleight_of_hand(BOOL sleight_of_hand)
{
	this->sleight_of_hand = sleight_of_hand;
}
BOOL Player::get_stealth()
{
	return this->stealth;
}
void Player::set_stealth(BOOL stealth)
{
	this->stealth = stealth;
}
BOOL Player::get_survival()
{
	return this->survival;
}
void Player::set_survival(BOOL survival)
{
	this->survival = survival;
}
BOOL Player::get_character_turn()
{
	return this->character_turn;
}
void Player::set_character_turn(BOOL character_turn)
{
	this->character_turn = character_turn;
}
std::vector<std::string> Player::get_attack_buttons()
{
	return this->attack_buttons;
}
void Player::set_attack_buttons(std::vector<std::string> attack_buttons)
{
	this->attack_buttons = attack_buttons;
}
std::vector<std::string> Player::get_info_tab()
{
	return this->info_tab;
}
void Player::set_info_tab(std::vector<std::string> info_tab)
{
	this->info_tab = info_tab;
}
int Player::get_character_x_coordinate()
{
	return this->character_x_coordinate;
}
void Player::set_character_x_coordinate(int character_x_coordinate)
{
	this->character_x_coordinate = character_x_coordinate;
}
int Player::get_character_y_coordinate()
{
	return this->character_y_coordinate;
}
void Player::set_character_y_coordinate(int character_y_coordinate)
{
	this->character_y_coordinate = character_y_coordinate;
}