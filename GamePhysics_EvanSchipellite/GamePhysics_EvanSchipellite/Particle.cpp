//=============================================================================
//                              Particle
//
// Written by Evan Schipellite
//
// Contains all information to be shared by particles
//=============================================================================
#include "Particle.h"
//=============================================================================
Particle::Particle()
:PhysicsObject()
{
	m_ActiveTime = 0;
}

//-----------------------------------------------------------------------------
Particle::~Particle()
{
}

//-----------------------------------------------------------------------------
void Particle::Initialize(float activeTime, float radius, Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initialRotation)
{
	PhysicsObject::Initialize(radius, 1, initialPosition, initialVelocity, initialAcceleration, initialRotation);

	m_ActiveTime = activeTime;
}

//-----------------------------------------------------------------------------
void Particle::Update(float deltaTime)
{
	PhysicsObject::Update(deltaTime);

	m_ActiveTime -= deltaTime;

	if (m_ActiveTime < 0)
	{
		m_ActiveTime = 0;
	}
}

//-----------------------------------------------------------------------------
bool Particle::GetIsActive()
{
	return m_ActiveTime > 0;
}
//=============================================================================
