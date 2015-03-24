//=============================================================================
//                              Bungee Contact Generator
//
// Written by Evan Schipellite
//
// Allows for bungee contact resolution between physics objects
//=============================================================================
#include "BungeeContactGenerator.h"
//=============================================================================
BungeeContactGenerator::BungeeContactGenerator(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo, float k, float restLength)
	: SpringContactGenerator(physicsObjectOne, physicsObjectTwo, k, restLength)
{
}

//-----------------------------------------------------------------------------
BungeeContactGenerator::~BungeeContactGenerator()
{
}

//-----------------------------------------------------------------------------
void BungeeContactGenerator::AddContact(CollisionHandler* collisionHandler)
{
	Vector3D force = mp_PhysicsObjectOne->GetPosition();
	force -= mp_PhysicsObjectTwo->GetPosition();

	float magnitude = force.Magnitude();

	if (magnitude <= m_RestLength)
	{
		return;
	}

	magnitude = abs(magnitude - m_RestLength);
	magnitude *= m_K;

	force.Normalize();
	force *= -magnitude;
	mp_PhysicsObjectOne->AddForce(force);
}
//=============================================================================