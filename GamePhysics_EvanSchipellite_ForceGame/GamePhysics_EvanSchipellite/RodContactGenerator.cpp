//=============================================================================
//                              Rod Contact Generator
//
// Written by Evan Schipellite
//
// Handles Contact additions for Rods
//=============================================================================
#include "RodContactGenerator.h"
#include "Contact.h"
//=============================================================================
RodContactGenerator::RodContactGenerator(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo, float maxLength)
{
	mp_PhysicsObjectOne = physicsObjectOne;
	mp_PhysicsObjectTwo = physicsObjectTwo;

	m_MaxLength = maxLength;
}

//-----------------------------------------------------------------------------
RodContactGenerator::~RodContactGenerator()
{
}

//-----------------------------------------------------------------------------
float RodContactGenerator::getLength()
{
	return mp_PhysicsObjectOne->GetPosition().GetDistance(mp_PhysicsObjectTwo->GetPosition());
}

//-----------------------------------------------------------------------------
void RodContactGenerator::AddContact(CollisionHandler* collisionHandler)
{
	float length = getLength();
	if (length == m_MaxLength)
	{
		return;
	}

	float restitution = 0.0f;
	float penetration = 0.0f;
	Vector3D contactNormal = mp_PhysicsObjectTwo->GetPosition() - mp_PhysicsObjectOne->GetPosition();
	contactNormal.Normalize();

	if (length > m_MaxLength) 
	{
		penetration = length - m_MaxLength;
	}
	else 
	{
		contactNormal = contactNormal * -1.0f;
		penetration = m_MaxLength - length;
	}

	collisionHandler->AddContact(Contact(restitution, penetration, contactNormal, mp_PhysicsObjectOne, mp_PhysicsObjectTwo));
}
//=============================================================================
