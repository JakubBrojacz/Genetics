#include "Engine.h"
#include <iostream>

float randomAsteroidSpeed(int k)
{
	return rand() % k - k / 2;
}

Engine::Engine()
{
	player.clear();
	wave = points = 0;
	
	clock.restart();
	lastWave = lastFrame = lastShot = clock.getElapsedTime();
	window.create(sf::VideoMode(WINDOWX, WINDOWY), "Asteroids");

	for (int i = 0; i<5; i++)
		enemy.push_back(Asteroid(0, rand() % WINDOWY, 0.75*randomAsteroidSpeed(ASTEROIDSPEED), 0.75*randomAsteroidSpeed(ASTEROIDSPEED), 1));
}

bool Engine::update()
{
	// UPDATE TIME
	lastFrame = thisFrame;
	thisFrame = clock.getElapsedTime();
	float delta = thisFrame.asSeconds() - lastFrame.asSeconds();

	// NEW WAVE
	if (thisFrame.asSeconds() - lastWave.asSeconds() > 15)
	{
		wave++;
		for (int i = 0; i<3 + wave; i++)
			enemy.push_back(Asteroid(0, rand() % WINDOWY, 0.75*randomAsteroidSpeed(ASTEROIDSPEED), 0.75*randomAsteroidSpeed(ASTEROIDSPEED), 1));
		lastWave = thisFrame;
	}

	//STEERING
	sf::Event event;
	while (window.pollEvent(event))
	{
		if ( event.type == sf::Event::Closed)
			window.close();
	};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player.accelerate(delta);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player.rotate(-1, delta);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.rotate(1, delta);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (thisFrame.asSeconds() - lastShot.asSeconds() > 0.4)
		{
			shots.push_back(player.fire());
			lastShot = thisFrame;
		}
	}

	//UPDATE ENTITIES
	if(!player.update(delta))
		return false;
	int d1 = shots.size();
	for (int i = 0; i < d1; i++)
	{
		if (!shots[i].update(delta))
		{
			shots.erase(shots.begin()+i);
			d1--;
		}
	}
	int d2 = enemy.size();
	for (int i = 0; i < d2; i++)
		enemy[i].update(delta);

	//DESTROYING HIT ENTITIES
	for (int i = 0; i < d2; i++)
		if (player.isHit(enemy[i]))
			return false;
	for(int i=0;i<d2;i++)
		for (int j = 0; j < d1; j++)
		{
			if (enemy[i].isHit(shots[j]))
			{
				int tmp;
				if ((tmp = enemy[i].size + 1) != 4)
				{
					enemy.push_back(Asteroid(enemy[i].getPosition().x, enemy[i].getPosition().y, (0.75 + (double)i*0.25)*randomAsteroidSpeed(ASTEROIDSPEED * tmp), (0.75 + (double)i*0.25)*randomAsteroidSpeed(ASTEROIDSPEED * tmp), tmp));
					enemy.push_back(Asteroid(enemy[i].getPosition().x, enemy[i].getPosition().y, (0.75 + (double)i*0.25)*randomAsteroidSpeed(ASTEROIDSPEED * tmp), (0.75 + (double)i*0.25)*randomAsteroidSpeed(ASTEROIDSPEED * tmp), tmp));
					d2 += 2;
				}
				enemy.erase(enemy.begin() + i);
				shots.erase(shots.begin() + j);
				d1--;
				d2--;
				points++;
			}
		}

	//VISUALIZATION
	window.clear(sf::Color::White);
	window.draw(player);
	for (int i = 0; i < d1; i++)
		window.draw(shots[i]);
	for (int i = 0; i < d2; i++)
		window.draw(enemy[i]);
	window.display();

	
	//everything is fine :D
	return true;
}

int Engine::endGame()
{
	window.close();
	return points;
}
