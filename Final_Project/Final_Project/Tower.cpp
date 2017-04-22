#include "Tower.h"


Tower::Tower(int current)
{
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
