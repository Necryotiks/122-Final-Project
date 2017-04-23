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

//Inventory & PlayerCharacter::getINV()//view inventory
//{
//	return gear;
//}
