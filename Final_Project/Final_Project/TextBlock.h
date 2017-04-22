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
		//testlines
	//TextBlock HP(24, "Health", sf::Vector2f(32,32), font);
	//window.draw(HP);

};
