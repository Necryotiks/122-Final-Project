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
#include <fstream>
#include "Tile.h"

//#include "Creature.h"

using std::ifstream;
using std::vector;
using std::string;

#define FLOOR_WIDTH 25 //number of 32x32 tiles across horizontally
#define FLOOR_HEIGHT 16 //number of 32x32 tiles stacked vertically 
#define MAP_OFFSET 88 //number of pixels to offset map from top banner

class Floor
{
public:
	Floor(string floorFile, string musicFile, sf::Texture & tileSet)
	{
		mBgmFileName = musicFile;
		mFloor = new Tile(FLOOR, tileSet);
		mWall = new Tile(WALL, tileSet);
		mStairs = new Tile(STAIRS, tileSet);

		//open file
		openCsv(floorFile);

		vector<Type> line = csvLineReader(); //Grab the first line of the floor CSV file


		//fill Tile array
		for (int y = 0; y < FLOOR_HEIGHT; y++) //loop each row
		{
			for (int x = 0; x < FLOOR_WIDTH; x++) //loop each column
			{
				switch (line.at(x))
				{
				/*case FLOOR:
					mLevel[x][y] = mFloor;
					break;
				case WALL:
					mLevel[x][y] = mWall;
					break;
				case STAIRS:
					mLevel[x][y] = mStairs;
					break;*/
				default:
					mLevel[x][y] = new Tile(line.at(x), tileSet);
					break;
				}
				mLevel[x][y]->setPosition((float) (x * TILE_SIZE),(float)((y * TILE_SIZE) + MAP_OFFSET));
			}

			if (!line.empty()) //empty the current line, grab next line of floor CSV file
			{
				line.clear();
				line = csvLineReader();
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

	Tile *& getTile(int x, int y)
	{
		//cout << (mLevel[x][y]->getPosition().x / 32) << (mLevel[x][y]->getPosition().y / 32) << endl;
		
		return mLevel[x][y];
	}

	Tile *& getFloorTile()
	{
		return mFloor;
	}

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

	void openCsv(string filename)
	{
		//safely open file and return stream
		try
		{
			mCsvStream.open(filename, ifstream::in);
		}
		catch (std::exception & e)
		{
			cout << "Exception: " << e.what() << endl;
		}
	}


	vector<Type> csvLineReader()
	{
		//read one line from file and split line into individual fields
		vector<Type> result;
		string line;

		std::getline(mCsvStream, line);

		std::stringstream lineStream(line);
		string field;

		while (std::getline(lineStream, field, ','))
		{
			result.push_back((Type) atoi(field.c_str()));
		}

		return result;

	}

	void csvFileReader()
	{
		//loop until all lines are read from the file
		vector<Type> line = csvLineReader();

		while (!line.empty())
		{
			
			line.clear();
			line = csvLineReader();
		}
	}
};

