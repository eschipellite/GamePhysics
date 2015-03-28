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
#include "ForceGenerator.h"
//=============================================================================
class GravityGenerator :
	public ForceGenerator
{
private:
	static const float GRAVITY_CONSTANT;
public:
	GravityGenerator();
	~GravityGenerator();

	void UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo = NULL);
};
//=============================================================================
#endif //GRAVITYGENERATOR_H

