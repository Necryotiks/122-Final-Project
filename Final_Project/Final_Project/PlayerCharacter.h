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
	explicit PlayerCharacter(string newname = "Mithril Jackson", int newHP  =100, int newSTR = 10, int XP = 0);
	~PlayerCharacter();
	int getMana() const;
	void setMana(int &value);
	int getCurrentMana() const;
	void setCurrentMana(int addMana);
	
	int getCurrentHP() override;
	int getCurrentXP() const;
	void awardXP(int &value);
	int getNextXP() const;
	int getCurrentLVL() const;
	void setCurrentLVL(int addLVL);

	int getShekels() const;
	void setShekels(int val);

	int getHPpot() const;
	void setHPpot(int value);

	int getMpot() const;
	void setMpot(int value);

	int magicMissileDmg();//10 mana
	void healHP();//25 mana


	//Inventory & getINV();

private:
	int mana;
	int currentMana;
	int current_XP;
	int XP_to_next_LVL;
	int currentLVL;
	int shekels;
	int hp_potions;
	int mana_potions;
	//Inventory gear;
};
