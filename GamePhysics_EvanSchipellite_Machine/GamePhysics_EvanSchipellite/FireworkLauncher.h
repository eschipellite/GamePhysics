//=============================================================================
//                              FireworkLauncher
//
// Written by Evan Schipellite
//
// Particle System for launching and maintaining firework particles
//=============================================================================
#ifndef FIREWORKLAUNCHER_H
#define FIREWORKLAUNCHER_H
//=============================================================================
#include "Firework.h"
#include <vector>
#include "Vector3D.h"
//=============================================================================
class FireworkLauncher
{
private:
	std::vector<Firework*> m_Fireworks;

	int m_MinFireworksPerExplosion;
	int m_MaxFireworksPerExplosion;
	float m_ExplosionChance;

	int m_MinLifeTime;
	int m_MaxLifeTime;

	int m_CurrentLevel;
	int m_MaxLevel = 0; //0 - Potentially Infinite

	Vector3D m_Position;

	float m_MinSpeed;
	float m_MaxSpeed;

	float m_FireworkSize;

private:
	Firework* createInitialFirework();
	void createExplosion(Vector3D position, int numFireworks);
	Firework* createFirework(Vector3D position, float lifeTime);

	int getNumFireworksToCreate();
	int getExplosionLifeTime();
	bool getShouldFireworkExplode();
	Vector3D getLaunchVelocity();
	float getFireworkSpeed();
	Vector3D getVelocity(bool shouldExplode);

public:
	FireworkLauncher();
	~FireworkLauncher();

	void Initialize(Vector3D position, float fireworkSize, float minSpeed, float maxSpeed, int minFireworksPerExplosion, int maxFireworksPerExplosion, float explosionChance, int minLifeTime, int maxLifeTime, int maxLevel = 0);
	void Start();
	void Update(float deltaTime);
	void CleanUp();
	void Draw();
	void Reset();
};
//=============================================================================
#endif // FIREWORKLAUNCHER_H

