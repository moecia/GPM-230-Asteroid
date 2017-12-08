#include "Spaceship.h"

Spaceship::Spaceship(SoundEffectManager* SEManager)
{
	LoadTexture("spaceship.png");
	setScale(.2f, .2f);
	Animation sPlayer(*texture, 40, 0, 40, 40, 1, 0);
	Animation sPlayer_go(*texture, 40, 40, 40, 40, 1, 0);
	aniStatic = sPlayer;
	aniMove = sPlayer_go;
	Settings(sPlayer, 200, 200, 0, 20);
	name = "Spaceship";
	this->SEManager = SEManager;
}

void Spaceship::Update(sf::RenderWindow* window)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) 
		angle += 3;
	if (Keyboard::isKeyPressed(Keyboard::Left)) 
		angle -= 3;
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		thrust = true;
	}
	else 
		thrust = false;


	if (thrust)
	{
		//SEManager->PlaySoundEffect(ThrustSound);
		anim = aniMove;
		dx += cos(angle*DEGTORAD)*0.1;
		dy += sin(angle*DEGTORAD)*0.1;
	}
	else
	{
		//SEManager->soundThrust->stop();
		anim = aniStatic;
		dx *= 0.99;
		dy *= 0.99;
	}

	int maxSpeed = 15;
	float speed = sqrt(dx*dx + dy*dy);
	if (speed>maxSpeed)
	{
		dx *= maxSpeed / speed;
		dy *= maxSpeed / speed;
	}

	x += dx;
	y += dy;

	if (x>1200) 
		x = 0; 
	else if (x<0) 
		x = 1200;
	if (y>800) 
		y = 0; 
	else if (y<0) 
		y = 800;
}
