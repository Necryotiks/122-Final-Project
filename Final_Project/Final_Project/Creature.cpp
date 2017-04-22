#include "Creature.h"


Creature::Creature()
{

}


Creature::~Creature()
{

}



int Creature::get_health()
{
	return hp;
}
void Creature::set_health(int temp)
{
	hp = temp;
}

int Creature::get_strength()
{
	return strength;
}
void Creature::set_strength(int temp)
{
	strength = temp;
}

int Creature::get_defense()
{
	return defense;
}
void Creature::set_defense(int temp)
{
	defense = temp;
}