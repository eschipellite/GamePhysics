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
#include "RigidForceRegistration.h"
//=============================================================================
class ForceRegistry
{
private:
	std::vector<ForceRegistration> m_ForceRegistration;
	std::vector<RigidForceRegistration> m_RigidForceRegistration;

private:
	void updateForceGenerators();

public:
	ForceRegistry();
	~ForceRegistry();

	void AddForceRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject);
	void AddForceRegistration(ForceGenerator* forceGenerator, RigidBody* rigidBody);

	void RemoveForceRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject);
	void RemoveForceRegistration(ForceGenerator* forceGenerator, RigidBody* rigidBody);
	
	void Clear();

	void UpdateForces();
};
//=============================================================================
#endif //FORCEREGISTRY_H

