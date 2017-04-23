#pragma once
#include "Source.h"

#define TILE_SIZE 32 //number of pixels in one edge of tile square: 32x32
#define FLOOR_TILE 21 //position of floor tile on tileset (top row)
#define WALL_TILE_L 21 //position of wall tile (left) on tileset
#define WALL_TILE_T 2 //position of wall tile (top) on tileset
#define STAIRS_TILE 22 //position of stairs tile on tileset (top row)
#define TRAP_TILE_L 15 //position of trap tile (left) on tileset 
#define TRAP_TILE_T 3 //position of trap tile (top) on tileset
#define CHEST_TILE_L 26 //position of chest tile (left) on tileset
#define CHEST_TILE_T 4 //position of chest tile (top) on tileset
#define MOB_TILE_L 7 //position of mob tile (left) on tileset
#define MOB_TILE_T 18  //position of mob tile (top) on tileset
#define MINI_TILE_L 16 //position of mini boss tile (left) on tileset
#define MINI_TILE_T 32 //position of mini boss tile (top) on tileset
#define BOSS_TILE_L 28 //position of boss tile (left) on tileset
#define BOSS_TILE_T 50 //position of boss tile (top) on tileset

typedef enum type
{
	FLOOR, WALL, STAIRS, CHEST, TRAP, MOB, MINI, BOSS
}Type;

class Tile : public sf::Sprite
{
public:
	Tile(Type tileType, sf::Texture & tileSet);
	~Tile();

	//getters
	bool getPassState();

	bool getInteractState();

	Type getType();
	
	//setters
	void setTileState(bool newInteract);

protected:

	bool mCanPass;
	bool mCanInteract;
	Type mTileType;

private:


};

