//=============================================================================
//                              Spring Force Generator
//
// Written by Evan Schipellite
//
// Allows for spring force resolution between physics objects
//=============================================================================
#include "SpringForceGenerator.h"
#include <math.h>
//=============================================================================
SpringForceGenerator::SpringForceGenerator(PhysicsObject* anchorObject, float k, float restLength)
{
	mp_AnchorObject = anchorObject;

	m_K = k;
	m_RestLength = restLength;
}

//-----------------------------------------------------------------------------
SpringForceGenerator::~SpringForceGenerator()
{
}

//-----------------------------------------------------------------------------
void SpringForceGenerator::UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	Vector3D force = physicsObjectOne->GetPosition();
	force -= mp_AnchorObject->GetPosition();

	float magnitude = force.Magnitude();
	magnitude = abs(magnitude - m_RestLength);
	magnitude *= m_K;

	force.Normalize();
	force *= -magnitude;
	physicsObjectOne->AddForce(force);
}
//=============================================================================