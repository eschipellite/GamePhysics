//=============================================================================
//                              Spring Force Generator
//
// Written by Evan Schipellite
//
// Allows for spring force resolution between physics objects
//=============================================================================
#ifndef SPRINT_FORCE_GENERATOR_H
#define SPRINT_FORCE_GENERATOR_H
//=============================================================================
#include "ForceGenerator.h"
#include "PhysicsObject.h"
//=============================================================================
class SpringForceGenerator :
	public ForceGenerator
{
protected:
	PhysicsObject* mp_AnchorObject;

	float m_K;
	float m_RestLength;
public:
	SpringForceGenerator(PhysicsObject* anchorObject, float k, float restLength);
	~SpringForceGenerator();

	void UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjecTwo = NULL);
};
//=============================================================================
#endif // SPRINT_FORCE_GENERATOR_H
