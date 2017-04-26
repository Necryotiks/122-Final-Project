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

		//TODO: fill vector and use for creating floors
		//mMusicFilePaths.clear(); //base initialization 

		for (int i = NUM_FLOORS; i > 0; i--)
		{
			string filename = "Level" + std::to_string(i); //Build filename to push.
			//mMusicFilePaths.push_back(filename + ".ogg");
			mFloorBlueprints.push_back(new Floor(filename + ".txt", "Music\\" + filename + ".ogg", mTileset));
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

	void nextFloor()
	{
		this->getCurrentFloor()->stopBgm();
		mFloorBlueprints.pop_back();
	}

protected:
	sf::Image mBitmap;
	sf::Texture mTileset;
	vector<Floor *> mFloorBlueprints;
	//vector<string> mMusicFilePaths;

private:
	
};

