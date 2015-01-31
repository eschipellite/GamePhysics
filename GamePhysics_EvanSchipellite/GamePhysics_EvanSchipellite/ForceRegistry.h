//=============================================================================
//                              Force Registry
//
// Written by Evan Schipellite
//
// Handles all force registrations
//=============================================================================
#ifndef FORCEREGISTRY_H
#define FORCEREGISTRY_H
//=============================================================================
#include <vector>
#include "ForceRegistration.h"
#include "PhysicsObject.h"
#include "ForceGenerator.h"
#include "ObjectForceGenerator.h"
#include "ObjectForceRegistration.h"
//=============================================================================
class ForceRegistry
{
private:
	std::vector<ForceRegistration> m_ForceRegistration;
	std::vector<ObjectForceRegistration> m_ObjectForceRegistration;

private:
	void updateForceGenerators();
	void updateObjectForceGenerators();

public:
	ForceRegistry();
	~ForceRegistry();

	void AddRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject);
	void AddRegistration(ObjectForceGenerator* objectForceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo);

	void RemoveRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject);
	void RemoveRegistration(ObjectForceGenerator* objectForceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo);
	
	void Clear();

	void UpdateForces();
};
//=============================================================================
#endif //FORCEREGISTRY_H

