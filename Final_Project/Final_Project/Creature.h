#pragma once
#include "Source.h"
///Enemies - includes stats

class Creature
{
public:
	Creature(string newname, int newHP, int newSTR);
	~Creature();

	int get_health() const;
	void set_health(int temp);

	int get_strength();
	void set_strength(int temp);

	//int get_defense();
	//void set_defense(int temp);

private:
	string name;
	int hp;
	int strength;
	//int defense;
};

