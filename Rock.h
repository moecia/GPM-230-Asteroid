#pragma once
#include "Entity.h"
#include "ExplosionEffect.h"
#define BigRock 0
#define MediumRock 1
#define SmallRock 2

class Rock : public Entity
{
public:
	Rock(int type, int difficulty);
	void Update(sf::RenderWindow* window);
	Animation aniRock;
//	~Rock();
private:	
	int rockType;
	float rock_Velocity;
};
