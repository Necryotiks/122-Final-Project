#include "Tower.h"


Tower::Tower(int current)
{
	mTileset.loadFromFile("32x32.bmp");
	current_floor = current;
}


Tower::~Tower()
{

}



int Tower::get_floor()
{
	return current_floor;
}

void Tower::set_floor(int temp)
{
	current_floor = temp;
}
