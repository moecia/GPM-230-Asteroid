#include "Bullet.h"
Bullet::Bullet()
{
	name = "Bullet";
	LoadTexture("fire_blue.png");
	Animation sBullet(*texture, 0, 0, 32, 64, 16, 0.8);
	aniBullet = sBullet;
}

void Bullet::Update(sf::RenderWindow* window)
{
	dx = cos(angle*DEGTORAD) * 6;
	dy = sin(angle*DEGTORAD) * 6;
	// angle+=rand()%6-3;
	x += dx;
	y += dy;

	if (x>1200 || x<0 || y>800 || y<0) 
		life = 0;

	/*if (x>1200)
		x = 0;
	else if (x<0)
		x = 1200;
	if (y>800)
		y = 0;
	else if (y<0)
		y = 800;*/
}
