#pragma once
#include "Source.h"

class Item
{
public:

	Item(int h, int s, int d, string n);
	~Item();

	int get_plush();
	int get_pluss();
	int get_plusd();
	string get_name();


private:
	int plus_health;
	int plus_strength;
	int plus_defense;
	string name;
};