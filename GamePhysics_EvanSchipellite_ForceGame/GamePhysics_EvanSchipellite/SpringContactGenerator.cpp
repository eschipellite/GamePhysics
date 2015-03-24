//=============================================================================
//                              Spring Contact Generator
//
// Written by Evan Schipellite
//
// Allows for spring contact resolution between physics objects
//=============================================================================
#include "SpringContactGenerator.h"
#include <math.h>
//=============================================================================
SpringContactGenerator::SpringContactGenerator(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo, float k, float restLength)
{
	mp_PhysicsObjectOne = physicsObjectOne;
	mp_PhysicsObjectTwo = physicsObjectTwo;

	m_K = k;
	m_RestLength = restLength;
}

//-----------------------------------------------------------------------------
SpringContactGenerator::~SpringContactGenerator()
{
}

//-----------------------------------------------------------------------------
void SpringContactGenerator::AddContact(CollisionHandler* collisionHandler)
{
	Vector3D force = mp_PhysicsObjectOne->GetPosition();
	force -= mp_PhysicsObjectTwo->GetPosition();

	float magnitude = force.Magnitude();
	magnitude = abs(magnitude - m_RestLength);
	magnitude *= m_K;

	force.Normalize();
	force *= -magnitude;
	mp_PhysicsObjectOne->AddForce(force);
}
//=============================================================================