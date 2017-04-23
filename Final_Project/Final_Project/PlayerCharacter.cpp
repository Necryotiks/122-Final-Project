#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(string newname, int newHP, int newSTR): Creature(newname,newHP,newSTR)
{
	mana = 100;
	currentMana = 100;
	hp = 100;
	currentHP = 100;
	current_XP = 0;
	XP_to_next_LVL = 1000;
	currentLVL = 1;
	shekels = 0;//BROKE AS FUCK
	hp_potions = 0;
	mana_potions = 0;
}

PlayerCharacter::~PlayerCharacter()
{
}

int PlayerCharacter::getMana() const
{
	return mana;
}

void PlayerCharacter::setMana(int & value)
{
	mana = value;
	currentMana = value;
	assert(mana == value);
}

int PlayerCharacter::getCurrentMana() const
{
	return currentMana;
}

int PlayerCharacter::getCurrentHP()
{
	return currentHP;
}

int PlayerCharacter::getCurrentXP() const
{
	return current_XP;
}

void PlayerCharacter::awardXP(int & value)//increment XP
{
	current_XP += value;
}

int PlayerCharacter::getNextXP() const
//amount of XP to next level
{
	return currentLVL * 1000 - current_XP;
}

int PlayerCharacter::getCurrentLVL() const
{
	return currentLVL;
}

int PlayerCharacter::getShekels() const
{
	return shekels;
}

void PlayerCharacter::setShekels(int val)
{
	shekels += val;
}

int PlayerCharacter::getHPpot() const
{
	return hp_potions;
}

void PlayerCharacter::setHPpot(int value)
{
	hp_potions += value;
}

int PlayerCharacter::getMpot() const
{
	return mana_potions;
}

void PlayerCharacter::setMpot(int value)
{
	mana_potions += value;
}

int PlayerCharacter::magicMissileDmg()
{
	currentMana = currentMana - 10;
	return 2* currentLVL + 10;
}

int PlayerCharacter::healHP()
{
	currentMana = currentMana - 25;
	return rand() % (10 * currentLVL)+1;
}

//Inventory & PlayerCharacter::getINV()//view inventory
//{
//	return gear;
//}
