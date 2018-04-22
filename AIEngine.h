#pragma once

#include "Engine.h"

class AIEngine
{
protected:
	Ship player;
	double Shotcount;
	double lifespan;
	sf::Time lastShot;
	std::vector < Bullet > shots;
	std::vector < Asteroid > enemy;
	int wave;
	double points;
	const int ASTEROIDSPEED = 500;

	sf::Time lastFrame;
	sf::Time thisFrame;
	sf::Time lastWave;
	sf::Clock clock;
	sf::RenderWindow window;
	bool visibility;

	float LookAt(sf::Vector2f direction); // for AI sensor
	float sensorFunction(float distance);
public:
	
	AIEngine(bool visibility = 1);
	float* update(bool*);
	double endGame();

	~AIEngine();
};