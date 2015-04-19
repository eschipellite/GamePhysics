//=============================================================================
//                              RigidyBody Force Registration
//
// Written by Evan Schipellite
//
// Registers RigidBodies with Force Generators
//=============================================================================
#ifndef RIGIDBODY_FORCE_REGISTRATION_H
#define RIGIDBODY_FORCE_REGISTRATION_H
//=============================================================================
#include "ForceGenerator.h"
#include "RigidBody.h"
//=============================================================================
class RigidForceRegistration
{
private:
	ForceGenerator* m_ForceGenerator;
	RigidBody* m_RigidBody;

public:
	RigidForceRegistration(ForceGenerator* forceGenerator, RigidBody* rigidBody);
	~RigidForceRegistration();

	ForceGenerator* GetForceGenerator() { return m_ForceGenerator; }
	RigidBody* GetRigidBody() { return m_RigidBody; }

	void Update();
};
//=============================================================================
#endif // RIGIDBODY_FORCE_REGISTRATION_H
