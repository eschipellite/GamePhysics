//=============================================================================
//                              Rigid Contact
//
// Written by Evan Schipellite
//
//=============================================================================
#include "RigidContact.h"
//=============================================================================
RigidContact::RigidContact()
{
}

//-----------------------------------------------------------------------------
RigidContact::~RigidContact()
{
}

//-----------------------------------------------------------------------------
void RigidContact::Initialize(RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo, Vector3D contactPoint, Vector3D contactNormal, float penetration, float restitution, float friction)
{
	mp_RigidBodyOne = rigidBodyOne;
	mp_RigidBodyTwo = rigidBodyTwo;

	m_ContactPoint = contactPoint;
	m_ContactNormal = contactNormal;

	m_Penetration = penetration;
	m_Restitution = restitution;
	m_Friction = friction;
}
//=============================================================================