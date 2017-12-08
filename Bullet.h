#pragma once
#include "Entity.h"
class Bullet : public Entity
{
public:
	Bullet();
	void Update(sf::RenderWindow* window);
	Animation aniBullet;
};