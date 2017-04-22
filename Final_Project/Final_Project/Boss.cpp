#include "Boss.h"



Boss::Boss(string newname, int newHP, int newSTR) :Creature(newname, newHP, newSTR)
{
	health = newHP;
	strength = newSTR;
	name = newname;
}


Boss::~Boss()
{
}
