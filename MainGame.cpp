#include "MainGame.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "WinScreen.h"
#include "Asteriod.h"
#include <iostream>
#include <Windows.h>

#include <time.h>

bool gameOver = false;
int bricksDestroyed = 0;
void MainGame::Initialize(sf::RenderWindow* window)
{
	SEManager = new SoundEffectManager;
	SEManager->InitializeSoundEffect();

	this->font = new sf::Font();
	this->font->loadFromFile("Fonts/visitor1.ttf");
	this->score = new Score(*font, 64U);
	this->lives = new Lives(*font, 64U);
	this->lives->setPosition(window->getSize().x - this->lives->getGlobalBounds().width, 0);

	this->level = new sf::Text("Current Level: " + std::to_string(levelIndex), *font, 32U);
	this->level->setFillColor(sf::Color::White);
	this->level->setPosition((window->getSize().x - this->lives->getGlobalBounds().width) / 2, 32);

	this->difficulty = new sf::Text("Asteroid speed bonus: " + std::to_string(levelIndex*2), *font, 32U);
	this->difficulty->setFillColor(sf::Color::White);
	this->difficulty->setPosition((window->getSize().x - this->lives->getGlobalBounds().width) / 2.3, 64U);

	shipExplodeTexture = new Texture;
	rockExplodeTexture = new Texture;
	shipExplodeTexture->loadFromFile("Images/explosions/type_B.png");
	rockExplodeTexture->loadFromFile("Images/explosions/type_C.png");

	this->spaceship = new Spaceship(SEManager);
	entities.push_back(spaceship);

	rockNum = 0;
	for (int i = 0; i<levelIndex * 5; i++)
	{
		bool isOverlap = false;
		Rock *rock = new Rock(BigRock, levelIndex*2);	
		//entities.push_back(rock);
		

		for (auto b : entities)
			if (CheckCollide(rock, b))
				isOverlap = true;

		if (!isOverlap)
		{
			entities.push_back(rock);
			rockNum += 7;
		}
	}

	if(levelIndex > 1)
		SEManager->PlaySoundEffect(WinSound);
	
}
void MainGame::Update(sf::RenderWindow* window)
{
	lives->Update();
	score->Update();

	if (live == 0)
	{
		finalScore = score->value;
		_currentState.SetState(new GameOver);
	}

	if (rockNum == 0)
	{
		levelIndex += 1;
		_currentState.SetState(new WinScreen());
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
		_currentState.SetState(new MainMenu);

	if (Keyboard::isKeyPressed(Keyboard::Space) && SEManager->CheckPlayStatus(LaserSound) == true)
	{
		Bullet* bullet = new Bullet();
		SEManager->PlaySoundEffect(LaserSound);
		bullet->Settings(bullet->aniBullet, spaceship->x, spaceship->y, spaceship->angle, 10);
		entities.push_back(bullet);
	}

	for (auto a : entities)
	{
		for (auto b : entities)
		{
			if ((a->entityType == "Rock" && b->entityType == "Rock")
				&& !(a->x == b->x&&a->y == b->y))
				if (CheckRockCollide(a, b) == true)
				{
					if (!a->isRockCollide && !b->isRockCollide)
					{
						a->dx *= -1;
						a->dy *= -1;
						b->dx *= -1;
						b->dy *= -1;
						a->isRockCollide = true;
						b->isRockCollide = true;
					}
				}

			if ((a->name == "BigRock" || a->name == "MediumRock" || a->name == "SmallRock") && b->name == "Bullet")
				if (CheckCollide(a, b))
				{
					a->life = 0;
					b->life = 0;

					score->AddScore();
					rockNum -= 1;
					SEManager->PlaySoundEffect(DestroySound);

					ExplosionEffect *explosionEffect_Rock = new ExplosionEffect(RockExplode, shipExplodeTexture, rockExplodeTexture);
					explosionEffect_Rock->Settings(explosionEffect_Rock->aniExplosion, a->x, a->y, 0, 0);
					entities.push_back(explosionEffect_Rock);

					for (int i = 0; i < 2; i++)
					{
						/*if (a->R == 25)
							continue;*/
						if (a->name == "BigRock")
						{
							Rock* newRock = new Rock(MediumRock, levelIndex * 2);
							newRock->Settings(newRock->aniRock, a->x - 64 * i, a->y - 64 * i, rand() % 360, 25);
							entities.push_back(newRock);
						}
						if (a->name == "MediumRock")
						{
							Rock* newRock = new Rock(SmallRock, levelIndex * 2);
							newRock->Settings(newRock->aniRock, a->x - 32 * i, a->y - 32 * i, rand() % 360, 20);
							entities.push_back(newRock);
						}
					}
				}

			if ((a->name == "BigRock" || a->name == "MediumRock" || a->name == "SmallRock") && b->name == "Spaceship")
				if (CheckCollide(a, b))
				{			
					lives->RemoveLife();
					SEManager->PlaySoundEffect(DestroySound);

					ExplosionEffect *explosionEffect_ship = new ExplosionEffect(ShipExplode, shipExplodeTexture, rockExplodeTexture);
					explosionEffect_ship->Settings(explosionEffect_ship->aniExplosion, a->x, a->y, 0, 0);
					entities.push_back(explosionEffect_ship);

					spaceship->Settings(spaceship->aniStatic, 1200 / 2, 800 / 2, 0, 20);
					spaceship->dx = 0;
					spaceship->dy = 0;
				}
		}
	}

	for (auto a : entities)
		for (auto b : entities) 
		{
			a->isRockCollide = false;
			b->isRockCollide = false;
		}

	int bulletCount = 0;
	for (auto e : entities)
	{
		if (e->name == "Explosion")
			if (e->anim.IsEnd())
				e->life = 0;

		if (e->name == "Bullet")
		{
			if (bulletCount < 10)
				bulletCount++;
			else
			{
				//e->life = 0;
			}
		}

	}

	for (auto i = entities.begin(); i != entities.end();)
	{
		Entity *e = *i;

		e->Update(window);
		e->anim.Update(window);

		if (e->life == 0) 
		{ 
			i = entities.erase(i); 
			delete e; 
		}
		else 
			i++;
	}

	
}
void MainGame::Render(sf::RenderWindow* window)
{
	window->draw(*this->lives);
	window->draw(*this->score);
	window->draw(*this->level);
	window->draw(*this->difficulty);
	for (auto i : entities)
		i->Draw(*window);
}
void MainGame::Destroy(sf::RenderWindow* window)
{
	delete this->score;
	delete this->lives;
	delete this->font;
	delete this->level;
	delete this->difficulty;
	delete this->rockExplodeTexture;
	delete this->shipExplodeTexture;
}

bool MainGame::CheckCollide(Entity *a, Entity *b)
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y)<
		(a->R + b->R)*(a->R + b->R);
}

bool MainGame::CheckRockCollide(Entity *a, Entity *b)
{
	float ax = a->x + a->R;
	float ay = a->y + a->R;

	float bx = b->x + b->R;
	float by = b->y + b->R;

	return (bx - ax)*(bx - ax) +
		(by - ay)*(by - ay)<
		(a->R + b->R)*(a->R + b->R);
}