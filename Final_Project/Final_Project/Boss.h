#pragma once
#include "Creature.h"

///Final enemy - includes stats

class Boss : public Creature
{
public:
	Boss();
	~Boss();

	//all stats derived from Creature.h

private:
	int health;
	int defense;
	int strength;
};

