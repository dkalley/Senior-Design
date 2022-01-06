#include "pch.h"
#include "Player.h"

Player::Player(int location, string filename)
{
	this->location = location;
	this->filename = filename;
}

int Player::get_location()
{
	return this->location;
}
void Player::set_location(int newLocation)
{
	this->location = newLocation;
}
string Player::get_filename()
{
	return this->filename;
}
void Player::set_filename(string newFilename)
{
	this->filename = newFilename;
}