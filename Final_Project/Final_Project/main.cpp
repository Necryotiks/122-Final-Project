#include "Source.h"
#include "Creature.h"
#include "Tower.h"
#include "TextBlock.h"
#include "PlayerCharacter.h"
//#include "Item.h"



int main()
{
	int selection = 0;

	do
	{
		cout << "Enter 1-16 to select character:" << endl;
		cin >> selection;
	} while ((selection < 1) && (selection > 16));

	
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
	if (!texture.loadFromFile("CharSprites/" + std::to_string(selection) + ".png"))
	{
		std::cout << "Failed to load player spritesheet!" << std::endl;
		return 1;
	}

	sf::Music battle;
	if (!battle.openFromFile("Music\\battle.ogg"))
	{
		std::cout << "Bad load." << std::endl; //error message
	}

	sf::Music deathKnell;
	if (!deathKnell.openFromFile("Music\\death.ogg"))
	{
		std::cout << "Bad load." << std::endl; //error message
	}
	deathKnell.setLoop(true);

	sf::Music victory;
	if (!victory.openFromFile("Music\\victory.wav"))
	{
		std::cout << "Bad load." << std::endl; //error message
	}

	Tower mageAscent;

	/*Start Title Screen code*/

	sf::RenderWindow titleWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "The Perils of Aeliorn: Mage's Tower Ascent");
	titleWindow.setFramerateLimit(60);

	sf::Vector2f targetSize((float)titleWindow.getSize().x, (float)titleWindow.getSize().y);

	sf::Texture titleScreen;
	titleScreen.loadFromFile("tower.jpg");

	sf::Image title;
	title.loadFromFile("titlescroll.png");
	title.createMaskFromColor(sf::Color::Black);
	sf::Texture titleTexture;
	titleTexture.loadFromImage(title);

	sf::Sprite titleSprite;
	titleSprite.setTexture(titleScreen);
	titleSprite.scale(
		targetSize.x / titleSprite.getLocalBounds().width,
		targetSize.y / titleSprite.getLocalBounds().height);

	sf::Texture combatBG;
	combatBG.loadFromFile("combatBG.png");

	sf::Sprite combatBgSprite(combatBG);
	combatBgSprite.scale(
		targetSize.x / combatBgSprite.getLocalBounds().width,
		targetSize.y / combatBgSprite.getLocalBounds().height);


	sf::Sprite titleScroll;
	titleScroll.setTexture(titleTexture);
	titleScroll.setPosition(((float)TILE_SIZE / 2), (float)((titleWindow.getSize().y / 2)) - (titleScroll.getLocalBounds().height / 2));
	titleScroll.scale((targetSize.x - TILE_SIZE) / titleScroll.getLocalBounds().width, 1);

	TextBlock instructions((Charsize * 1.25), "Press any key to START", sf::Vector2f(((targetSize.x / 2) - (5 * TILE_SIZE)), ((targetSize.y / 2) + (3 * TILE_SIZE))), font);
	instructions.setFillColor(sf::Color(174, 174, 210));
	instructions.setOutlineThickness(2.0f);
	instructions.setOutlineColor(sf::Color::Black);

	TextBlock instructions2((Charsize * 1.25), "W = up, A = left, S = down, D = right", sf::Vector2f(((targetSize.x / 2) - (5 * TILE_SIZE)), ((targetSize.y / 2) + (5 * TILE_SIZE))), font);
	instructions2.setFillColor(sf::Color(174, 174, 210));
	instructions2.setOutlineThickness(2.0f);
	instructions2.setOutlineColor(sf::Color::Black);

	//light purple (224,224,255)
	//medium purple (174,174,210)
	//dark purple (112,112,157)

	sf::Music titleBgm;
	titleBgm.openFromFile("Music\\intro.ogg");
	titleBgm.setLoop(true);
	titleBgm.play();

	while (titleWindow.isOpen())
	{
		sf::Event titleEvent;


		while (titleWindow.pollEvent(titleEvent))
		{
			if (titleEvent.type == sf::Event::KeyPressed)
			{
				titleBgm.stop();
				titleWindow.close();
			}

		}

		// draw title
		titleWindow.clear();
		titleWindow.draw(titleSprite);
		titleWindow.draw(titleScroll);
		titleWindow.draw(instructions);
		titleWindow.draw(instructions2);
		titleWindow.display();
	}
	/*End Title Screen Code*/
	



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
	animatedSprite.setPosition(mageAscent.getCurrentFloor()->getStartPosition());

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
			y = (y - MAP_OFFSET) / TILE_SIZE;
			y2 = (y2 - MAP_OFFSET) / TILE_SIZE;
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
				animatedSprite.setPosition(mageAscent.nextFloor());
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
				Player.setCurrentHP(Player.getCurrentHP() - (10 * mageAscent.getCurrentFloorNumber()));
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
			}

			//Creature event happens. 
			if (((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == MOB || mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == MOB)||
				(mageAscent.getCurrentFloor()->getTile(x, y)->getType() == MINI || mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == MINI) ||
				(mageAscent.getCurrentFloor()->getTile(x, y)->getType() == BOSS || mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == BOSS)) &&
				(mageAscent.getCurrentFloor()->getTile(x, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y)->getInteractState()))
			{
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
				Creature testCreep("AndyBot", 50 * mageAscent.getCurrentFloorNumber(), 5 * mageAscent.getCurrentFloorNumber(), 10);
				if ((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == MOB || mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == MOB))
				{
					testCreep.setXP(10);
				}
				else if ((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == MINI || mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == MINI))
				{
					testCreep.setXP(42);
					testCreep.setHP(400);
					testCreep.setCurrentHP(400);
					testCreep.set_strength(20);
				}
				else
				{
					testCreep.setXP(45);
					testCreep.setHP(2500);
					testCreep.setCurrentHP(2500);
					testCreep.set_strength(50);
				}
				sf::RenderWindow combatWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Fight!", sf::Style::Titlebar);
				combatWindow.setFramerateLimit(60);
				//set combat resolve time
				
				mageAscent.getCurrentFloor()->stopBgm();

				if (combatWindow.hasFocus())
					battle.play();
				else
					battle.stop();

				while (combatWindow.isOpen())
				{

					sf::Event combatEvent;
					while (combatWindow.pollEvent(combatEvent))
					{
						if (combatEvent.type == sf::Event::Closed)
						{
							combatWindow.close();
							battle.stop();
							mageAscent.getCurrentFloor()->playBgm();
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num1)
						{	//Melee attack
							testCreep.dmgCalc(Player.hitDmg());//player attacks creep, creep takes damage
							if (testCreep.getCurrentHP() <= 0)
							{
								victory.play();
								int experiencePoints = 300 * mageAscent.getCurrentFloorNumber(), mana = 100;
								Player.awardXP(experiencePoints);
								if (Player.getCurrentXP() >= Player.getNextXP())
								{
									Player.setCurrentLVL(1);
									Player.set_strength(5);
									Player.setHP(Player.getHP() + 50);
								}
								Player.setCurrentMana(mana);
								combatWindow.close();
								battle.stop();
								mageAscent.getCurrentFloor()->playBgm();
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
									victory.play();
									int experiencePoints = 300 * mageAscent.getCurrentFloorNumber(), mana = 100;
									Player.awardXP(experiencePoints);
									if (Player.getCurrentXP() >= Player.getNextXP())
									{
										Player.setCurrentLVL(1);
										Player.set_strength(5);
										Player.setHP(Player.getHP() + 50);
									}
									Player.setCurrentMana(mana);
									combatWindow.close();
									battle.stop();
									mageAscent.getCurrentFloor()->playBgm();
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
							battle.stop();
							sf::RenderWindow deathWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "RIP", sf::Style::Titlebar);
							mageAscent.getCurrentFloor()->stopBgm();

							if (deathWindow.hasFocus())
								deathKnell.play();
							else
								deathKnell.stop();

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
						TextBlock playerName(Charsize, "Brave Adventurer", sf::Vector2f(0, 0), font);
						TextBlock CombatHpBox(Charsize, "Health:", std::to_string(Player.getCurrentHP()), std::to_string(Player.getHP()), sf::Vector2f(0, Charsize), font);
						TextBlock CombatManaBox(Charsize, "Mana:", std::to_string(Player.getCurrentMana()), std::to_string(Player.getMana()), sf::Vector2f(0, Charsize * 2), font);
						TextBlock CombatAttack(Charsize, "Press 1 to attack with your weapon", sf::Vector2f(0, Charsize*26.5), font);
						TextBlock CombatMMissile(Charsize, "Press 2 to attack with your magic (requires 10 mana)", sf::Vector2f(0, Charsize * 27.5), font);
						TextBlock CombatHeal(Charsize, "Press 3 to heal with your magic (requires 25 mana)", sf::Vector2f(0, Charsize * 28.5), font);


						TextBlock creepHPBOX(Charsize, "Health:", std::to_string(testCreep.getCurrentHP()), std::to_string(testCreep.getHP()), sf::Vector2f(600, Charsize), font);
						

						TextBlock versus(Charsize, "versus", sf::Vector2f(350, Charsize), font);

						combatWindow.clear();
						/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
						{
						combatWindow.draw(lvlBox);
						}*/

						sf::Texture highreshero;
						sf::Texture highresogre;
						highreshero.loadFromFile("CharSprites/hero.png");
						highresogre.loadFromFile("CharSprites/ogre.png");
						sf::Sprite combathero;
						sf::Sprite combatogre;
						combathero.setTexture(highreshero);
						combatogre.setTexture(highresogre);
						combathero.setPosition(5.0f, 75.0f);
						combathero.setScale(0.4f, 0.4f);
						combatogre.setPosition(435.0f, 50.0f);
						combatogre.setScale(0.5f, 0.5f);

						if (testCreep.getXP() == 42)
						{
							sf::Texture miniboss;
							miniboss.loadFromFile("CharSprites/miniboss.png");
							sf::Sprite mini;
							mini.setTexture(miniboss);
							mini.setPosition(240.0f, 125.0f);
							mini.setScale(0.4f, 0.4f);
							TextBlock creepName(Charsize, "Minotard", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(mini);
						}
						else if (testCreep.getXP() == 45)
						{
							sf::Texture mainboss;
							mainboss.loadFromFile("CharSprites/mainboss.png");
							sf::Sprite main;
							main.setTexture(mainboss);
							main.setPosition(500.0f, 72.5f);
							main.setScale(0.6f, 0.6f);
							TextBlock creepName(Charsize, "Necromancer", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(main);
						}
						else
						{
							sf::Texture highresogre;
							highresogre.loadFromFile("CharSprites/ogre.png");
							sf::Sprite combatogre;
							combatogre.setTexture(highresogre);
							combatogre.setPosition(435.0f, 50.0f);
							combatogre.setScale(0.5f, 0.5f);
							TextBlock creepName(Charsize, "Ogricus", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(combatogre);
						}


						combatWindow.draw(playerName);
						combatWindow.draw(CombatManaBox);
						combatWindow.draw(CombatHpBox);

						combatWindow.draw(combathero);
						combatWindow.draw(creepHPBOX);

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
				animatedSprite.setPosition(mageAscent.nextFloor());
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
				Player.setCurrentHP(Player.getCurrentHP() - (10 * mageAscent.getCurrentFloorNumber()));
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
			}

			//Creature event happens. 
			if ((mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == MOB || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == MOB) &&
				(mageAscent.getCurrentFloor()->getTile(x, y2)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y2)->getInteractState()))
			{
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
				Creature testCreep("AndyBot", 50 * mageAscent.getCurrentFloorNumber(), 5 * mageAscent.getCurrentFloorNumber(), 10);
				sf::RenderWindow combatWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Fight!", sf::Style::Titlebar);
				combatWindow.setFramerateLimit(60);
				//set combat resolve time
				mageAscent.getCurrentFloor()->stopBgm(); 
				
				if (combatWindow.hasFocus())
					battle.play();
				else
					battle.stop();
				
				while (combatWindow.isOpen())
				{

					sf::Event combatEvent;
					while (combatWindow.pollEvent(combatEvent))
					{
						if (combatEvent.type == sf::Event::Closed)
						{
							combatWindow.close();
							battle.stop();
							mageAscent.getCurrentFloor()->playBgm();
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num1)
						{	//Melee attack
							testCreep.dmgCalc(Player.hitDmg());//player attacks creep, creep takes damage
							if (testCreep.getCurrentHP() <= 0)
							{
								victory.play();
								int experiencePoints = 300 * mageAscent.getCurrentFloorNumber(), mana = 100;
								Player.awardXP(experiencePoints);
								if (Player.getCurrentXP() >= Player.getNextXP())
								{
									Player.setCurrentLVL(1);
									Player.set_strength(5);
									Player.setHP(Player.getHP() + 50);
								}
								Player.setCurrentMana(mana);
								combatWindow.close();
								battle.stop();
								mageAscent.getCurrentFloor()->playBgm();
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
									victory.play();
									int experiencePoints = 300 * mageAscent.getCurrentFloorNumber(), mana = 100;
									Player.awardXP(experiencePoints);
									if (Player.getCurrentXP() >= Player.getNextXP())
									{
										Player.setCurrentLVL(1);
										Player.set_strength(5);
										Player.setHP(Player.getHP() + 50);
									}
									Player.setCurrentMana(mana);
									combatWindow.close();
									battle.stop();
									mageAscent.getCurrentFloor()->playBgm();
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
							battle.stop();
							sf::RenderWindow deathWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "RIP", sf::Style::Titlebar);
							mageAscent.getCurrentFloor()->stopBgm();

							if (deathWindow.hasFocus())
								deathKnell.play();
							else
								deathKnell.stop();
							
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
						TextBlock playerName(Charsize, "Brave Adventurer", sf::Vector2f(0, 0), font);
						TextBlock CombatHpBox(Charsize, "Health:", std::to_string(Player.getCurrentHP()), std::to_string(Player.getHP()), sf::Vector2f(0, Charsize), font);
						TextBlock CombatManaBox(Charsize, "Mana:", std::to_string(Player.getCurrentMana()), std::to_string(Player.getMana()), sf::Vector2f(0, Charsize * 2), font);
						TextBlock CombatAttack(Charsize, "Press 1 to attack with your weapon", sf::Vector2f(0, Charsize*26.5), font);
						TextBlock CombatMMissile(Charsize, "Press 2 to attack with your magic (requires 10 mana)", sf::Vector2f(0, Charsize * 27.5), font);
						TextBlock CombatHeal(Charsize, "Press 3 to heal with your magic (requires 25 mana)", sf::Vector2f(0, Charsize * 28.5), font);


						TextBlock creepHPBOX(Charsize, "Health:", std::to_string(testCreep.getCurrentHP()), std::to_string(testCreep.getHP()), sf::Vector2f(600, Charsize), font);
						TextBlock creepName(Charsize, "AndyBot 122", sf::Vector2f(650, 0), font);

						TextBlock versus(Charsize, "versus", sf::Vector2f(350, Charsize), font);

						combatWindow.clear();
						/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
						{
						combatWindow.draw(lvlBox);
						}*/
						sf::Texture highreshero;
						sf::Texture highresogre;
						highreshero.loadFromFile("CharSprites/hero.png");
						highresogre.loadFromFile("CharSprites/ogre.png");
						sf::Sprite combathero;
						sf::Sprite combatogre;
						combathero.setTexture(highreshero);
						combatogre.setTexture(highresogre);
						combathero.setPosition(5.0f, 75.0f);
						combathero.setScale(0.4f, 0.4f);
						combatogre.setPosition(435.0f, 50.0f);
						combatogre.setScale(0.5f, 0.5f);

						if (testCreep.getXP() == 42)
						{
							sf::Texture miniboss;
							miniboss.loadFromFile("CharSprites/miniboss.png");
							sf::Sprite mini;
							mini.setTexture(miniboss);
							mini.setPosition(240.0f, 125.0f);
							mini.setScale(0.4f, 0.4f);
							TextBlock creepName(Charsize, "Minotard", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(mini);
						}
						else if (testCreep.getXP() == 45)
						{
							sf::Texture mainboss;
							mainboss.loadFromFile("CharSprites/mainboss.png");
							sf::Sprite main;
							main.setTexture(mainboss);
							main.setPosition(500.0f, 72.5f);
							main.setScale(0.6f, 0.6f);
							TextBlock creepName(Charsize, "Necromancer", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(main);
						}
						else
						{
							sf::Texture highresogre;
							highresogre.loadFromFile("CharSprites/ogre.png");
							sf::Sprite combatogre;
							combatogre.setTexture(highresogre);
							combatogre.setPosition(435.0f, 50.0f);
							combatogre.setScale(0.5f, 0.5f);
							TextBlock creepName(Charsize, "Ogricus", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(combatogre);
						}


						combatWindow.draw(playerName);
						combatWindow.draw(CombatManaBox);
						combatWindow.draw(CombatHpBox);

						combatWindow.draw(combathero);
						combatWindow.draw(creepHPBOX);

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
				animatedSprite.setPosition(mageAscent.nextFloor());
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
				Player.setCurrentHP(Player.getCurrentHP() - (10 * mageAscent.getCurrentFloorNumber()));
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
			}

			//Creature event happens. 
			if ((mageAscent.getCurrentFloor()->getTile(x, y)->getType() == MOB || mageAscent.getCurrentFloor()->getTile(x, y2)->getType() == MOB) &&
				(mageAscent.getCurrentFloor()->getTile(x, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x, y2)->getInteractState()))
			{
				mageAscent.getCurrentFloor()->getTile(x, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x, y2)->setTileState(false);
				Creature testCreep("AndyBot", 50 * mageAscent.getCurrentFloorNumber(), 5 * mageAscent.getCurrentFloorNumber(), 10);
				sf::RenderWindow combatWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Fight!", sf::Style::Titlebar);
				combatWindow.setFramerateLimit(60);
				//set combat resolve time
				mageAscent.getCurrentFloor()->stopBgm(); 
				
				if (combatWindow.hasFocus())
					battle.play();
				else
					battle.stop();
				
				while (combatWindow.isOpen())
				{
					sf::Event combatEvent;
					while (combatWindow.pollEvent(combatEvent))
					{
						if (combatEvent.type == sf::Event::Closed)
						{
							combatWindow.close();
							battle.stop();
							mageAscent.getCurrentFloor()->playBgm();
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num1)
						{	//Melee attack
							testCreep.dmgCalc(Player.hitDmg());//player attacks creep, creep takes damage
							if (testCreep.getCurrentHP() <= 0)
							{
								victory.play();
								int experiencePoints = 300 * mageAscent.getCurrentFloorNumber(), mana = 100;
								Player.awardXP(experiencePoints);
								if (Player.getCurrentXP() >= Player.getNextXP())
								{
									Player.setCurrentLVL(1);
									Player.set_strength(5);
									Player.setHP(Player.getHP() + 50);
								}
								Player.setCurrentMana(mana);
								combatWindow.close();
								battle.stop();
								mageAscent.getCurrentFloor()->playBgm();
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
									victory.play(); 
									int experiencePoints = 300 * mageAscent.getCurrentFloorNumber(), mana = 100;
									Player.awardXP(experiencePoints);
									if (Player.getCurrentXP() >= Player.getNextXP())
									{
										Player.setCurrentLVL(1);
										Player.set_strength(5);
										Player.setHP(Player.getHP() + 50);
									}
									Player.setCurrentMana(mana);
									combatWindow.close();
									battle.stop();
									mageAscent.getCurrentFloor()->playBgm();
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
							battle.stop();
							sf::RenderWindow deathWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "RIP", sf::Style::Titlebar);
							mageAscent.getCurrentFloor()->stopBgm();

							if (deathWindow.hasFocus())
								deathKnell.play();
							else
								deathKnell.stop();

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
						TextBlock playerName(Charsize, "Brave Adventurer", sf::Vector2f(0, 0), font);
						TextBlock CombatHpBox(Charsize, "Health:", std::to_string(Player.getCurrentHP()), std::to_string(Player.getHP()), sf::Vector2f(0, Charsize), font);
						TextBlock CombatManaBox(Charsize, "Mana:", std::to_string(Player.getCurrentMana()), std::to_string(Player.getMana()), sf::Vector2f(0, Charsize * 2), font);
						TextBlock CombatAttack(Charsize, "Press 1 to attack with your weapon", sf::Vector2f(0, Charsize*26.5), font);
						TextBlock CombatMMissile(Charsize, "Press 2 to attack with your magic (requires 10 mana)", sf::Vector2f(0, Charsize * 27.5), font);
						TextBlock CombatHeal(Charsize, "Press 3 to heal with your magic (requires 25 mana)", sf::Vector2f(0, Charsize * 28.5), font);


						TextBlock creepHPBOX(Charsize, "Health:", std::to_string(testCreep.getCurrentHP()), std::to_string(testCreep.getHP()), sf::Vector2f(600, Charsize), font);
						TextBlock creepName(Charsize, "AndyBot 122", sf::Vector2f(650, 0), font);

						TextBlock versus(Charsize, "versus", sf::Vector2f(350, Charsize), font);

						combatWindow.clear();
						/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
						{
						combatWindow.draw(lvlBox);
						}*/
						sf::Texture highreshero;
						sf::Texture highresogre;
						highreshero.loadFromFile("CharSprites/hero.png");
						highresogre.loadFromFile("CharSprites/ogre.png");
						sf::Sprite combathero;
						sf::Sprite combatogre;
						combathero.setTexture(highreshero);
						combatogre.setTexture(highresogre);
						combathero.setPosition(5.0f, 75.0f);
						combathero.setScale(0.4f, 0.4f);
						combatogre.setPosition(435.0f, 50.0f);
						combatogre.setScale(0.5f, 0.5f);

						if (testCreep.getXP() == 42)
						{
							sf::Texture miniboss;
							miniboss.loadFromFile("CharSprites/miniboss.png");
							sf::Sprite mini;
							mini.setTexture(miniboss);
							mini.setPosition(240.0f, 125.0f);
							mini.setScale(0.4f, 0.4f);
							TextBlock creepName(Charsize, "Minotard", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(mini);
						}
						else if (testCreep.getXP() == 45)
						{
							sf::Texture mainboss;
							mainboss.loadFromFile("CharSprites/mainboss.png");
							sf::Sprite main;
							main.setTexture(mainboss);
							main.setPosition(500.0f, 72.5f);
							main.setScale(0.6f, 0.6f);
							TextBlock creepName(Charsize, "Necromancer", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(main);
						}
						else
						{
							sf::Texture highresogre;
							highresogre.loadFromFile("CharSprites/ogre.png");
							sf::Sprite combatogre;
							combatogre.setTexture(highresogre);
							combatogre.setPosition(435.0f, 50.0f);
							combatogre.setScale(0.5f, 0.5f);
							TextBlock creepName(Charsize, "Ogricus", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(combatogre);
						}


						combatWindow.draw(playerName);
						combatWindow.draw(CombatManaBox);
						combatWindow.draw(CombatHpBox);

						combatWindow.draw(combathero);
						combatWindow.draw(creepHPBOX);

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
				animatedSprite.setPosition(mageAscent.nextFloor());
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
				Player.setCurrentHP(Player.getCurrentHP() - (10 * mageAscent.getCurrentFloorNumber()));
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
			}

			//Creature event happens. 
			if ((mageAscent.getCurrentFloor()->getTile(x2, y)->getType() == MOB || mageAscent.getCurrentFloor()->getTile(x2, y2)->getType() == MOB) &&
				(mageAscent.getCurrentFloor()->getTile(x2, y)->getInteractState() || mageAscent.getCurrentFloor()->getTile(x2, y2)->getInteractState()))
			{
				mageAscent.getCurrentFloor()->getTile(x2, y)->setTileState(false);
				mageAscent.getCurrentFloor()->getTile(x2, y2)->setTileState(false);
				Creature testCreep("AndyBot", 50 * mageAscent.getCurrentFloorNumber(), 5 * mageAscent.getCurrentFloorNumber(), 10);
				sf::RenderWindow combatWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Fight!", sf::Style::Titlebar);
				combatWindow.setFramerateLimit(60);
				//set combat resolve time
				mageAscent.getCurrentFloor()->stopBgm();
				if (combatWindow.hasFocus())
					battle.play();
				else
					battle.stop();
				
				while (combatWindow.isOpen())
				{
					sf::Event combatEvent;
					while (combatWindow.pollEvent(combatEvent))
					{
						if (combatEvent.type == sf::Event::Closed)
						{
							combatWindow.close();
							battle.stop();
							mageAscent.getCurrentFloor()->playBgm();
						}
						if (combatEvent.type == sf::Event::KeyPressed && combatEvent.key.code == sf::Keyboard::Num1)
						{	//Melee attack
							testCreep.dmgCalc(Player.hitDmg());//player attacks creep, creep takes damage
							if (testCreep.getCurrentHP() <= 0)
							{
								victory.play();
								int experiencePoints = 300 * mageAscent.getCurrentFloorNumber(), mana = 100;
								Player.awardXP(experiencePoints);
								if (Player.getCurrentXP() >= Player.getNextXP())
								{
									Player.setCurrentLVL(1);
									Player.set_strength(5);
									Player.setHP(Player.getHP() + 50);
								}
								Player.setCurrentMana(mana);
								combatWindow.close();
								battle.stop();
								mageAscent.getCurrentFloor()->playBgm();
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
									victory.play(); 
									int experiencePoints = 300 * mageAscent.getCurrentFloorNumber(), mana = 100;
									Player.awardXP(experiencePoints);
									if (Player.getCurrentXP() >= Player.getNextXP())
									{
										Player.setCurrentLVL(1);
										Player.set_strength(5);
										Player.setHP(Player.getHP() + 50);
									}
									Player.setCurrentMana(mana);
									combatWindow.close();
									battle.stop();
									mageAscent.getCurrentFloor()->playBgm();
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
							battle.stop();
							
							
							sf::RenderWindow deathWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "RIP", sf::Style::Titlebar);
							mageAscent.getCurrentFloor()->stopBgm();
							

							if (deathWindow.hasFocus())
								deathKnell.play();
							else
								deathKnell.stop();

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
						TextBlock playerName(Charsize, "Brave Adventurer", sf::Vector2f(0, 0), font);
						TextBlock CombatHpBox(Charsize, "Health:", std::to_string(Player.getCurrentHP()), std::to_string(Player.getHP()), sf::Vector2f(0, Charsize), font);
						TextBlock CombatManaBox(Charsize, "Mana:", std::to_string(Player.getCurrentMana()), std::to_string(Player.getMana()), sf::Vector2f(0, Charsize * 2), font);
						TextBlock CombatAttack(Charsize, "Press 1 to attack with your weapon", sf::Vector2f(0, Charsize*26.5), font);
						TextBlock CombatMMissile(Charsize, "Press 2 to attack with your magic (requires 10 mana)", sf::Vector2f(0, Charsize * 27.5), font);
						TextBlock CombatHeal(Charsize, "Press 3 to heal with your magic (requires 25 mana)", sf::Vector2f(0, Charsize * 28.5), font);


						TextBlock creepHPBOX(Charsize, "Health:", std::to_string(testCreep.getCurrentHP()), std::to_string(testCreep.getHP()), sf::Vector2f(600, Charsize), font);
						TextBlock creepName(Charsize, "AndyBot 122", sf::Vector2f(650, 0), font);

						TextBlock versus(Charsize, "versus", sf::Vector2f(350, Charsize), font);

						combatWindow.clear();
						/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
						{
						combatWindow.draw(lvlBox);
						}*/
						sf::Texture highreshero;
						sf::Texture highresogre;
						highreshero.loadFromFile("CharSprites/hero.png");
						highresogre.loadFromFile("CharSprites/ogre.png");
						sf::Sprite combathero;
						sf::Sprite combatogre;
						combathero.setTexture(highreshero);
						combatogre.setTexture(highresogre);
						combathero.setPosition(5.0f, 75.0f);
						combathero.setScale(0.4f, 0.4f);
						combatogre.setPosition(435.0f, 50.0f);
						combatogre.setScale(0.5f, 0.5f);

						if (testCreep.getXP() == 42)
						{
							sf::Texture miniboss;
							miniboss.loadFromFile("CharSprites/miniboss.png");
							sf::Sprite mini;
							mini.setTexture(miniboss);
							mini.setPosition(240.0f, 125.0f);
							mini.setScale(0.4f, 0.4f);
							TextBlock creepName(Charsize, "Minotard", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(mini);
						}
						else if (testCreep.getXP() == 45)
						{
							sf::Texture mainboss;
							mainboss.loadFromFile("CharSprites/mainboss.png");
							sf::Sprite main;
							main.setTexture(mainboss);
							main.setPosition(500.0f, 72.5f);
							main.setScale(0.6f, 0.6f);
							TextBlock creepName(Charsize, "Necromancer", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(main);
						}
						else
						{
							sf::Texture highresogre;
							highresogre.loadFromFile("CharSprites/ogre.png");
							sf::Sprite combatogre;
							combatogre.setTexture(highresogre);
							combatogre.setPosition(435.0f, 50.0f);
							combatogre.setScale(0.5f, 0.5f);
							TextBlock creepName(Charsize, "Ogricus", sf::Vector2f(600, 0), font);
							combatWindow.draw(combatBgSprite);
							combatWindow.draw(creepName);
							combatWindow.draw(combatogre);
						}


						combatWindow.draw(playerName);
						combatWindow.draw(CombatManaBox);
						combatWindow.draw(CombatHpBox);

						combatWindow.draw(combathero);
						combatWindow.draw(creepHPBOX);

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
		TextBlock manaBox(Charsize, "Mana:", std::to_string(Player.getCurrentMana()), std::to_string(Player.getMana()), sf::Vector2f(150 + Charsize * 2, 0), font);
		TextBlock xpBox(Charsize, "XP:", std::to_string(Player.getCurrentXP()), std::to_string(Player.getNextXP()), sf::Vector2f(150 + Charsize*2, Charsize), font);
		TextBlock lvlBox(Charsize, "LVL:", std::to_string(Player.getCurrentLVL()), sf::Vector2f(0, Charsize), font);
		TextBlock shekelBox(Charsize, "Shekels:", std::to_string(Player.getShekels()), sf::Vector2f(290 + Charsize * 2, 0), font);

		mageAscent.getCurrentFloor()->printFloor(window);
		window.draw(animatedSprite);
		window.draw(manaBox);
		window.draw(hpBox);
		window.draw(xpBox);
		window.draw(lvlBox);
		window.draw(shekelBox);
		window.draw(tipBox);
		window.display();
		if (window.hasFocus())
			mageAscent.getCurrentFloor()->playBgm();
		else
			mageAscent.getCurrentFloor()->stopBgm();
	}
	/*Start Credits Screen code*/

	sf::RenderWindow creditsWindow(sf::VideoMode(screenDimensions.x, screenDimensions.y), "The Perils of Aeliorn: Mage's Tower Ascent");
	titleWindow.setFramerateLimit(60);

	sf::Vector2f creditsSize((float)creditsWindow.getSize().x, (float)creditsWindow.getSize().y);

	sf::Texture creditsScreen;
	creditsScreen.loadFromFile("tower.jpg");

	sf::Sprite creditsSprite;
	creditsSprite.setTexture(creditsScreen);
	creditsSprite.scale(
		creditsSize.x / creditsSprite.getLocalBounds().width,
		creditsSize.y / creditsSprite.getLocalBounds().height);

	TextBlock creditsReel((Charsize * 1.25), "Credits", sf::Vector2f(((creditsSize.x / 2) - (2 * TILE_SIZE)), (TILE_SIZE / 3)), font);
	creditsReel.setFillColor(sf::Color(174, 174, 210));
	creditsReel.setOutlineThickness(2.0f);
	creditsReel.setOutlineColor(sf::Color::Black);

	TextBlock credits1(Charsize, "Thomas Osterdock\t\t\t\t\tTiles\n\t\t\t\t\t\t\t\t\t\t\t\tFloors\n\t\t\t\t\t\t\t\t\t\t\t\tTower\n\t\t\t\t\t\t\t\t\t\t\t\tTitle\n\t\t\t\t\t\t\t\t\t\t\t\tCredits\n\t\t\t\t\t\t\t\t\t\t\t\tBackground Music", sf::Vector2f(TILE_SIZE, ((2 * TILE_SIZE))), font);
	credits1.setFillColor(sf::Color(174, 174, 210));
	credits1.setOutlineThickness(2.0f);
	credits1.setOutlineColor(sf::Color::Black);

	TextBlock credits2(Charsize, "Trevor Smith\t\t\t\t\t\t\tWindow Rendering\n\t\t\t\t\t\t\t\t\t\t\t\tUI Design", sf::Vector2f(TILE_SIZE, (6 * TILE_SIZE)), font);
	credits2.setFillColor(sf::Color(174, 174, 210));
	credits2.setOutlineThickness(2.0f);
	credits2.setOutlineColor(sf::Color::Black);

	TextBlock credits3(Charsize, "Elliott Villars\t\t\t\t\t\t\tSprite Animation\n\t\t\t\t\t\t\t\t\t\t\t\tEvent Handler: Player Movement\n\t\t\t\t\t\t\t\t\t\t\t\tPlayer Death\n\t\t\t\t\t\t\t\t\t\t\t\tVersion Control", sf::Vector2f(TILE_SIZE, (7.33 * TILE_SIZE)), font);
	credits3.setFillColor(sf::Color(174, 174, 210));
	credits3.setOutlineThickness(2.0f);
	credits3.setOutlineColor(sf::Color::Black);

	TextBlock credits4(Charsize, "Josh Cross\t\t\t\t\t\t\t\t Level Design\n\t\t\t\t\t\t\t\t\t\t\t\tEvent Handler: Collisions\n\t\t\t\t\t\t\t\t\t\t\t\tPlayer Stats", sf::Vector2f(TILE_SIZE, ((creditsSize.y / 2) + (0.65 * TILE_SIZE))), font);
	credits4.setFillColor(sf::Color(174, 174, 210));
	credits4.setOutlineThickness(2.0f);
	credits4.setOutlineColor(sf::Color::Black);

	TextBlock credits5(Charsize, "Kathy Freund\t\t\t\t\t\t   Player Character Design\n\t\t\t\t\t\t\t\t\t\t\t\tQuality Assurance\n\t\t\t\t\t\t\t\t\t\t\t\tCombat Window", sf::Vector2f(TILE_SIZE, (12 * TILE_SIZE)), font);
	credits5.setFillColor(sf::Color(174, 174, 210));
	credits5.setOutlineThickness(2.0f);
	credits5.setOutlineColor(sf::Color::Black);

	TextBlock credits6(Charsize, "Flying Spaghetti Monster\t\t Main.cpp", sf::Vector2f(TILE_SIZE, ((creditsSize.y / 2) + (4.65* TILE_SIZE))), font);
	credits6.setFillColor(sf::Color(174, 174, 210));
	credits6.setOutlineThickness(2.0f);
	credits6.setOutlineColor(sf::Color::Black);

	TextBlock credits7(Charsize, "Game Textures and Music obtained from www.OpenGameArt.org", sf::Vector2f(TILE_SIZE, ((creditsSize.y / 2) + (6.5 * TILE_SIZE))), font);
	credits7.setFillColor(sf::Color(174, 174, 210));
	credits7.setOutlineThickness(2.0f);
	credits7.setOutlineColor(sf::Color::Black);

	//light purple (224,224,255)
	//medium purple (174,174,210)
	//dark purple (112,112,157)

	sf::Music creditsBgm;
	creditsBgm.openFromFile("Music\\Death Music\\old city theme.ogg");
	creditsBgm.setLoop(true);
	creditsBgm.play();

	while (creditsWindow.isOpen())
	{
		sf::Event creditsEvent;


		while (creditsWindow.pollEvent(creditsEvent))
		{
			if (creditsEvent.type == sf::Event::KeyPressed)
			{
				creditsBgm.stop();
				creditsWindow.close();
			}

		}

		// draw title
		creditsWindow.clear();
		creditsWindow.draw(creditsSprite);
		creditsWindow.draw(creditsReel);
		creditsWindow.draw(credits1);
		creditsWindow.draw(credits2);
		creditsWindow.draw(credits3);
		creditsWindow.draw(credits4);
		creditsWindow.draw(credits5);
		creditsWindow.draw(credits6);
		creditsWindow.draw(credits7);

		creditsWindow.display();
	}
	/*End Credits Screen Code*/
}
