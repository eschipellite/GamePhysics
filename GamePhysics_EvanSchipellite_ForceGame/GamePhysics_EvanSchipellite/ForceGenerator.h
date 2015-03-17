//=============================================================================
//                              Force Generator
//
// Written by Evan Schipellite
//
// Base Force Generator class for Physics System
//=============================================================================
#ifndef FORCEGENERATOR_H
#define FORCEGENERATOR_H
//=============================================================================
#include "PhysicsObject.h"
#include "Generator.h"
//=============================================================================
class ForceGenerator :
	public Generator
{
public:
	ForceGenerator();
	~ForceGenerator();

	virtual void UpdateForce(PhysicsObject* physicsObject) = 0;
};
//=============================================================================
#endif //FORCEGENERATOR_H