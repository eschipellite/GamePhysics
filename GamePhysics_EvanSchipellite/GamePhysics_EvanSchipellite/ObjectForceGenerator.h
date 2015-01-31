//=============================================================================
//                              Object Force Generator
//
// Written by Evan Schipellite
//
// Handles forces between two objects
//=============================================================================
#ifndef OBJECTFORCEGENERATOR_H
#define OBJECTFORCEGENERATOR_H
//=============================================================================
#include "PhysicsObject.h"
#include "Generator.h"
//=============================================================================
class ObjectForceGenerator :
	public Generator
{
public:
	ObjectForceGenerator();
	~ObjectForceGenerator();

	virtual void UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo) = 0;
};
//=============================================================================
#endif //GRAVITYGENERATOR_H

