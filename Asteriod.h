#pragma once

#include "Movable.h"
#include "Bullet.h"
#include <random>

class Asteroid : public Movable
{
	float valpha; //predkosc obrotu wokol wlasnej osi
public:
	float r;
	int size;
	Asteroid(float x, float y, float vx, float vy, int size); //1 - big; 2 - medium; 3 - small
	bool update(float delta);
	bool isHit(Bullet);

	bool inside(sf::Vector2f); //if piont is inside asteroid
};