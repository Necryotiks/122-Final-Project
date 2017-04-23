#include "Tile.h"
#include <SFML/Graphics/Drawable.hpp>


Tile::Tile()
{
}


Tile::~Tile()
{
}

void Tile::setTileState(bool isPass, bool isInteractable)
{
	isInteract = isInteractable;
}

