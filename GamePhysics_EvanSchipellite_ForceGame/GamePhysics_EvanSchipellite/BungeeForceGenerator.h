//=============================================================================
//                              Bungee Force Generator
//
// Written by Evan Schipellite
//
// Allows for bungee force resolution between physics objects
//=============================================================================
#ifndef BUNGEE_FORCE_GENERATOR_H
#define BUNGEE_FORCE_GENERATOR_H
//=============================================================================
#include "SpringForceGenerator.h"
//=============================================================================
class BungeeForceGenerator :
	public SpringForceGenerator
{
public:
	BungeeForceGenerator(PhysicsObject* anchorObject, float k, float restLength);
	~BungeeForceGenerator();

	void UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo = NULL);
};
//=============================================================================
#endif // BUNGEE_FORCE_GENERATOR_H

