#include "Creature.h"


Creature::Creature(string newname, int newHP, int newSTR)
{
	name = newname;
	hp = newHP;
	currentHP = hp;
	strength = newSTR;
}


Creature::~Creature()
{

}



int Creature::getHP() const
{
	return hp;
}
void Creature::setHP(int &value)
{
	hp = value;
}

int Creature::getCurrentHP()
{
	return currentHP;
}

void Creature::setCurrentHP(int temp)
{
	currentHP = temp;
}

int Creature::get_strength() const
{
	return strength;
}
void Creature::set_strength(int temp)
{
	strength = temp;
}

void Creature::dmgCalc(int incDamage)
{
	hp = hp - incDamage;
}

int Creature::hitDmg() const
{
	return rand() % strength;
}

string Creature::getName() const
{
	return name;
}

//int Creature::get_defense()
//{
//	return defense;
//}
//void Creature::set_defense(int temp)
//{
//	defense = temp;
//}