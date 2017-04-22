#pragma once
#include "Creature.h"

///Final enemy - includes stats

class Boss : public Creature
{
public:
	Boss(string newname, int newHP, int newSTR);
	~Boss();

	//all stats derived from Creature.h

private:
	int health;
	string name;
	int strength;
};

