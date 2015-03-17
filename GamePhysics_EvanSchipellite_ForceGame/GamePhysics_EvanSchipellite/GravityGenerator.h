//=============================================================================
//                              Gravity Generator
//
// Written by Evan Schipellite
//
// Handles gravity between two objects
//=============================================================================
#ifndef GRAVITYGENERATOR_H
#define GRAVITYGENERATOR_H
//=============================================================================
#include "ObjectForceGenerator.h"
//=============================================================================
class GravityGenerator :
	public ObjectForceGenerator
{
private:
	static const float GRAVITY_CONSTANT;
public:
	GravityGenerator();
	~GravityGenerator();

	virtual void UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo);
};
//=============================================================================
#endif //GRAVITYGENERATOR_H

