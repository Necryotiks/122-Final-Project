#pragma once
#include "Creature.h"

///Final enemy - includes stats

class Boss : public Creature
{
public:
	Boss(string newname, int newHP, int newSTR, int newArmor, int XP);
	~Boss();

	//all stats derived from Creature.h
	int getArmorValue() const;
	void dmgCalc(int incDamage) override;

private:
	int armorval;
};

