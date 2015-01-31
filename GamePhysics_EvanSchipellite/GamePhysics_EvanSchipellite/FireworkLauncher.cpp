//=============================================================================
//                              FireworkLauncher
//
// Written by Evan Schipellite
//
// Particle System for launching and maintaining firework particles
//=============================================================================
#define _USE_MATH_DEFINES

#include "FireworkLauncher.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <iostream>

using namespace std;
//=============================================================================
FireworkLauncher::FireworkLauncher()
{
	m_MinFireworksPerExplosion = 0;
	m_MaxFireworksPerExplosion = 0;
	m_ExplosionChance = 0;
	
	m_MinLifeTime = 0;
	m_MaxLifeTime = 0;
	
	m_MaxLevel = 0;

	m_Position = Vector3D::Zero;

	m_MinSpeed = 0;
	m_MaxSpeed = 0;

	m_CurrentLevel = 0;
}

//-----------------------------------------------------------------------------
FireworkLauncher::~FireworkLauncher()
{
}

//-----------------------------------------------------------------------------
void FireworkLauncher::Initialize(Vector3D position, float fireworkSize, float minSpeed, float maxSpeed, int minFireworksPerExplosion, int maxFireworksPerExplosion, float explosionChance, int minLifeTime, int maxLifeTime, int maxLevel)
{
	m_MinFireworksPerExplosion = minFireworksPerExplosion;
	m_MaxFireworksPerExplosion = maxFireworksPerExplosion;
	m_ExplosionChance = explosionChance;
	
	m_MinLifeTime = minLifeTime;
	m_MaxLifeTime = maxLifeTime;

	m_MaxLevel = maxLevel;

	m_Position = position;
	
	m_MinSpeed = minSpeed;
	m_MaxSpeed = maxSpeed;

	m_FireworkSize = fireworkSize;
}

//-----------------------------------------------------------------------------
void FireworkLauncher::Start()
{
	m_Fireworks.push_back(createInitialFirework());
}

//-----------------------------------------------------------------------------
void FireworkLauncher::Update(float deltaTime)
{
	bool spawnAtNextLevel = false;
	int currentSize = m_Fireworks.size();

	for (int index = 0; index < currentSize; index++)
	{
		m_Fireworks[index]->Update(deltaTime);

		if (!m_Fireworks[index]->GetIsActive())
		{
			if (m_Fireworks[index]->GetShouldExplode())
			{
				if (m_MaxLevel > 0 && m_Fireworks[index]->GetCurrentLevel() == m_CurrentLevel)
				{
					m_CurrentLevel++;
				}

				createExplosion(m_Fireworks[index]->GetPosition(), getNumFireworksToCreate());
			}
		}
	}

	for (unsigned int index = 0; index < m_Fireworks.size(); index++)
	{
		if (!m_Fireworks[index]->GetIsActive())
		{
			if (m_CurrentLevel == 3)
			{
				cout << m_Fireworks.size() << endl;
			}

			delete m_Fireworks[index];
			m_Fireworks.erase(m_Fireworks.begin() + index);
			index--;
		}
	}
}

//-----------------------------------------------------------------------------
void FireworkLauncher::CleanUp()
{
	std::vector<Firework*>::iterator iter;
	for (iter = m_Fireworks.begin(); iter != m_Fireworks.end(); iter++)
	{
		delete *iter;
	}

	m_Fireworks.clear();
}

//-----------------------------------------------------------------------------
void FireworkLauncher::Draw()
{
	std::vector<Firework*>::iterator iter;
	for (iter = m_Fireworks.begin(); iter != m_Fireworks.end(); iter++)
	{
		(*iter)->Draw();
	}
}

//-----------------------------------------------------------------------------
void FireworkLauncher::Reset()
{
	CleanUp();

	m_CurrentLevel = 0;

	Start();
}

//-----------------------------------------------------------------------------
Firework* FireworkLauncher::createInitialFirework()
{
	Firework* firework = new Firework();

	float lifeTime = (float)getExplosionLifeTime();

	Vector3D launchVelocity = getLaunchVelocity();

	firework->Initialize(true, 0, lifeTime, m_FireworkSize, m_Position, launchVelocity);

	return firework;
}

//-----------------------------------------------------------------------------
void FireworkLauncher::createExplosion(Vector3D position, int numFireworks)
{
	float lifeTime = (float)getExplosionLifeTime();

	for (int index = 0; index < numFireworks; index++)
	{
		m_Fireworks.push_back(createFirework(position, lifeTime));
	}
}

//-----------------------------------------------------------------------------
Firework* FireworkLauncher::createFirework(Vector3D position, float lifeTime)
{
	Firework* firework = new Firework();

	bool shouldExplode = getShouldFireworkExplode();

	Vector3D velocity = getVelocity(shouldExplode);

	firework->Initialize(shouldExplode, m_CurrentLevel, lifeTime, m_FireworkSize, position, velocity);

	return firework;
}

//-----------------------------------------------------------------------------
int FireworkLauncher::getNumFireworksToCreate()
{
	if (m_MaxFireworksPerExplosion == m_MinFireworksPerExplosion)
	{
		return m_MaxFireworksPerExplosion;
	}

	return (rand() % (m_MaxFireworksPerExplosion - m_MinFireworksPerExplosion) + m_MinFireworksPerExplosion);
}

//-----------------------------------------------------------------------------
int FireworkLauncher::getExplosionLifeTime()
{
	if (m_MaxLifeTime == m_MinLifeTime)
	{
		return m_MaxLifeTime;
	}

	return (rand() % (m_MaxLifeTime - m_MinLifeTime) + m_MinLifeTime);
}

//-----------------------------------------------------------------------------
bool FireworkLauncher::getShouldFireworkExplode()
{
	if (m_MaxLevel > 0 && m_CurrentLevel >= m_MaxLevel)
	{
		return false;
	}

	return ((rand() % 100 + 0) <= (int)(m_ExplosionChance * 100));
}

//-----------------------------------------------------------------------------
Vector3D FireworkLauncher::getLaunchVelocity()
{
	Vector3D launchVelocity = Vector3D(0, 1, 0);

	launchVelocity *= (float)getFireworkSpeed();

	return launchVelocity;
}

//-----------------------------------------------------------------------------
float FireworkLauncher::getFireworkSpeed()
{
	if (m_MaxSpeed == m_MinSpeed)
	{
		return m_MaxSpeed;
	}

	return (m_MinSpeed + (rand()) / (RAND_MAX / (m_MaxSpeed - m_MinSpeed)));
}

//-----------------------------------------------------------------------------
//Random Vector rotation completed with assistance from Jake Ellenberg
Vector3D FireworkLauncher::getVelocity(bool shouldExplode)
{
	Vector3D velocity = Vector3D::Zero;

	float randomRotation = (float)rand();

	if (shouldExplode)
	{
		randomRotation /= (float)(RAND_MAX / M_PI);
	}
	else
	{
		randomRotation /= (float)(RAND_MAX / 2 * M_PI);
	}

	float randomZ = -1.0f + (float)(rand() / (float)(RAND_MAX / 2));
	velocity.X = sqrt(1 - pow(randomZ, 2)) * cos(randomRotation);
	velocity.Y = sqrt(1 - pow(randomZ, 2)) * sin(randomRotation);
	velocity.Z = randomZ;

	return velocity.Normalized() * getFireworkSpeed();
}
//=============================================================================
