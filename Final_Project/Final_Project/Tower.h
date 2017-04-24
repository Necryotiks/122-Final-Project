#pragma once
#include "Floor.h"

///*Floor Test Code*/
//sf::Image image;
//image.loadFromFile("32x32.bmp");
//image.createMaskFromColor(sf::Color::Black);
//sf::Texture texture2;
//texture2.loadFromImage(image);
//
//Floor testFloor("Level1.txt", "Music\\Early Floor Music\\Ala Flair.ogg", texture2);
//
///*End Floor Test*/

#define NUM_FLOORS 10 //total number of floors in this tower

class Tower
{
public:
	Tower()
	{
		bitmap.loadFromFile("32x32.bmp");
		bitmap.createMaskFromColor(sf::Color::Black);
		tileset.loadFromImage(bitmap);

		//TODO: fill vector and use for creating floors
		musicFilePaths.clear(); //base initialization 

		for (int i = NUM_FLOORS; i > 0; i--)
		{
			string filename = "Level" + std::to_string(i) + ".txt"; //Build filename to push.

			floorBlueprints.push_back(new Floor(filename, "Music\\Early Floor Music\\Ala Flair.ogg", tileset));
		}
	}

	~Tower()
	{

	}

	Floor *& getCurrentFloor()
	{
		return floorBlueprints.back();
	}

	void nextFloor()
	{
		floorBlueprints.pop_back();
	}

protected:
	sf::Image bitmap;
	sf::Texture tileset;
	vector<Floor *> floorBlueprints;
	vector<string> musicFilePaths;

private:
	
};

