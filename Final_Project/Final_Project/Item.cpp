#include  "Item.h"

Item::Item(int h, int s, int d, string n)
{
	plus_health = h;
	plus_strength = s;
	plus_defense = d;
	name = n;
}

Item::~Item()
{

}


int Item::get_plush()
{
	return plus_health;
}


int Item::get_pluss()
{
	return plus_strength;
}

int Item::get_plusd()
{
	return plus_defense;
}

string Item::get_name()
{
	return name;
}