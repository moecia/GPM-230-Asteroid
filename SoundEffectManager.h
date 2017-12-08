#pragma once
#include <SFML/Audio.hpp>

#define LaserSound 0
#define DestroySound 1
#define DamageSound 2
#define ThrustSound 3
#define LoseLifeSound 4
#define WinSound 5
using namespace sf;
class SoundEffectManager
{
public:
	void InitializeSoundEffect();
	void PlaySoundEffect(int index);
	bool CheckPlayStatus(int index);

	~SoundEffectManager();

	SoundBuffer* bufferLaser;
	Sound* soundLaser;

	SoundBuffer* bufferDestroyBrick;
	Sound* soundDestroyBrick;

	SoundBuffer* bufferDamageBrick;
	Sound* soundDamageBrick;

	SoundBuffer* bufferThrust;
	Sound* soundThrust;

	SoundBuffer* bufferLoseLife;
	Sound* soundLoseLife;

	SoundBuffer* bufferWin;
	Sound* soundWin;	
};