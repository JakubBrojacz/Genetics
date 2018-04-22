#include "Movable.h"


bool Movable::update(float delta)
{
	move(sf::Vector2f(vx, vy)*delta);
	sf::Vector2f position = this->getPosition();
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

float distance(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f c = a - b;
	return sqrt(c.x*c.x + c.y*c.y);
}
