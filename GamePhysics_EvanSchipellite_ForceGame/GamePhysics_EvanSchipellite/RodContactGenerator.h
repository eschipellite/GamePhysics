//=============================================================================
//                              Rod Contact Generator
//
// Written by Evan Schipellite
//
// Handles Contact additions for Rods
//=============================================================================
#ifndef ROD_CONTACT_GENERATOR
#define ROD_CONTACT_GENERATOR
//=============================================================================
#include "ContactGenerator.h"
#include "PhysicsHandler.h"
//=============================================================================
class RodContactGenerator :
	public ContactGenerator
{
protected:
	PhysicsObject* mp_PhysicsObjectOne;
	PhysicsObject* mp_PhysicsObjectTwo;

	float m_MaxLength;

protected:
	float getLength();

public:
	RodContactGenerator(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo, float maxLength);
	~RodContactGenerator();

	virtual void AddContact(CollisionHandler* collisionHandler);
};
//=============================================================================
#endif // ROD_CONTACT_GENERATOR