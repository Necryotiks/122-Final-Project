#pragma once
/*
	Order of operations for loading transparent tile sprites
	
	sf::Image image;
	image.loadFromFile("32x32.bmp");
	image.createMaskFromColor(sf::Color::Black);
	sf::Texture texture;
	texture.loadFromImage(image);

	Then draw in order:
	floor
	next tile
*/

#include <SFML\Audio.hpp>
#include <fstream>
#include "Tile.h"

using std::ifstream;
using std::vector;
using std::string;


#define FLOOR_WIDTH 25 //number of 32x32 tiles across horizontally
#define FLOOR_HEIGHT 16 //number of 32x32 tiles stacked vertically 
#define MAP_OFFSET 88 //number of pixels to offset map from top banner

class Floor
{
public:
	Floor(string floorFile, string musicFile, sf::Texture & tileSet);
	
	~Floor();
	
	void printFloor(sf::RenderWindow & window);

	
	void playBgm();

	void stopBgm();

	Tile *& getTile(int x, int y);

	Tile *& getFloorTile();

protected:
	Tile * mLevel[FLOOR_WIDTH][FLOOR_HEIGHT];
	sf::Music mBgm; //background music stream
	string mBgmFileName; //music file to open
	
	//These should probably be in Tower.h
	Tile * mFloor;
	Tile * mWall;
	Tile * mStairs;
	

private:
	ifstream mCsvStream;

	void openCsv(string filename);

	vector<Type> csvLineReader();

	void csvFileReader();
};

