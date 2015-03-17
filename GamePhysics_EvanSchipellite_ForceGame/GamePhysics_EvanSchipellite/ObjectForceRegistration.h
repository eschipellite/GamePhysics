//=============================================================================
//                              Object Force Registration
//
// Written by Evan Schipellite
//
// Registers two Physics Objects with Generators
//=============================================================================
#ifndef OBJECTFORCEREGISTRATION_H
#define OBJECTFORCEREGISTRATION_H
//=============================================================================
#include "ObjectForceGenerator.h"
#include "PhysicsObject.h"
//=============================================================================
class ObjectForceRegistration
{
private:
	ObjectForceGenerator* m_ObjectForceGenerator;
	PhysicsObject* m_PhysicsObjectOne;
	PhysicsObject* m_PhysicsObjectTwo;
public:
	ObjectForceRegistration(ObjectForceGenerator* objectForceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo);
	~ObjectForceRegistration();

	ObjectForceGenerator* GetObjectForceGenerator() { return m_ObjectForceGenerator; }
	PhysicsObject* GetPhysicsOneObject() { return m_PhysicsObjectOne; }
	PhysicsObject* GetPhysicsTwoObject() { return m_PhysicsObjectTwo; }

	void Update();
};
//=============================================================================
#endif // OBJECT_FORCE_REGISTRATION_H

