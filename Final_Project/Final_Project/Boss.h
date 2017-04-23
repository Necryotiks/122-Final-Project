#pragma once
#include "Creature.h"

///Final enemy - includes stats

class Boss : public Creature
{
public:
	Boss(string newname, int newHP, int newSTR, int newArmor);
	~Boss();

	//all stats derived from Creature.h
	int getArmorValue();
	void dmgCalc(int incDamage) override;

private:
	int armorval;
};

