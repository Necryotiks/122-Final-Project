#pragma once
#include "Item.h"
#include "Creature.h"

///Main character. Includes stats and inventory

class Bob : public Creature
{
public:
	Bob();
	~Bob();

	//stats derived from Creature.h

	Item get_item();
	void add_item(Item temp);

private:
	Item inventory[4];
	int strength;
	int health;
	int defense;
};