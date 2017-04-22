#pragma once

///Enemies - includes stats

class Creature
{
public:
	Creature();
	~Creature();

	int get_health();
	void set_health(int temp);

	int get_strength();
	void set_strength(int temp);

	int get_defense();
	void set_defense(int temp);

private:
	int hp;
	int strength;
	int defense;
};

