#pragma once
#include "Source.h"
///Enemies - includes stats

class Creature
{
public:
	Creature(string newname, int newHP, int newSTR);
	virtual ~Creature();

	int getHP() const;
	void setHP(int &value);

	virtual int getCurrentHP();
	void setCurrentHP(int temp);

	int get_strength() const;
	void set_strength(int temp);


	virtual void dmgCalc(int incDamage);

protected:
	string name;
	int hp;
	int currentHP;
	int strength;
};

