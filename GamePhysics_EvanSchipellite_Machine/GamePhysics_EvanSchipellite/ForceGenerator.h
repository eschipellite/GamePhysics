//=============================================================================
//                              Force Generator
//
// Written by Evan Schipellite
//
// Base Force Generator class for Physics System
//=============================================================================
#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H
//=============================================================================
#include "PhysicsObject.h"
#include "RigidBody.h"
//=============================================================================
class ForceGenerator
{
public:
	ForceGenerator();
	~ForceGenerator();

	virtual void UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo = NULL) = 0;
	virtual void UpdateForce(RigidBody *rigidBodyOne, RigidBody *rigidBodyTwo = NULL) {};
};
//=============================================================================
#endif //FORCE_GENERATOR_H