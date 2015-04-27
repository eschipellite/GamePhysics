//=============================================================================
//                              Rigid Ground Contact Generator
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef RIGID_GROUND_CONTACT_GENERATOR_H
#define RIGID_GROUND_CONTACT_GENERATOR_H
//=============================================================================
#include "ContactGenerator.h"

class CollisionPlane;
//=============================================================================
class RigidGroundContactGenerator :
	public ContactGenerator
{
private:
	CollisionPlane m_CollisionPlane;

public:
	RigidGroundContactGenerator(float groundY = 0);
	~RigidGroundContactGenerator();

	void AddContact(CollisionHandler* collisionHandler);
	void SetGroundY(float groundY);
};
//=============================================================================
#endif // RIGID_GROUND_CONTACT_GENERATOR_H