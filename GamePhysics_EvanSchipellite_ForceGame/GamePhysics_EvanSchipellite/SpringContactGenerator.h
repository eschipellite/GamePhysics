//=============================================================================
//                              Spring Contact Generator
//
// Written by Evan Schipellite
//
// Allows for spring contact resolution between physics objects
//=============================================================================
#ifndef SPRINT_CONTACT_GENERATOR_H
#define SPRINT_CONTACT_GENERATOR_H
//=============================================================================
#include "ContactGenerator.h"
#include "PhysicsObject.h"
#include "CollisionHandler.h"
//=============================================================================
class SpringContactGenerator :
	public ContactGenerator
{
protected:
	PhysicsObject* mp_PhysicsObjectOne;
	PhysicsObject* mp_PhysicsObjectTwo;

	float m_K;
	float m_RestLength;
public:
	SpringContactGenerator(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo, float k, float restLength);
	~SpringContactGenerator();

	virtual void AddContact(CollisionHandler* collisionHandler);
};
//=============================================================================
#endif // SPRINT_CONTACT_GENERATOR_H
