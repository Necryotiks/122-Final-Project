#pragma once
#include "Source.h"
class Tile : sf::Drawable
{
public:
	Tile();
	~Tile();

	void setTileState(bool isPass, bool isOccupied);
private:
	bool isInteract;


};

