#include "Boss.h"



Boss::Boss(string newname, int newHP, int newSTR,int newArmor) :Creature(newname, newHP, newSTR)
{
	hp = newHP;
	strength = newSTR;
	name = newname;
	armorval = newArmor;
}


Boss::~Boss()
{
}

void Boss::dmgCalc(int incDamage)
{
	currentHP = currentHP - (incDamage- armorval);
}
