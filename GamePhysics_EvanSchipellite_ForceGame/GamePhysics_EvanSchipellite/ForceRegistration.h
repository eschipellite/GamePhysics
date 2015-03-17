//=============================================================================
//                              Force Registration
//
// Written by Evan Schipellite
//
// Registers Physics Objects with Generators
//=============================================================================
#ifndef FORCEREGISTRATION_H
#define FORCEREGISTRATION_H
//=============================================================================
#include "ForceGenerator.h"
#include "PhysicsObject.h"
//=============================================================================
class ForceRegistration
{
private:
	ForceGenerator* m_ForceGenerator;
	PhysicsObject* m_PhysicsObject;

public:
	ForceRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject);
	~ForceRegistration();

	ForceGenerator* GetForceGenerator() { return m_ForceGenerator; }
	PhysicsObject* GetPhysicsObject() { return m_PhysicsObject; }

	void Update();
};
//=============================================================================
#endif // FORCEREGISTRATION_H

