#include "SoundEffectManager.h"

void SoundEffectManager::InitializeSoundEffect()
{
	this->bufferLaser = new SoundBuffer;
	this->bufferLaser->loadFromFile("Sounds/Laser.wav");
	this->soundLaser = new Sound(*this->bufferLaser);

	this->bufferDestroyBrick = new SoundBuffer;
	this->bufferDestroyBrick->loadFromFile("Sounds/Explosion.wav");
	this->soundDestroyBrick = new Sound(*this->bufferDestroyBrick);

	this->bufferDamageBrick = new SoundBuffer;
	this->bufferDamageBrick->loadFromFile("Sounds/Brick.wav");
	this->soundDamageBrick = new Sound(*this->bufferDamageBrick);

	this->bufferThrust = new SoundBuffer;
	this->bufferThrust->loadFromFile("Sounds/Thrust.wav");
	this->soundThrust = new Sound(*this->bufferThrust);

	this->bufferLoseLife = new SoundBuffer;
	this->bufferLoseLife->loadFromFile("Sounds/LoseLife.wav");
	this->soundLoseLife = new Sound(*this->bufferLoseLife);

	this->bufferWin = new SoundBuffer;
	this->bufferWin->loadFromFile("Sounds/Winner.wav");
	this->soundWin = new Sound(*this->bufferWin);
}

void SoundEffectManager::PlaySoundEffect(int index)
{
	switch (index)
	{
	case LaserSound:
		this->soundLaser->play();
		index = -1;
		break;
	case DestroySound:
		this->soundDestroyBrick->play();
		index = -1;
		break;
	case DamageSound:
		this->soundDamageBrick->play();
		index = -1;
		break;
	case ThrustSound:
		this->soundThrust->play();
		index = -1;
		break;
	case LoseLifeSound:
		this->soundLoseLife->play();
		index = -1;
		break;
	case WinSound:
		this->soundWin->play();
		index = -1;
		break;
	}
}

bool SoundEffectManager::CheckPlayStatus(int index)
{
	bool isPlaying;
	switch (index)
	{
	case LaserSound:
		if (this->soundLaser->getStatus() != SoundSource::Playing)
			return true;
		break;
	}
	return false;
}

SoundEffectManager::~SoundEffectManager()
{
	delete this->soundLaser;
	delete this->bufferLaser;
	delete this->bufferDestroyBrick;
	delete this->soundDestroyBrick;
	delete this->bufferDamageBrick;
	delete this->soundDamageBrick;
	delete this->bufferThrust;
	delete this->soundThrust;
	delete this->bufferLoseLife;
	delete this->soundLoseLife;
	delete this->bufferWin;
	delete this->soundWin;
}