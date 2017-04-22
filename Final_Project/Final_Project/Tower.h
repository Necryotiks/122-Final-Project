#pragma once
#include "Item.h"
#include "Floor.h"

class Tower
{
public:
	Tower(int current = 1);
	~Tower();

	int get_floor();
	void set_floor(int temp);

private:
	int current_floor;
	//Floor level[5];
};

