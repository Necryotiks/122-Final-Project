#pragma once
#include "Source.h"
typedef struct inventory
{
	double armor_hp;
	int weapon_hp;
	int gold;
	int hp_potions;
	int mana_potions;
}Inventory;
class PlayerCharacter
{
public:
	PlayerCharacter();
	~PlayerCharacter();
	int getMana() const;
	void setMana(int &value);
	int getCurrentMana() const;
	int getHP() const;
	void setHP(int &value);
	int getCurrentHP() const;
	int getCurrentXP() const;
	void awardXP(int &value);
	int getNextXP() const;
	int getCurrentLVL() const;
	Inventory & getINV();

private:
	int mana;
	int currentMana;
	int hp;
	int currentHP;
	int current_XP;
	int XP_to_next_LVL;
	int currentLVL;
	Inventory gear;
};

