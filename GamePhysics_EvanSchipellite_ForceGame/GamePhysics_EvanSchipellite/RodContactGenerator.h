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
private:
	PhysicsObject* mp_PhysicsObjectOne;
	PhysicsObject* mp_PhysicsObjectTwo;

	float m_MaxLength;

private:
	float getLength();

public:
	RodContactGenerator(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo, float maxLength);
	~RodContactGenerator();

	void RodContactGenerator::AddContact(CollisionHandler* collisionHandler);
};
//=============================================================================
#endif // ROD_CONTACT_GENERATOR