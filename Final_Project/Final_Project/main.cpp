#include "Source.h"
#include "Creature.h"
#include "Floor.h"
#include "TextBlock.h"
#include "PlayerCharacter.h"
//#include "Item.h"



int main()
{
	sf::Font font;
	
	if(!font.loadFromFile("font1.ttf"))
	{
		//will throw error
	}
	PlayerCharacter Player;
	TextBlock hpBox(Charsize, "Health:", std::to_string(Player.getCurrentHP()), std::to_string(Player.getHP()), sf::Vector2f(0, 0), font);
	TextBlock manaBox(Charsize, "Mana:" ,std::to_string(Player.getCurrentMana()), std::to_string(Player.getMana()), sf::Vector2f(150, 0), font);
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
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

	Animation walkingAnimationLeft;
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));

	Animation walkingAnimationRight;
	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));

	Animation walkingAnimationUp;
	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));

	Animation DeathAnimation;
	DeathAnimation.setSpriteSheet(texture);
	DeathAnimation.addFrame(sf::IntRect(32, 160, 32, 32));//finish death anims
	auto * currentAnimation = &walkingAnimationDown;

	// set up AnimatedSprite
	AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

	sf::Clock frameClock;

	auto speed = 100.0;
	auto noKeyWasPressed = true;

	while (window.isOpen())
	{
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

