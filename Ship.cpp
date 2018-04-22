#include "Ship.h"
#include <iostream>

const float Ship::ROTATIONRATE = 1000.f;
const float Ship::ACCELERATIONRATE = 0.5f;
const float Ship::MAXSPEED = 50.f;
const float Ship::SLOWRATE = 0.0002;
const float Ship::BULLETSPEED = 3000.f;

Ship::Ship()
{
	setPointCount(4);
	setPoint(0, sf::Vector2f(0,2));
	setPoint(0, sf::Vector2f(-1,-1));
	setPoint(0, sf::Vector2f(0,0));
	setPoint(0, sf::Vector2f(1,-1));
	setOrigin(sf::Vector2f(0,0));

	this->vx = 0;
	this->vy = 0;
}

void Ship::clear()
{
	setPointCount(4);
	setPoint(0, sf::Vector2f(0, 25));
	setPoint(1, sf::Vector2f(-10, -10));
	setPoint(2, sf::Vector2f(0, 0));
	setPoint(3, sf::Vector2f(10, -10));
	setOrigin(sf::Vector2f(0, 0));
	setFillColor(sf::Color::Green);
	move(WINDOWX / 2.0, WINDOWY / 2.0);
	this->vx = 0;
	this->vy = 0;
}

bool Ship::update(float delta)
{
	move(vx, vy);
	vx = vx - vx * SLOWRATE;
	vy = vy - vy * SLOWRATE;

	sf::Vector2f position = getPosition();
	if (position.x > WINDOWX)
		this->move(-WINDOWX, 0);
	if (position.x < 0)
		this->move(WINDOWX, 0);
	if (position.y > WINDOWY)
		this->move(0, -WINDOWY);
	if (position.y < 0)
		this->move(0, WINDOWY);
	return true;
}

bool Ship::rotate(int direction, float delta)
{
	Movable::rotate(direction*delta*ROTATIONRATE);
	return false;
}

bool Ship::isHit(Asteroid aim)
{
	/*
	for (int i = 0; i < 4; i++)
		if (distance(aim.getPosition(), getPosition()+getPoint(i)) < aim.r)
			return true;
			*/
	if (distance(aim.getPosition(), getPosition()) < aim.r)
		return true;
	return false;
}

void Ship::accelerate(float delta)
{
	float alpha = getRotation()*M_PI / 180.0;
	vx -= sin(alpha)*delta*ACCELERATIONRATE;
	vy += cos(alpha)*delta*ACCELERATIONRATE;

	float v = sqrt(vx * vx + vy * vy);
	if (v > MAXSPEED)
	{
		vx = vx / v * MAXSPEED;
		vy = vy / v * MAXSPEED;
	}
}

Bullet Ship::fire()
{
	float alpha = getRotation()*M_PI / 180.0;
	return Bullet( getPosition()+sf::Vector2f(-sin(alpha)*25,cos(alpha)*25),BULLETSPEED,getRotation() );
}
