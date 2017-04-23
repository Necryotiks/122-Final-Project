#pragma once

#include "Source.h"

class TextBlock : public sf::Text
{
public:
	TextBlock(int size, string contents, sf::Vector2f const &pos, sf::Font &font)
	{
		this->setCharacterSize(size);
		this->setFont(font);
		this->setString(contents);
		this->setStyle(sf::Text::Regular);
		this->setPosition(pos);
	}
	TextBlock(int size, string Label, string num, string denom, sf::Vector2f const &pos, sf::Font &font)
	{
		this->setCharacterSize(size);
		this->setFont(font);
		string contents = Label + " " + num + "/" + denom;
		this->setString(contents);
		this->setStyle(sf::Text::Regular);
		this->setPosition(pos);
	}
	TextBlock(int size, string contents,string cont2,sf::Vector2f const &pos, sf::Font &font)
	{
		this->setCharacterSize(size);
		this->setFont(font);
		string contents1 = contents+" "+cont2;
		this->setString(contents1);
		this->setStyle(sf::Text::Regular);
		this->setPosition(pos);
	}
		//testlines
	//TextBlock HP(24, "Health", sf::Vector2f(32,32), font);
	//window.draw(HP);
	//TextBlock XP(Charsize, "Exp:", std::to_string(MJ.getCurrentXP()), std::to_string(MJ.getNextXP()), sf::Vector2f(0,Charsize), font);
	//window.draw(XP);

};
