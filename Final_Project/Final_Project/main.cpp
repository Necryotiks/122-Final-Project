#include "Source.h"
#include "Creature.h"
#include "Tower.h"
#include "TextBlock.h"
#include "PlayerCharacter.h"
//#include "Item.h"



int main()
{
	sf::Font font;

	if (!font.loadFromFile("font1.ttf"))
	{
		//will throw error
	}
	PlayerCharacter Player;
	TextBlock hpBox(Charsize, "Health:", std::to_string(Player.getCurrentHP()), std::to_string(Player.getHP()), sf::Vector2f(0, 0), font);
	TextBlock manaBox(Charsize, "Mana:", std::to_string(Player.getCurrentMana()), std::to_string(Player.getMana()), sf::Vector2f(150, 0), font);
	TextBlock xpBox(Charsize, "XP:", std::to_string(Player.getCurrentXP()), std::to_string(Player.getNextXP()), sf::Vector2f(150, Charsize), font);
	TextBlock lvlBox(Charsize, "LVL:", std::to_string(Player.getCurrentLVL()), sf::Vector2f(0, Charsize), font);
	TextBlock shekelBox(Charsize, "Shekels:", std::to_string(Player.getShekels()), sf::Vector2f(290, 0), font);
	// POTS GO HERE
	TextBlock tipBox(Charsize, "ESC to quit!", sf::Vector2f(350, 570), font);
	// setup window
	sf::Vector2i screenDimensions(800, 600);
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "The Perils of Aeliorn: Mage's Tower Ascent");
	window.setFramerateLimit(60);

	// load texture (spritesheet)
	sf::Texture texture;
	if (!texture.loadFromFile("CharSprites/BronzeKnight.png"))
	{
		std::cout << "Failed to load player spritesheet!" << std::endl;
		return 1;
	}

	// set up the animations for all four directions (set spritesheet and push frames)
	Animation walkingAnimationDown;
	Animation walkingAnimationLeft;
	Animation walkingAnimationRight;
	Animation walkingAnimationUp;
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));//finish anims.
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));


	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 64, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 64, 32, 32));


	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));


	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));

	Animation DeathAnimation;
	DeathAnimation.setSpriteSheet(texture);
	DeathAnimation.addFrame(sf::IntRect(0, 128, 32, 32));//change death animation key
	DeathAnimation.addFrame(sf::IntRect(32, 128, 32, 32));
	DeathAnimation.addFrame(sf::IntRect(64, 128, 32, 32));
	DeathAnimation.addFrame(sf::IntRect(96, 128, 32, 32));
	DeathAnimation.addFrame(sf::IntRect(160, 128, 32, 32));
	DeathAnimation.addFrame(sf::IntRect(192, 128, 32, 32));
	DeathAnimation.addFrame(sf::IntRect(224, 128, 32, 32));
	DeathAnimation.addFrame(sf::IntRect(256, 128, 32, 32));
	DeathAnimation.addFrame(sf::IntRect(288, 128, 32, 32));

	auto * currentAnimation = &walkingAnimationDown;

	// set up AnimatedSprite
	AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

	sf::Clock frameClock;

	auto speed = 100.0;
	auto noKeyWasPressed = true;

	while (window.isOpen())
	{
		srand(time(nullptr));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		auto frameTime = frameClock.restart();

		// if a key was pressed set the correct animation and move correctly
		sf::Vector2f movement(0.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			currentAnimation = &walkingAnimationLeft;
			movement.y -= speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			currentAnimation = &walkingAnimationLeft;
			movement.y += speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			currentAnimation = &walkingAnimationRight;
			movement.x -= speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			currentAnimation = &walkingAnimationLeft;
			movement.x += speed;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			currentAnimation = &DeathAnimation;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			Creature testCreep("AndyBot", 50, 50, 100);
			sf::RenderWindow combatWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Fight!", sf::Style::Titlebar);
			combatWindow.setFramerateLimit(60);
			while (combatWindow.isOpen())
			{
				sf::Event combatEvent;
				while (combatWindow.pollEvent(combatEvent))
				{
					if (combatEvent.type == sf::Event::Closed)
						combatWindow.close();
					if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Escape)
						combatWindow.close();
					if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num1)
					{	//Melee attack
						testCreep.dmgCalc(Player.hitDmg());//player attacks creep, creep takes damage
						if (testCreep.getCurrentHP() <= 0)
						{
							combatWindow.close();
						}//else keep fighting!
						Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
					}
					if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == (sf::Keyboard::Num2))
					{	//Magic attack
						if (Player.getCurrentMana() >= 10)
						{
							testCreep.dmgCalc(Player.magicMissileDmg());//player attacks creep, creep takes damage
							if (testCreep.getCurrentHP() <= 0)
							{
								combatWindow.close();
							}//else keep fighting!
							Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
						}
					}
					if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == (sf::Keyboard::Num3))
					{	//Heal
						if (Player.getCurrentMana() >= 25)
						{
							Player.healHP();

							Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage

						}
					}

					//end Event Handler

					if (Player.getCurrentHP() <= 0)
					{
						//death animation, you die
						combatWindow.close();
						sf::RenderWindow deathWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "RIP", sf::Style::Titlebar);
						while (deathWindow.isOpen())
						{
							sf::Event deathEvent;
							while (deathWindow.pollEvent(deathEvent))
							{
								if (deathEvent.type == sf::Event::KeyPressed && deathEvent.key.code == sf::Keyboard::Escape)
									deathWindow.close();
							}
							TextBlock RIP(Charsize * 5, "YOU DIED", sf::Vector2f(100, 200), font);
							deathWindow.clear();
							deathWindow.draw(RIP);
							deathWindow.draw(tipBox);
							deathWindow.display();
						}

					}
					TextBlock playerName(Charsize, "Mithril Jackson", sf::Vector2f(0, 0), font);
					TextBlock CombatHpBox(Charsize, "Health:", std::to_string(Player.getCurrentHP()), std::to_string(Player.getHP()), sf::Vector2f(0, Charsize), font);
					TextBlock CombatManaBox(Charsize, "Mana:", std::to_string(Player.getCurrentMana()), std::to_string(Player.getMana()), sf::Vector2f(0, Charsize * 2), font);
					TextBlock CombatAttack(Charsize, "Press 1 to attack with your weapon", sf::Vector2f(0, Charsize*26.5), font);
					TextBlock CombatMMissile(Charsize, "Press 2 to attack with your magic (requires 10 mana)", sf::Vector2f(0, Charsize * 27.5), font);
					TextBlock CombatHeal(Charsize, "Press 3 to heal with your magic (requires 25 mana)", sf::Vector2f(0, Charsize * 28.5), font);


					TextBlock creepHPBOX(Charsize, "Health:", std::to_string(testCreep.getCurrentHP()), std::to_string(testCreep.getHP()), sf::Vector2f(650, Charsize), font);
					TextBlock creepName(Charsize, "AndyBot 122", sf::Vector2f(650, 0), font);

					TextBlock versus(Charsize, "versus", sf::Vector2f(350, Charsize), font);

					combatWindow.clear();
					/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
					{
					combatWindow.draw(lvlBox);
					}*/
					combatWindow.draw(playerName);
					combatWindow.draw(CombatManaBox);
					combatWindow.draw(CombatHpBox);

					combatWindow.draw(creepHPBOX);
					combatWindow.draw(creepName);

					combatWindow.draw(CombatAttack);
					combatWindow.draw(CombatMMissile);
					combatWindow.draw(CombatHeal);
					combatWindow.draw(versus);
					combatWindow.display();

				}
			}
		}


				animatedSprite.play(*currentAnimation);
				animatedSprite.move(movement * frameTime.asSeconds());

				// if no key was pressed stop the animation
				if (noKeyWasPressed)
				{
					animatedSprite.stop();
				}
				noKeyWasPressed = true;

				// update AnimatedSprite
				animatedSprite.update(frameTime);

				// draw
				window.clear();

				window.draw(animatedSprite);
				window.draw(manaBox);
				window.draw(hpBox);
				window.draw(xpBox);
				window.draw(lvlBox);
				window.draw(shekelBox);
				window.draw(tipBox);
				window.display();
			}
		}
