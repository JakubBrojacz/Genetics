#pragma once

#include "Bullet.h"
#include "Asteriod.h"
#include "Ship.h"

class Engine
{
protected:
	Ship player;
	sf::Time lastShot;
	std::vector < Bullet > shots;
	std::vector < Asteroid > enemy;
	int wave;
	int points;
	const int ASTEROIDSPEED = 500;

	sf::Time lastFrame;
	sf::Time thisFrame;
	sf::Time lastWave;
	sf::Clock clock;
	sf::RenderWindow window;
public:
	Engine();
	bool update();
	int endGame();
};