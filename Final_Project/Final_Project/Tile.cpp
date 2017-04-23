#include "Tile.h"



Tile::Tile(Type tileType, sf::Texture & tileSet) : sf::Sprite::Sprite() //load texture/position from sprite functions
{
	this->setTexture(tileSet);
	mTileType = tileType;
	switch (mTileType)
	{
	case FLOOR:
		this->setTextureRect(sf::IntRect((FLOOR_TILE * TILE_SIZE), 0, TILE_SIZE, TILE_SIZE));
		mCanInteract = false;
		mCanPass = true;
		break;
	case WALL:
		this->setTextureRect(sf::IntRect((WALL_TILE_L * TILE_SIZE), (WALL_TILE_T * TILE_SIZE), TILE_SIZE, TILE_SIZE));
		mCanInteract = false;
		mCanPass = false;
		break;
	case STAIRS:
		this->setTextureRect(sf::IntRect((STAIRS_TILE * TILE_SIZE), 0, TILE_SIZE, TILE_SIZE));
		mCanInteract = true;
		mCanPass = true;
		break;
	case CHEST:
		this->setTextureRect(sf::IntRect((CHEST_TILE_L * TILE_SIZE), (CHEST_TILE_T * TILE_SIZE), TILE_SIZE, TILE_SIZE));
		mCanInteract = true;
		mCanPass = true;
		break;
	case TRAP:
		this->setTextureRect(sf::IntRect((TRAP_TILE_L * TILE_SIZE), (TRAP_TILE_T * TILE_SIZE), TILE_SIZE, TILE_SIZE));
		mCanInteract = true;
		mCanPass = true;
		break;
	case MOB:
		this->setTextureRect(sf::IntRect((MOB_TILE_L * TILE_SIZE), (MOB_TILE_T * TILE_SIZE), TILE_SIZE, TILE_SIZE));
		mCanInteract = true;
		mCanPass = true;
		break;
	case MINI:
		this->setTextureRect(sf::IntRect((MINI_TILE_L * TILE_SIZE), (MINI_TILE_T * TILE_SIZE), TILE_SIZE, TILE_SIZE));
		mCanInteract = true;
		mCanPass = true;
		break;
	case BOSS:
		this->setTextureRect(sf::IntRect((BOSS_TILE_L * TILE_SIZE), (BOSS_TILE_T * TILE_SIZE), TILE_SIZE, TILE_SIZE));
		mCanInteract = true;
		mCanPass = true;
		break;
	}
}


Tile::~Tile()
{
}

bool Tile::getPassState()
{
	return mCanPass;
}

bool Tile::getInteractState()
{
	return mCanInteract;
}

Type Tile::getType()
{
	return mTileType;
}

void Tile::setTileState (bool newInteract)
{
	mCanInteract = newInteract;
}



