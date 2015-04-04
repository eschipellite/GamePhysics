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
//=============================================================================
class ForceRegistry
{
private:
	std::vector<ForceRegistration> m_ForceRegistration;

private:
	void updateForceGenerators();

public:
	ForceRegistry();
	~ForceRegistry();

	void AddForceRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject);

	void RemoveForceRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject);
	
	void Clear();

	void UpdateForces();
};
//=============================================================================
#endif //FORCEREGISTRY_H

