#pragma once
#include "Source.h"
///Enemies - includes stats

class Creature
{
public:
	Creature(string newname, int newHP, int newSTR,int XP);
	virtual ~Creature();

	int getHP() const;
	void setHP(int &value);

	virtual int getCurrentHP();
	void setCurrentHP(int temp);

	int get_strength() const;
	void set_strength(int temp);


	virtual void dmgCalc(int incDamage);//incoming damage
	int hitDmg() const;//outgoing damage

	string getName() const;

	int getXP() const;

protected:
	string name;
	int hp;
	int currentHP;
	int strength;
	int xpWorth;
};

