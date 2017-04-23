#pragma once
#include "Source.h"
#include "Creature.h"

//typedef struct inventory
//{
//	double armor_hp;//current
//	int weapon_hp;
//	int gold;
//	int hp_potions;
//	int mana_potions;
//}Inventory;
class PlayerCharacter : public Creature
{
public:
	PlayerCharacter(string newname, int newHP, int newSTR);
	~PlayerCharacter();
	int getMana() const;
	void setMana(int &value);
	int getCurrentMana() const;
	
	int getCurrentHP() override;
	int getCurrentXP() const;
	void awardXP(int &value);
	int getNextXP() const;
	int getCurrentLVL() const;
	//Inventory & getINV();

private:
	int mana;
	int currentMana;
	int current_XP;
	int XP_to_next_LVL;
	int currentLVL;
	//Inventory gear;
};
