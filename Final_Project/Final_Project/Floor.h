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

#include <SFML/Audio.hpp>
#include "Tile.h"
#include "Tower.h"
//#include "Creature.h"


#define FLOOR_WIDTH 25 //number of 32x32 tiles across horizontally
#define FLOOR_HEIGHT 16 //number of 32x32 tiles stacked vertically 

class Floor
{
public:
	Floor(char * floorFile, char * musicFile, sf::Texture & tileSet)
	{
		mBgmFileName = musicFile;
		mFloor = new Tile(FLOOR, tileSet);
		mWall = new Tile(WALL, tileSet);
		mStairs = new Tile(STAIRS, tileSet);

		//open file


		

		//fill Tile array
		for (int i = 0; i < FLOOR_WIDTH; i++)
		{
			for (int j = 0; j < FLOOR_HEIGHT; j++)
			{
				
				//mLevel[i][j] = 
			}
		}
	}
	~Floor()
	{
		mBgm.stop();
	}
	
	void playBgm()
	{
		if (!mBgm.openFromFile(mBgmFileName)) //check for loading issues
		{
			std::cout << "Bad load." << std::endl; //error message
		}
		mBgm.setLoop(true); //loop entire time player is on the floor
		mBgm.play(); //start playing
	}

protected:
	Tile * mLevel[FLOOR_WIDTH][FLOOR_HEIGHT];
	sf::Music mBgm; //background music stream
	char * mBgmFileName; //music file to open
	
	//These should probably be in Tower.h
	Tile * mFloor;
	Tile * mWall;
	Tile * mStairs;
	

private:
	
};

