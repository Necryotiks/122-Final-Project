#include "Boss.h"



Boss::Boss(string newname, int newHP, int newSTR,int newArmor, int XP) :Creature(newname, newHP, newSTR, XP)
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
