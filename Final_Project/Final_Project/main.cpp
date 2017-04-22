#include "Source.h"
#include "Bob.h"
#include "Boss.h"
#include "Creature.h"
#include "Encounter.h"
#include "Floor.h"
#include "Tower.h"
//#include "Item.h"

#include <SFML/Graphics.hpp>


int main()
{
	int currentfloor = 1, choice = 0;

	sf::RenderWindow window(sf::VideoMode(825, 600), "The Perils of Aeliorn: Mage's Tower Ascent");
	
	///Main Character
	sf::Texture bob_front;
	bob_front.loadFromFile("BobSprite/BobFront.png");
	sf::Texture bob_back;
	bob_back.loadFromFile("BobSprite/BobBack.png");
	sf::Texture bob_left;
	bob_left.loadFromFile("BobSprite/BobLeft.png");
	sf::Texture bob_right;
	bob_right.loadFromFile("BobSprite/BobRight.png");
	sf::Sprite bob(bob_front);
	bob.setPosition(0.0f, 225.0f);
	bob.setScale(4.0f, 4.5f);
	//create bob object
	
	///Enemies
	//create textures/sprites for all 5 enemies. edit positions/scales

	///Items
	/*Item shield(0,0,5,"Shield");
	Item dagger(0, 5, 0, "Dagger");
	Item elixer(10, 0, 0, "Elixer");*/
	//item in which player can choose which stat to increase created later on

	///Other Elements
	Tower gameplay;


	///Event
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				
				if (event.key.code == sf::Keyboard::A)
				{
					if (bob.getPosition().x == 0)
					{
						//not to go off edge
					}
					else
					{
						bob.move(sf::Vector2f(-50, 0));
						bob.setTexture(bob_left);
					}
				}

				if (event.key.code == sf::Keyboard::D)
				{
					if (bob.getPosition().x == 700)
					{
						//not to go off edge
					}
					else
					{
						bob.move(sf::Vector2f(50, 0));
						bob.setTexture(bob_right);
					}
				}

				if (event.key.code == sf::Keyboard::S)
				{
					if (bob.getPosition().y == 475)
					{
						//not to go off edge
					}
					else
					{
						bob.move(sf::Vector2f(0, 50));
						bob.setTexture(bob_front);
					}

				}

				if (event.key.code == sf::Keyboard::W)
				{
					if (bob.getPosition().y == -25)
					{
						//not to go off edge
					}
					else
					{
						bob.move(sf::Vector2f(0, -50));
						bob.setTexture(bob_back);
					}
					
				}

				if (event.key.code == sf::Keyboard::Space)
				{
					//attack?
				}
			}
			if (bob.getPosition().x == 600 && bob.getPosition().y == 225)
			{
				//encounter
				switch (currentfloor)
				{
				case 1: 
					//enemy1
					break;
				case 2:
					//enemy2
					break;
				case 3:
					//enemy3
					break;
				case 4:
					//enemy4
					break;
				case 5:
					//bigboyboss
					break;
				default:
					break;
				}
			}

			if (bob.getPosition().x == 650 && bob.getPosition().y == 225)
			{
				//chest
				switch (currentfloor)
				{
				case 1:
					//shield
					break;
				case 2:
					//dagger
					break;
				case 3:
					//elixer
					break;
				case 4:
					//display choices (3)
					cin >> choice;
					//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) //plus health
					//{
					//	Item extrah(5, 0, 0, "Potion");
					//}
					//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) //plus strength
					//{
					//	Item extras(0, 5, 0, "CrossBow");
					//}
					//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) //plus defense
					//{
					//	Item extrad(0, 0, 5, "Helmet");
					//}
					break;
				case 5:
					//special somethinng - end of game - close window.
					break;
				default:
					break;
				}
			}

			if (bob.getPosition().x == 700 && bob.getPosition().y == 225)
			{
				if (currentfloor == 5)
				{
					//end game
				}
				else
				{
					currentfloor++;
					//next floor: change bob position
				}
			}
		}

		window.clear();


		window.draw(bob);
		//window.draw(bigboy);
		//window.draw(c1);
		//window.draw(c2);
		//window.draw(c3);
		//window.draw(c4);
		//window.draw(c5);
		//window.draw(f1);
		//window.draw(f2);
		//window.draw(f3);
		//window.draw(f4);
		//window.draw(f5);


		window.display();
		
	}
}