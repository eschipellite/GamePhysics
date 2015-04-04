//=============================================================================
//                              Bungee Force Generator
//
// Written by Evan Schipellite
//
// Allows for bungee force resolution between physics objects
//=============================================================================
#include "BungeeForceGenerator.h"
#include <math.h>
//=============================================================================
BungeeForceGenerator::BungeeForceGenerator(PhysicsObject* anchorObject, float k, float restLength)
: SpringForceGenerator(anchorObject, k, restLength)
{
}

//-----------------------------------------------------------------------------
BungeeForceGenerator::~BungeeForceGenerator()
{
}

//-----------------------------------------------------------------------------
void BungeeForceGenerator::UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	Vector3D force = physicsObjectOne->GetPosition();
	force -= mp_AnchorObject->GetPosition();

	float magnitude = force.Magnitude();

	if (magnitude <= m_RestLength)
	{
		return;
	}

	magnitude = abs(magnitude - m_RestLength);
	magnitude *= m_K;

	force.Normalize();
	force *= -magnitude;
	physicsObjectOne->AddForce(force);
}
//=============================================================================