//=============================================================================
//                              Cable Contact Generator
//
// Written by Evan Schipellite
//
// Handles contact information for cable creation
//=============================================================================
#include "CableContactGenerator.h"
//=============================================================================
CableContactGenerator::CableContactGenerator(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo, float maxLength)
	: RodContactGenerator(physicsObjectOne, physicsObjectTwo, maxLength)
{
}

//-----------------------------------------------------------------------------
CableContactGenerator::~CableContactGenerator()
{
}

//-----------------------------------------------------------------------------
void CableContactGenerator::AddContact(CollisionHandler* collisionHandler)
{
	float length = getLength();
	if (length < m_MaxLength)
	{
		return;
	}

	float restitution = 0.0f;
	float penetration = 0.0f;
	Vector3D contactNormal = mp_PhysicsObjectTwo->GetPosition() - mp_PhysicsObjectOne->GetPosition();
	contactNormal.Normalize();
	penetration = length - m_MaxLength;

	collisionHandler->AddContact(Contact(restitution, penetration, contactNormal, mp_PhysicsObjectOne, mp_PhysicsObjectTwo));
}
//=============================================================================