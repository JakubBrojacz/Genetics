#pragma once

#include "Movable.h"
#include "Bullet.h"
#include "Asteriod.h"


class Ship : public Movable
{
private:
	static const float ACCELERATIONRATE;
	static const float ROTATIONRATE;
	static const float MAXSPEED;
	static const float SLOWRATE;
	static const float BULLETSPEED; //bulletspeed * 2
public:
	Ship();
	void clear();
	bool update(float delta);
	bool rotate(int direction, float delta); //-1 - left, 1 - right
	bool isHit(Asteroid); //rly bad function...
	void accelerate(float delta);
	Bullet fire();
};
