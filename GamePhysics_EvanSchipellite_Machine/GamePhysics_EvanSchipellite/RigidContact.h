//=============================================================================
//                              Rigid Contact
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef RIGID_CONTACT_H
#define RIGID_CONTACT_H
//=============================================================================
#include "Vector3D.h"
#include "RigidBody.h"
//=============================================================================
class RigidContact
{
private:
	RigidBody* mp_RigidBodyOne;
	RigidBody* mp_RigidBodyTwo;

	Vector3D m_ContactPoint;
	Vector3D m_ContactNormal;

	float m_Penetration;
	float m_Restitution;
	float m_Friction;

public:
	RigidContact();
	~RigidContact();

	void Initialize(RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo, Vector3D contactPoint, Vector3D contactNormal, float penetration, float restitution, float friction);
};
//=============================================================================
#endif // RIGID_CONTACT_H

