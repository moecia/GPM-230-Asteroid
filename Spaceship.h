#pragma once
#include "Entity.h"
#include "SoundEffectManager.h"
class Spaceship : public Entity
{
public:
	Animation aniStatic;
	Animation aniMove;

	bool thrust;
	Spaceship(SoundEffectManager* SEManager);

	void Update(sf::RenderWindow* window);

private:
	SoundEffectManager* SEManager;


};