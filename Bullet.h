#pragma once

#include "Movable.h"

class Bullet : public Movable
{
	float liveTime;
	static const float maxliveTime;
public:
	Bullet(sf::Vector2f,float,float); //position, velocity, direction ( degrees )
	bool update(float delta);
};