//=============================================================================
//                              Firework
//
// Written by Evan Schipellite
//
// A Firework particle in charge of detonating and launching further Fireworks
//=============================================================================
#include "Firework.h"
//=============================================================================
Firework::Firework()
{
	m_ShouldExplode = false;
	m_CurrentLevel = 0;
}

//-----------------------------------------------------------------------------
Firework::~Firework()
{
}

//-----------------------------------------------------------------------------
void Firework::Initialize(bool shouldExplode, int currentLevel, float activeTime, float radius, Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initialRotation)
{
	Particle::Initialize(activeTime, radius, initialPosition, initialVelocity, initialAcceleration, initialRotation);

	m_ShouldExplode = shouldExplode;
	m_CurrentLevel = currentLevel;
}

//-----------------------------------------------------------------------------
bool Firework::GetShouldExplode()
{
	return m_ShouldExplode;
}

//-----------------------------------------------------------------------------
int Firework::GetCurrentLevel()
{
	return m_CurrentLevel;
}
//=============================================================================
