#include "Rock.h"
Rock::Rock(int type, int difficulty)
{
	int rockSize;
	this->rockType = type;
	if (rockType == BigRock)
	{
		name = "BigRock";
		LoadTexture("Asteroid_Big.png");
		Animation sRock(*texture, 0, 0, 128, 128, 1, 0);
		rockSize = 64;
		aniRock = sRock;
	}
	else if (rockType == MediumRock)
	{
		name = "MediumRock";
		LoadTexture("Asteroid_Medium.png");
		Animation sRock(*texture, 0, 0, 64, 64, 1, 0);
		rockSize = 25;
		aniRock = sRock;
	}
	else if(rockType == SmallRock)
	{
		name = "SmallRock";
		LoadTexture("Asteroid_Small.png");
		Animation sRock(*texture, 0, 0, 32, 32, 1, 0);
		rockSize = 20;
		aniRock = sRock;
	}
	entityType = "Rock";
	Settings(aniRock, rand() % 1200, rand() % 800, rand() % 360, rockSize);
	dx = rand() % 8 - 4;
	dy = rand() % 8 - 4;
	rock_Velocity = rand() % (20-difficulty)  + 1;
	if (rock_Velocity <= 0)
		rock_Velocity = 1;

}

void Rock::Update(sf::RenderWindow* window)
{
	x += dx/ rock_Velocity;
	y += dy/ rock_Velocity;

	angle += .5f;

	if (x>1200) 
		x = 0;  
	else if (x<0) 
		x = 1200;
	if (y>800) 
		y = 0;  
	else if (y<0) 
		y = 800;
}