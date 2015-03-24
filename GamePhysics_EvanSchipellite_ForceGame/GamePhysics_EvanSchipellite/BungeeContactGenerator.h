//=============================================================================
//                              Bungee Contact Generator
//
// Written by Evan Schipellite
//
// Allows for bungee contact resolution between physics objects
//=============================================================================
#ifndef BUNGEE_CONTACT_GENERATOR_H
#define BUNGEE_CONTACT_GENERATOR_H
//=============================================================================
#include "SpringContactGenerator.h"
//=============================================================================
class BungeeContactGenerator :
	public SpringContactGenerator
{
public:
	BungeeContactGenerator(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo, float k, float restLength);
	~BungeeContactGenerator();

	virtual void AddContact(CollisionHandler* collisionHandler);
};
//=============================================================================
#endif // BUNGEE_CONTACT_GENERATOR_H

