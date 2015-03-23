//=============================================================================
//                              Cable Contact Generator
//
// Written by Evan Schipellite
//
// Handles contact information for cable creation
//=============================================================================
#ifndef CABLE_CONTACT_GENERATOR
#define CABLE_CONTACT_GENERATOR
//=============================================================================
#include "RodContactGenerator.h"
//=============================================================================
class CableContactGenerator :
	public RodContactGenerator
{
public:
	CableContactGenerator(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo, float maxLength);
	~CableContactGenerator();

	void AddContact(CollisionHandler* collisionHandler);
};
//=============================================================================
#endif // CABLE_CONTACT_GENERATOR
