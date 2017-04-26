#include "Floor.h"

using std::ifstream;
using std::vector;
using std::string;

Floor::Floor(string floorFile, string musicFile, sf::Texture & tileSet)
{
	mBgmFileName = musicFile;
	if (!mBgm.openFromFile(mBgmFileName)) //check for loading issues
	{
		std::cout << "Bad load." << std::endl; //error message
	}
	mBgm.setLoop(true); //loop entire time player is on the floor

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
			mLevel[x][y]->setPosition((float)(x * TILE_SIZE), (float)((y * TILE_SIZE) + MAP_OFFSET));
		}

		if (!line.empty()) //empty the current line, grab next line of floor CSV file
		{
			line.clear();
			line = csvLineReader();
		}
	}
}

Floor::~Floor()
{
		mBgm.stop();
}

void Floor::printFloor(sf::RenderWindow & window)
{
	for (int x = 0; x < FLOOR_WIDTH; x++)
	{
		for (int y = 0; y < FLOOR_HEIGHT; y++)
		{
			if (this->getTile(x, y)->getType() > STAIRS)
			{
				this->getFloorTile()->setPosition((float)(x * TILE_SIZE), (float)((y * TILE_SIZE) + MAP_OFFSET));
				window.draw(*this->getFloorTile());
			}
			window.draw(*this->getTile(x, y));
		}
	}
}

void Floor::playBgm()
{
	if (mBgm.getStatus() != sf::Music::Playing)
		mBgm.play(); //start playing
}

void Floor::stopBgm()
{
	mBgm.stop();
}

Tile *& Floor::getTile(int x, int y)
{
	//cout << (mLevel[x][y]->getPosition().x / 32) << (mLevel[x][y]->getPosition().y / 32) << endl;

	return mLevel[x][y];
}

Tile *& Floor::getFloorTile()
{
	return mFloor;
}

void Floor::openCsv(string filename)
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


vector<Type> Floor::csvLineReader()
{
	//read one line from file and split line into individual fields
	vector<Type> result;
	string line;

	std::getline(mCsvStream, line);

	std::stringstream lineStream(line);
	string field;

	while (std::getline(lineStream, field, ','))
	{
		result.push_back((Type)atoi(field.c_str()));
	}

	return result;

}

void Floor::csvFileReader()
{
	//loop until all lines are read from the file
	vector<Type> line = csvLineReader();

	while (!line.empty())
	{

		line.clear();
		line = csvLineReader();
	}
}