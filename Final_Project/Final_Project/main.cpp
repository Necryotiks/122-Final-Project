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

	Tower mageAscent;
	int floor = 1;
	



	// set up the animations for all four directions (set spritesheet and push frames)
	Animation walkingAnimationDown;
	Animation walkingAnimationLeft;
	Animation walkingAnimationRight;
	Animation walkingAnimationUp;
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
	walkingAnimationDown.addFrame(sf::IntRect((2 * TILE_SIZE), 0, TILE_SIZE, TILE_SIZE));
	walkingAnimationDown.addFrame(sf::IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));//finish anims.
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));


	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE));
	walkingAnimationLeft.addFrame(sf::IntRect(TILE_SIZE, (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationLeft.addFrame(sf::IntRect((2 * TILE_SIZE), TILE_SIZE, TILE_SIZE, TILE_SIZE));
	walkingAnimationLeft.addFrame(sf::IntRect(TILE_SIZE, (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationLeft.addFrame(sf::IntRect(TILE_SIZE, (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationLeft.addFrame(sf::IntRect((2 * TILE_SIZE), (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationLeft.addFrame(sf::IntRect(TILE_SIZE, (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationLeft.addFrame(sf::IntRect(0, (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));


	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(TILE_SIZE, (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationRight.addFrame(sf::IntRect((2 * TILE_SIZE), (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationRight.addFrame(sf::IntRect(TILE_SIZE, (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationRight.addFrame(sf::IntRect(0, (2 * TILE_SIZE), TILE_SIZE, TILE_SIZE));


	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(TILE_SIZE, (3 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationUp.addFrame(sf::IntRect((2 * TILE_SIZE), (3 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationUp.addFrame(sf::IntRect(TILE_SIZE, (3 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	walkingAnimationUp.addFrame(sf::IntRect(0, (3 * TILE_SIZE), TILE_SIZE, TILE_SIZE));

	Animation DeathAnimation;
	DeathAnimation.setSpriteSheet(texture);
	DeathAnimation.addFrame(sf::IntRect(0, (4 * TILE_SIZE), TILE_SIZE, TILE_SIZE));//change death animation key
	DeathAnimation.addFrame(sf::IntRect(TILE_SIZE, (4 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	DeathAnimation.addFrame(sf::IntRect((2 * TILE_SIZE), (4 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	DeathAnimation.addFrame(sf::IntRect((3 * TILE_SIZE), (4 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	DeathAnimation.addFrame(sf::IntRect((5 * TILE_SIZE), (4 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	DeathAnimation.addFrame(sf::IntRect((6 * TILE_SIZE), (4 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	DeathAnimation.addFrame(sf::IntRect((7 * TILE_SIZE), (4 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	DeathAnimation.addFrame(sf::IntRect((8 * TILE_SIZE), (4 * TILE_SIZE), TILE_SIZE, TILE_SIZE));
	DeathAnimation.addFrame(sf::IntRect((9 * TILE_SIZE), (4 * TILE_SIZE), TILE_SIZE, TILE_SIZE));

	auto * currentAnimation = &walkingAnimationDown;

	// set up AnimatedSprite
	AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	animatedSprite.setScale(.9, .9);
	animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			int x = 0, x2 = 0, y = 0, y2 = 0;
			x = (int)animatedSprite.getPosition().x + 3;
			x2 = (int)animatedSprite.getPosition().x + 23;
			y = (int)animatedSprite.getPosition().y+ 3;
			y2 = (int)animatedSprite.getPosition().y + 23;
			x = x / 32;
			x2 = x2 / 32;
			y = (y - MAP_OFFSET) / 32;
			y2 = (y2 - MAP_OFFSET) / 32;
			if (mageAscent.getCurrentFloor()->getTile(x, y)->getPassState() && mageAscent.getCurrentFloor()->getTile(x2, y)->getPassState() /*&&*/
				/*mageAscent.getCurrentFloor()->getTile(x, y + 1)->getPassState()&& mageAscent.getCurrentFloor()->getTile(x + 1, y + 1)->getPassState()*/)
			{
				currentAnimation = &walkingAnimationLeft;
				animatedSprite.setPosition((int)animatedSprite.getPosition().x, (int)animatedSprite.getPosition().y - 2);
			}
			else
			{
				currentAnimation = &walkingAnimationLeft;
				animatedSprite.setPosition((int)animatedSprite.getPosition().x, (int)animatedSprite.getPosition().y);
			}

			//Sets player to starting location based on floor!
			if (mageAscent.getCurrentFloor()->getTile(x, y)->getType() == STAIRS || mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == STAIRS)
			{
				floor++; 
				switch (floor)
				{
				case 2: 
					mageAscent.nextFloor();
					animatedSprite.setPosition(23 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					break;
				case 3:
					animatedSprite.setPosition(2 * TILE_SIZE, MAP_OFFSET + 1 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 4:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 5:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 6:
					animatedSprite.setPosition(20 * TILE_SIZE, MAP_OFFSET + 7 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 7:
					animatedSprite.setPosition(1 * TILE_SIZE, MAP_OFFSET + 1 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 8:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 9:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 10:
					animatedSprite.setPosition(23 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 11:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 12:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				}
			}

			//Gives loot for walking over chests, maybe add exp bonus?
			if ((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == CHEST || mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == CHEST) && 
				(mageAscent.getCurrentFloor()->getTile(x, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y)->getInteractState()))
			{
				Player.setShekels(Player.getShekels() + 100);
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
			}

			//Trap tile with dmg calc
			if ((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == TRAP || mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == TRAP) &&
				(mageAscent.getCurrentFloor()->getTile(x, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y)->getInteractState()))
			{
				Player.setCurrentHP(Player.getCurrentHP() - (10 * floor));
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
			}

			//Creature event happens. 
			if ((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == MOB || mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == MOB) &&
				(mageAscent.getCurrentFloor()->getTile(x, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y)->getInteractState()))
			{
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
				Creature testCreep("AndyBot", 50 * floor, 5 * floor, 10);
				sf::RenderWindow combatWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Fight!", sf::Style::Titlebar);
				combatWindow.setFramerateLimit(60);
				//set combat resolve time
				while (combatWindow.isOpen())
				{
					sf::Event combatEvent;
					while (combatWindow.pollEvent(combatEvent))
					{
						if (combatEvent.type == sf::Event::Closed)
							combatWindow.close();
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num1)
						{	//Melee attack
							testCreep.dmgCalc(Player.hitDmg());//player attacks creep, creep takes damage
							if (testCreep.getCurrentHP() <= 0)
							{
								int bullshit = 300 * floor, mana = 100;
								Player.awardXP(bullshit);
								if (Player.getCurrentXP() >= Player.getNextXP())
								{
									Player.setCurrentLVL(1);
									Player.set_strength(5);
									Player.setHP(Player.getHP() + 50);
								}
								Player.setCurrentMana(mana);
								combatWindow.close();
							}//else keep fighting!
							Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num2)
						{	//Magic attack
							if (Player.getCurrentMana() >= 10)
							{
								testCreep.dmgCalc(Player.magicMissileDmg());//player attacks creep, creep takes damage
								if (testCreep.getCurrentHP() <= 0)
								{
									int bullshit = 300 * floor, mana = 100;
									Player.awardXP(bullshit);
									if (Player.getCurrentXP() >= Player.getNextXP())
									{
										Player.setCurrentLVL(1);
										Player.set_strength(5);
										Player.setHP(Player.getHP() + 50);
									}
									Player.setCurrentMana(mana);
									combatWindow.close();
								}//else keep fighting!
								Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
							}
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num3)
						{	//Heal
							if (Player.getCurrentMana() >= 25)
							{
								Player.healHP();
								Player.dmgCalc(testCreep.hitDmg());
								//creep attacks, player takes damage

							}
						}

						//end Event Handler

						if (Player.getCurrentHP() <= 0)
						{
							sf::Image DIMG;
							DIMG.loadFromFile("Destinydark.jpg");
							DIMG.createMaskFromColor(sf::Color::Black);
							sf::Texture XV;
							XV.loadFromImage(DIMG);
							//DIMG.setSmooth(true);
							sf::Sprite UDED;
							UDED.setTexture(XV);
							UDED.setScale(.75, .75);
							UDED.setPosition(195, 0);
							sf::Font DFONT;
							if (!DFONT.loadFromFile("Origicide.ttf"))
							{
								//throw error
							}
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
								TextBlock RIP(Charsize * 5, "YOU DIED", sf::Vector2f(200, 400), DFONT);
								RIP.setFillColor(sf::Color::Red);
								deathWindow.clear();
								deathWindow.draw(RIP);
								deathWindow.draw(UDED);
								deathWindow.draw(tipBox);
								//get image here.
								deathWindow.display();
							}
							exit(1);
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


			noKeyWasPressed = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			int x = 0, x2 = 0, y = 0, y2 = 0;
			x = (int)animatedSprite.getPosition().x + 3;
			x2 = (int)animatedSprite.getPosition().x + 23;
			y = (int)animatedSprite.getPosition().y + 3;
			y2 = (int)animatedSprite.getPosition().y + 23;
			x = x / 32;
			x2 = x2 / 32;
			y = (y - MAP_OFFSET) / 32;
			y2 = (y2 - MAP_OFFSET) / 32;
			if (/*mageAscent.getCurrentFloor()->getTile(x, y)->getPassState() && mageAscent.getCurrentFloor()->getTile(x + 1, y)->getPassState() &&*/
				mageAscent.getCurrentFloor()->getTile(x, y2)->getPassState() && mageAscent.getCurrentFloor()->getTile(x2, y2)->getPassState())
			{
				currentAnimation = &walkingAnimationLeft;
				animatedSprite.setPosition((int)animatedSprite.getPosition().x, (int)animatedSprite.getPosition().y + 2);
			}
			else 
			{
				currentAnimation = &walkingAnimationLeft;
				animatedSprite.setPosition((int)animatedSprite.getPosition().x, (int)animatedSprite.getPosition().y);
			}
			if (mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == STAIRS || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == STAIRS)
			{
				floor++;
				switch (floor)
				{
				case 2:
					mageAscent.nextFloor();
					animatedSprite.setPosition(23 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					break;
				case 3:
					animatedSprite.setPosition(2 * TILE_SIZE, MAP_OFFSET + 1 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 4:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 5:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 6:
					animatedSprite.setPosition(20 * TILE_SIZE, MAP_OFFSET + 7 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 7:
					animatedSprite.setPosition(1 * TILE_SIZE, MAP_OFFSET + 1 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 8:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 9:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 10:
					animatedSprite.setPosition(23 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 11:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 12:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				}
			}

			//Gives loot for walking over chests, maybe add exp bonus?
			if ((mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == CHEST || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == CHEST) &&
				(mageAscent.getCurrentFloor()->getTile(x, y2)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y2)->getInteractState()))
			{
				Player.setShekels(Player.getShekels() + 100);
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
			}

			//Trap tile with dmg calc
			if ((mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == TRAP || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == TRAP) &&
				(mageAscent.getCurrentFloor()->getTile(x, y2)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y2)->getInteractState()))
			{
				Player.setCurrentHP(Player.getCurrentHP() - (10 * floor));
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
			}

			//Creature event happens. 
			if ((mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == MOB || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == MOB) &&
				(mageAscent.getCurrentFloor()->getTile(x, y2)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y2)->getInteractState()))
			{
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
				Creature testCreep("AndyBot", 50 * floor, 5 * floor, 10);
				sf::RenderWindow combatWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Fight!", sf::Style::Titlebar);
				combatWindow.setFramerateLimit(60);
				//set combat resolve time
				while (combatWindow.isOpen())
				{
					sf::Event combatEvent;
					while (combatWindow.pollEvent(combatEvent))
					{
						if (combatEvent.type == sf::Event::Closed)
							combatWindow.close();
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num1)
						{	//Melee attack
							testCreep.dmgCalc(Player.hitDmg());//player attacks creep, creep takes damage
							if (testCreep.getCurrentHP() <= 0)
							{
								int bullshit = 300 * floor, mana = 100;
								Player.awardXP(bullshit);
								if (Player.getCurrentXP() >= Player.getNextXP())
								{
									Player.setCurrentLVL(1);
									Player.set_strength(5);
									Player.setHP(Player.getHP() + 50);
								}
								Player.setCurrentMana(mana);
								combatWindow.close();
							}//else keep fighting!
							Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num2)
						{	//Magic attack
							if (Player.getCurrentMana() >= 10)
							{
								testCreep.dmgCalc(Player.magicMissileDmg());//player attacks creep, creep takes damage
								if (testCreep.getCurrentHP() <= 0)
								{
									int bullshit = 300 * floor, mana = 100;
									Player.awardXP(bullshit);
									if (Player.getCurrentXP() >= Player.getNextXP())
									{
										Player.setCurrentLVL(1);
										Player.set_strength(5);
										Player.setHP(Player.getHP() + 50);
									}
									Player.setCurrentMana(mana);
									combatWindow.close();
								}//else keep fighting!
								Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
							}
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num3)
						{	//Heal
							if (Player.getCurrentMana() >= 25)
							{
								Player.healHP();
								Player.dmgCalc(testCreep.hitDmg());
								//creep attacks, player takes damage

							}
						}

						//end Event Handler

						if (Player.getCurrentHP() <= 0)
						{
							sf::Image DIMG;
							DIMG.loadFromFile("Destinydark.jpg");
							DIMG.createMaskFromColor(sf::Color::Black);
							sf::Texture XV;
							XV.loadFromImage(DIMG);
							//DIMG.setSmooth(true);
							sf::Sprite UDED;
							UDED.setTexture(XV);
							UDED.setScale(.75, .75);
							UDED.setPosition(195, 0);
							sf::Font DFONT;
							if (!DFONT.loadFromFile("Origicide.ttf"))
							{
								//throw error
							}
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
								TextBlock RIP(Charsize * 5, "YOU DIED", sf::Vector2f(200, 400), DFONT);
								RIP.setFillColor(sf::Color::Red);
								deathWindow.clear();
								deathWindow.draw(RIP);
								deathWindow.draw(UDED);
								deathWindow.draw(tipBox);
								//get image here.
								deathWindow.display();
							}
							exit(1);
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
			noKeyWasPressed = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			int x = 0, x2 = 0, y = 0, y2 = 0;
			x = (int)animatedSprite.getPosition().x + 3;
			x2 = (int)animatedSprite.getPosition().x + 23;
			y = (int)animatedSprite.getPosition().y + 3;
			y2 = (int)animatedSprite.getPosition().y + 23;
			x = x / 32;
			x2 = x2 / 32;
			y = (y - MAP_OFFSET) / 32;
			y2 = (y2 - MAP_OFFSET) / 32;
			if (mageAscent.getCurrentFloor()->getTile(x, y)->getPassState() &&/* mageAscent.getCurrentFloor()->getTile(x + 1, y)->getPassState() &&*/
				mageAscent.getCurrentFloor()->getTile(x, y2)->getPassState()/* && mageAscent.getCurrentFloor()->getTile(x + 1, y + 1)->getPassState()*/)
			{
				currentAnimation = &walkingAnimationRight;
				animatedSprite.setPosition((int)animatedSprite.getPosition().x - 2, (int)animatedSprite.getPosition().y);
			}
			else
			{
				currentAnimation = &walkingAnimationRight;
				animatedSprite.setPosition((int)animatedSprite.getPosition().x, (int)animatedSprite.getPosition().y);
			}
			if (mageAscent.getCurrentFloor()->getTile(x, y)->getType() == STAIRS || mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == STAIRS)
			{
				floor++;
				switch (floor)
				{
				case 2:
					mageAscent.nextFloor();
					animatedSprite.setPosition(23 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					break;
				case 3:
					animatedSprite.setPosition(2 * TILE_SIZE, MAP_OFFSET + 1 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 4:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 5:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 6:
					animatedSprite.setPosition(20 * TILE_SIZE, MAP_OFFSET + 7 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 7:
					animatedSprite.setPosition(1 * TILE_SIZE, MAP_OFFSET + 1 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 8:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 9:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 10:
					animatedSprite.setPosition(23 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 11:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 12:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				}
			}

			//Gives loot for walking over chests, maybe add exp bonus?
			if ((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == CHEST || mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == CHEST) &&
				(mageAscent.getCurrentFloor()->getTile(x, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x, y2)->getInteractState()))
			{
				Player.setShekels(Player.getShekels() + 100);
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
			}

			//Trap tile with dmg calc
			if ((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == TRAP || mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == TRAP) &&
				(mageAscent.getCurrentFloor()->getTile(x, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x, y2)->getInteractState()))
			{
				Player.setCurrentHP(Player.getCurrentHP() - (10 * floor));
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
			}

			//Creature event happens. 
			if ((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == MOB || mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == MOB) &&
				(mageAscent.getCurrentFloor()->getTile(x, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x, y2)->getInteractState()))
			{
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
				Creature testCreep("AndyBot", 50 * floor, 5 * floor, 10);
				sf::RenderWindow combatWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Fight!", sf::Style::Titlebar);
				combatWindow.setFramerateLimit(60);
				//set combat resolve time
				while (combatWindow.isOpen())
				{
					sf::Event combatEvent;
					while (combatWindow.pollEvent(combatEvent))
					{
						if (combatEvent.type == sf::Event::Closed)
							combatWindow.close();
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num1)
						{	//Melee attack
							testCreep.dmgCalc(Player.hitDmg());//player attacks creep, creep takes damage
							if (testCreep.getCurrentHP() <= 0)
							{
								int bullshit = 300 * floor, mana = 100;
								Player.awardXP(bullshit);
								if (Player.getCurrentXP() >= Player.getNextXP())
								{
									Player.setCurrentLVL(1);
									Player.set_strength(5);
									Player.setHP(Player.getHP() + 50);
								}
								Player.setCurrentMana(mana);
								combatWindow.close();
							}//else keep fighting!
							Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num2)
						{	//Magic attack
							if (Player.getCurrentMana() >= 10)
							{
								testCreep.dmgCalc(Player.magicMissileDmg());//player attacks creep, creep takes damage
								if (testCreep.getCurrentHP() <= 0)
								{
									int bullshit = 300 * floor, mana = 100;
									Player.awardXP(bullshit);
									if (Player.getCurrentXP() >= Player.getNextXP())
									{
										Player.setCurrentLVL(1);
										Player.set_strength(5);
										Player.setHP(Player.getHP() + 50);
									}
									Player.setCurrentMana(mana);
									combatWindow.close();
								}//else keep fighting!
								Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
							}
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num3)
						{	//Heal
							if (Player.getCurrentMana() >= 25)
							{
								Player.healHP();
								Player.dmgCalc(testCreep.hitDmg());
								//creep attacks, player takes damage

							}
						}

						//end Event Handler

						if (Player.getCurrentHP() <= 0)
						{
							sf::Image DIMG;
							DIMG.loadFromFile("Destinydark.jpg");
							DIMG.createMaskFromColor(sf::Color::Black);
							sf::Texture XV;
							XV.loadFromImage(DIMG);
							//DIMG.setSmooth(true);
							sf::Sprite UDED;
							UDED.setTexture(XV);
							UDED.setScale(.75, .75);
							UDED.setPosition(195, 0);
							sf::Font DFONT;
							if (!DFONT.loadFromFile("Origicide.ttf"))
							{
								//throw error
							}
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
								TextBlock RIP(Charsize * 5, "YOU DIED", sf::Vector2f(200, 400), DFONT);
								RIP.setFillColor(sf::Color::Red);
								deathWindow.clear();
								deathWindow.draw(RIP);
								deathWindow.draw(UDED);
								deathWindow.draw(tipBox);
								//get image here.
								deathWindow.display();
							}
							exit(1);
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
			noKeyWasPressed = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			int x = 0, x2 = 0, y = 0, y2 = 0;
			x = (int)animatedSprite.getPosition().x + 3;
			x2 = (int)animatedSprite.getPosition().x + 23;
			y = (int)animatedSprite.getPosition().y + 3;
			y2 = (int)animatedSprite.getPosition().y + 23;
			x = x / 32;
			x2 = x2 / 32;
			y = (y - MAP_OFFSET) / 32;
			y2 = (y2 - MAP_OFFSET) / 32;
			if (/*mageAscent.getCurrentFloor()->getTile(x, y)->getPassState() && */mageAscent.getCurrentFloor()->getTile(x2, y)->getPassState() &&
				/*mageAscent.getCurrentFloor()->getTile(x, y + 1)->getPassState() && */mageAscent.getCurrentFloor()->getTile(x2, y2)->getPassState())
			{
				currentAnimation = &walkingAnimationLeft;
				animatedSprite.setPosition((int)animatedSprite.getPosition().x + 2, (int)animatedSprite.getPosition().y);
			}
			else
			{
				currentAnimation = &walkingAnimationLeft;
				animatedSprite.setPosition((int)animatedSprite.getPosition().x, (int)animatedSprite.getPosition().y);
			}
			if (mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == STAIRS || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == STAIRS)
			{
				floor++;
				switch (floor)
				{
				case 2:
					mageAscent.nextFloor();
					animatedSprite.setPosition(23 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					break;
				case 3:
					animatedSprite.setPosition(2 * TILE_SIZE, MAP_OFFSET + 1 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 4:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 5:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 6:
					animatedSprite.setPosition(20 * TILE_SIZE, MAP_OFFSET + 7 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 7:
					animatedSprite.setPosition(1 * TILE_SIZE, MAP_OFFSET + 1 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 8:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 9:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 10:
					animatedSprite.setPosition(23 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 11:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 14 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				case 12:
					animatedSprite.setPosition(12 * TILE_SIZE, MAP_OFFSET + 12 * TILE_SIZE);
					mageAscent.nextFloor();
					break;
				}
			}

			//Gives loot for walking over chests, maybe add exp bonus?
			if ((mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == CHEST || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == CHEST) &&
				(mageAscent.getCurrentFloor()->getTile(x2, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y2)->getInteractState()))
			{
				Player.setShekels(Player.getShekels() + 100);
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
			}

			//Trap tile with dmg calc
			if ((mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == TRAP || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == TRAP) &&
				(mageAscent.getCurrentFloor()->getTile(x2, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y2)->getInteractState()))
			{
				Player.setCurrentHP(Player.getCurrentHP() - (10 * floor));
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
			}

			//Creature event happens. 
			if ((mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == MOB || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == MOB) &&
				(mageAscent.getCurrentFloor()->getTile(x2, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y2)->getInteractState()))
			{
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
				Creature testCreep("AndyBot", 50 * floor, 5 * floor, 10);
				sf::RenderWindow combatWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Fight!", sf::Style::Titlebar);
				combatWindow.setFramerateLimit(60);
				//set combat resolve time
				while (combatWindow.isOpen())
				{
					sf::Event combatEvent;
					while (combatWindow.pollEvent(combatEvent))
					{
						if (combatEvent.type == sf::Event::Closed)
							combatWindow.close();
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num1)
						{	//Melee attack
							testCreep.dmgCalc(Player.hitDmg());//player attacks creep, creep takes damage
							if (testCreep.getCurrentHP() <= 0)
							{
								int bullshit = 300 * floor, mana = 100;
								Player.awardXP(bullshit);
								if (Player.getCurrentXP() >= Player.getNextXP())
								{
									Player.setCurrentLVL(1);
									Player.set_strength(5);
									Player.setHP(Player.getHP() + 50);
								}
								Player.setCurrentMana(mana);
								combatWindow.close();
							}//else keep fighting!
							Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num2)
						{	//Magic attack
							if (Player.getCurrentMana() >= 10)
							{
								testCreep.dmgCalc(Player.magicMissileDmg());//player attacks creep, creep takes damage
								if (testCreep.getCurrentHP() <= 0)
								{
									int bullshit = 300 * floor, mana = 100;
									Player.awardXP(bullshit);
									if (Player.getCurrentXP() >= Player.getNextXP())
									{
										Player.setCurrentLVL(1);
										Player.set_strength(5);
										Player.setHP(Player.getHP() + 50);
									}
									Player.setCurrentMana(mana);
									combatWindow.close();
								}//else keep fighting!
								Player.dmgCalc(testCreep.hitDmg());//creep attacks, player takes damage
							}
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num3)
						{	//Heal
							if (Player.getCurrentMana() >= 25)
							{
								Player.healHP();
								Player.dmgCalc(testCreep.hitDmg());
								//creep attacks, player takes damage

							}
						}

						//end Event Handler

						if (Player.getCurrentHP() <= 0)
						{
							sf::Image DIMG;
							DIMG.loadFromFile("Destinydark.jpg");
							DIMG.createMaskFromColor(sf::Color::Black);
							sf::Texture XV;
							XV.loadFromImage(DIMG);
							//DIMG.setSmooth(true);
							sf::Sprite UDED;
							UDED.setTexture(XV);
							UDED.setScale(.75, .75);
							UDED.setPosition(195, 0);
							sf::Font DFONT;
							if (!DFONT.loadFromFile("Origicide.ttf"))
							{
								//throw error
							}
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
								TextBlock RIP(Charsize * 5, "YOU DIED", sf::Vector2f(200, 400), DFONT);
								RIP.setFillColor(sf::Color::Red);
								deathWindow.clear();
								deathWindow.draw(RIP);
								deathWindow.draw(UDED);
								deathWindow.draw(tipBox);
								//get image here.
								deathWindow.display();
							}
							exit(1);
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
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			currentAnimation = &DeathAnimation;
			noKeyWasPressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			mageAscent.nextFloor();
			system("pause");
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

				TextBlock hpBox(Charsize, "Health:", std::to_string(Player.getCurrentHP()), std::to_string(Player.getHP()), sf::Vector2f(0, 0), font);
				TextBlock manaBox(Charsize, "Mana:", std::to_string(Player.getCurrentMana()), std::to_string(Player.getMana()), sf::Vector2f(150, 0), font);
				TextBlock xpBox(Charsize, "XP:", std::to_string(Player.getCurrentXP()), std::to_string(Player.getNextXP()), sf::Vector2f(150, Charsize), font);
				TextBlock lvlBox(Charsize, "LVL:", std::to_string(Player.getCurrentLVL()), sf::Vector2f(0, Charsize), font);
				TextBlock shekelBox(Charsize, "Shekels:", std::to_string(Player.getShekels()), sf::Vector2f(290, 0), font);

				mageAscent.getCurrentFloor()->printFloor(window);
				window.draw(animatedSprite);
				window.draw(manaBox);
				window.draw(hpBox);
				window.draw(xpBox);
				window.draw(lvlBox);
				window.draw(shekelBox);
				window.draw(tipBox);
				window.display();
				mageAscent.getCurrentFloor()->playBgm();
			}
		}
