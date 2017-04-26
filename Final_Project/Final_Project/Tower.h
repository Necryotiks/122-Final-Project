#pragma once
#include "Floor.h"

//*F/loor Test Code*/
//sf::Image image;
//image.loadFromFile("32x32.bmp");
//image.createMaskFromColor(sf::Color::Black);
//sf::Texture texture2;
//texture2.loadFromImage(image);
//
//Floor testFloor("Level1.txt", "Music\\Early Floor Music\\Ala Flair.ogg", texture2);
//
///*End Floor Test*/

#define NUM_FLOORS 12 //total number of floors in this tower

class Tower
{
public:
	Tower()
	{
		mBitmap.loadFromFile("32x32.bmp");
		mBitmap.createMaskFromColor(sf::Color::Black);
		mTileset.loadFromImage(mBitmap);
		sf::Vector2f startPosition[12] = 
		{
			{(float)(12 * TILE_SIZE), (float)MAP_OFFSET + (14 * TILE_SIZE)},
			{(float)(23 * TILE_SIZE), (float)MAP_OFFSET + (14 * TILE_SIZE)},
			{(float)(2 * TILE_SIZE), (float)MAP_OFFSET + (1 * TILE_SIZE)},
			{(float)(12 * TILE_SIZE), (float)MAP_OFFSET + (12 * TILE_SIZE)},
			{(float)(12 * TILE_SIZE), (float)MAP_OFFSET + (12 * TILE_SIZE)},
			{(float)(20 * TILE_SIZE), (float)MAP_OFFSET + (7 * TILE_SIZE)},
			{(float)(1 * TILE_SIZE), (float)MAP_OFFSET + (1 * TILE_SIZE)},
			{(float)(12 * TILE_SIZE), (float)MAP_OFFSET + (12 * TILE_SIZE)},
			{(float)(12 * TILE_SIZE), (float)MAP_OFFSET + (12 * TILE_SIZE)},
			{(float)(23 * TILE_SIZE), (float)MAP_OFFSET + (14 * TILE_SIZE)},
			{(float)(12 * TILE_SIZE), (float)MAP_OFFSET + (14 * TILE_SIZE)},
			{(float)(12 * TILE_SIZE), (float)MAP_OFFSET + (12 * TILE_SIZE)}
		};

		

		for (int i = NUM_FLOORS; i > 0; i--)
		{
			string filename = "Level" + std::to_string(i); //Build filename to push.
			
			mFloorBlueprints.push_back(new Floor(filename + ".txt", "Music\\" + filename + ".ogg", mTileset, startPosition[i-1]));
		}
	}

	~Tower()
	{

	}

	Floor *& getCurrentFloor()
	{
		return mFloorBlueprints.back();
	}

	int getCurrentFloorNumber()
	{
		return (NUM_FLOORS - mFloorBlueprints.size() + 1);
	}

	sf::Vector2f & nextFloor()
	{
		this->getCurrentFloor()->stopBgm();
		mFloorBlueprints.pop_back();
		return	this->getCurrentFloor()->getStartPosition();
		 
	}

protected:
	sf::Image mBitmap;
	sf::Texture mTileset;
	vector<Floor *> mFloorBlueprints;

private:
	
};

