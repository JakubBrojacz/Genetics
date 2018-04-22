#include "AIEngine.h"
#include <iostream>
#include <cmath>
#include <SFML\System.hpp>

float randomAsteroidSpeed(int k);
/*
{
	return rand() % k - k / 2;
}
*/

float AIEngine::sensorFunction(float distance)
{
	//return 1.0 / distance;
	return 1.0 - 1.0 / (1.0 + exp(-5 * (distance - 30.0) / 30.0));
}

float AIEngine::LookAt(sf::Vector2f direction)
{
	sf::Vector2f position = player.getPosition();
	float distance = 0;
	position = position + direction;
	distance += 1;
	int d2 = enemy.size();

	while (distance < 61)
	{
		for (int i = 0; i < d2; i++)
			if (enemy[i].inside(position))
				return sensorFunction(distance);

		position = position + direction;
		distance += 1;
		
		if (position.x > WINDOWX)
			position.x = 0;
		if (position.x < 0)
			position.x = WINDOWX;
		if (position.y > WINDOWY)
			position.y = 0;
		if (position.y < 0)
			position.y = WINDOWY;
	}
	return 0;
}



AIEngine::AIEngine(bool visibility) :visibility(visibility)
{
	player.clear();
	wave = 0;
	points = 0.0;
	Shotcount = 4.0;
	lifespan = 0.0;
	
	if (visibility)
	{
		clock.restart();
		lastWave = lastFrame = lastShot = clock.getElapsedTime();
	}
	else
		lastWave = lastFrame = lastShot = sf::seconds(0.0);
	if(visibility)
		window.create(sf::VideoMode(WINDOWX, WINDOWY), "Asteroids");
	
	for (int i = 0; i<5; i++)
		enemy.push_back(Asteroid(0, rand() % WINDOWY, 0.75*randomAsteroidSpeed(ASTEROIDSPEED), 0.75*randomAsteroidSpeed(ASTEROIDSPEED), 1));
}


float * AIEngine::update(bool *keyboard)
{
	
	// UPDATE TIME
	float delta;
	lastFrame = thisFrame;
	if (visibility)
	{	
		
		thisFrame = clock.getElapsedTime();
		//delta = thisFrame.asSeconds() - lastFrame.asSeconds();
		sf::sleep(sf::seconds(0.001) - thisFrame + lastFrame);
		delta = 0.001;
		thisFrame = lastFrame + sf::seconds(delta);
	}
	else
	{
		delta = 0.001;
		thisFrame = thisFrame + sf::seconds(delta);
		lifespan+=0.01;
	}


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
		if (event.type == sf::Event::Closed)
			window.close();
	};
	if (keyboard[0])
	{
		player.accelerate(delta);
	}
	if (keyboard[1])
	{
		player.rotate(-1, delta);
	}
	if (keyboard[2])
	{
		player.rotate(1, delta);
	}
	if (keyboard[3])
	{
		if (thisFrame.asSeconds() - lastShot.asSeconds() > 0.3)
		{
			shots.push_back(player.fire());
			lastShot = thisFrame;
			Shotcount+=1.0;
		}
	}
	
	//UPDATE ENTITIES
	if (!player.update(delta))
	{
		float* smierc = new float[1];
		smierc[0] = 200;
		return smierc;
	}
	int d1 = shots.size();
	for (int i = 0; i < d1; i++)
	{
		if (!shots[i].update(delta))
		{
			shots.erase(shots.begin() + i);
			d1--;
		}
	}
	int d2 = enemy.size();
	for (int i = 0; i < d2; i++)
		enemy[i].update(delta);

	//DESTROYING HIT ENTITIES
	for (int i = 0; i < d2; i++)
		if (player.isHit(enemy[i]))
		{
			float* smierc = new float[1];
			smierc[0] = 200;
			return smierc;
		}
	for (int i = 0; i<d2; i++)
		for (int j = 0; j < d1; j++)
		{
			if (enemy[i].isHit(shots[j]))
			{
				int tmp;
				if ((tmp = enemy[i].size + 1) != 4)
				{
					enemy.push_back(Asteroid(enemy[i].getPosition().x, enemy[i].getPosition().y, (0.75+(double)i*0.25)*randomAsteroidSpeed(ASTEROIDSPEED * tmp), (0.75 + (double)i*0.25)*randomAsteroidSpeed(ASTEROIDSPEED * tmp), tmp));
					enemy.push_back(Asteroid(enemy[i].getPosition().x, enemy[i].getPosition().y, (0.75 + (double)i*0.25)*randomAsteroidSpeed(ASTEROIDSPEED * tmp), (0.75 + (double)i*0.25)*randomAsteroidSpeed(ASTEROIDSPEED * tmp), tmp));
					d2 += 2;
				}
				enemy.erase(enemy.begin() + i);
				shots.erase(shots.begin() + j);
				d1--;
				d2--;
				points+=1.0;
			}
		}

	//VISUALIZATION
	if (visibility)
	{
		window.clear(sf::Color::White);
		window.draw(player);
		for (int i = 0; i < d1; i++)
			window.draw(shots[i]);
		for (int i = 0; i < d2; i++)
			window.draw(enemy[i]);
		window.display();
	}
	

	//everything is fine
	//i live
	float* sences = new float[9];
	for (int i = 0; i < 8; i++)
	{
		float alpha = player.getRotation()*M_PI / 180.0 + (double)i*(M_PI / 4.0);
		sences[i] = LookAt( sf::Vector2f(-10.0*cos(alpha), 10.0*sin(alpha)) ) ;
	}
	if (sences[0] > 0.2 && thisFrame.asSeconds() - lastShot.asSeconds() > 0.3) //usefull tip for shooting at starting generations
		sences[8] = 1.0;
	else
		sences[8] = 0.0;
		

	return sences;
}




double AIEngine::endGame()
{
	if(visibility) 
		window.close();
	if (visibility)
		lifespan = clock.getElapsedTime().asSeconds()*20.0;
	points++;
	if (visibility)
		std::cout << "Points: " << points-1 << ", lifespan: " << lifespan << ", Shotcount: " << Shotcount-4 << std::endl << "Total live score: " << (((double)points)*10.0)*((double)lifespan)*((double)points)*((double)points) / (((double)Shotcount)*((double)Shotcount)) << std::endl;
	if (points == 1)
		return 0.001;
	return ((points*10.0)*lifespan*points*points) / (Shotcount*Shotcount);
}

AIEngine::~AIEngine()
{
	shots.clear();
	enemy.clear();
}
