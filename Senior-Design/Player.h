#include "pch.h"

using namespace std;

#pragma once
class Player
{
private:
	int location;
	string filename;
public:
	Player(int location, string filename);
	int get_location();
	void set_location(int newLocation);
	string get_filename();
	void set_filename(string newFilename);


};

