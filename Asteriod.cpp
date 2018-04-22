#include "Asteriod.h"

Asteroid::Asteroid(float x, float y, float vx, float vy, int size) : size(size)
{
	int i;
	switch (size)
	{
	case 1:
		r = 60;
		i = 10;
		break;
	case 2:
		r = 30;
		i = 8;
		break;
	case 3:
		r = 20;
		i = 6;
		break;
	}

	setPointCount(i);
	for (int j = 0; j < i; j++)
	{
		float alpha = rand() % (360 / i) + (360 / i)*j;
		setPoint(j, sf::Vector2f(sin(alpha*M_PI/180.0)*r , cos(alpha*M_PI/180.0)*r ));
	}
		
	setOrigin(sf::Vector2f(0,0));
	move(x, y);
	setFillColor(sf::Color::Magenta);

	this->vx = vx;
	this->vy = vy;
	this->valpha = ((double)rand() / RAND_MAX- 0.5)*90.0/M_PI ;
}

bool Asteroid::update(float delta)
{
	Movable::update(delta);
	rotate(delta*valpha);
	return true;
}

bool Asteroid::isHit(Bullet aim)
{
	if(distance(aim.getPosition(),this->getPosition())<r)
		return true;
	return false;
}

bool Asteroid::inside(sf::Vector2f aim)
{
	if (distance(aim, this->getPosition())<r)
		return true;
	return false;
}
