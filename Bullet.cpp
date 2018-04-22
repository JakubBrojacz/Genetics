#include "Bullet.h"

const float Bullet::maxliveTime = 0.25;



Bullet::Bullet(sf::Vector2f xy, float speed, float rot)
{
	float a=1;
	float b=3;
	setPointCount(4);
	setPoint(0, sf::Vector2f(a,-b));
	setPoint(1, sf::Vector2f(a, b));
	setPoint(2, sf::Vector2f(-a, b));
	setPoint(3, sf::Vector2f(-a, -b));
	setFillColor(sf::Color::Blue);
	setOrigin(sf::Vector2f(0, 0));
	move(xy);
	rotate(rot);
	setFillColor(sf::Color::Blue);

	float alpha = rot*M_PI / 180.0;
	vx = -sin(alpha)*speed;
	vy = cos(alpha)*speed;
	this->liveTime = 0;

}

bool Bullet::update(float delta)
{
	Movable::update(delta);
	liveTime += delta;
	if (liveTime > maxliveTime)
		return false;
	return true;
}
