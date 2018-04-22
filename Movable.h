#pragma once
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

enum type {SHIP, ASTEROID1, ASTEROID2, ASTEROID3, BULLET};

const int WINDOWX = 1000;
const int WINDOWY = 800;

class Movable : public sf::ConvexShape
{
protected:
	float vx, vy;
public:
	virtual bool update(float delta);

	virtual void acceleration(float vx, float vy) { this->vx=vx; this->vy=vy; };
};

float distance(sf::Vector2f a, sf::Vector2f b);
