//=============================================================================
//                              RigidyBody Force Registration
//
// Written by Evan Schipellite
//
// Registers RigidBodies with Force Generators
//=============================================================================
#include "RigidForceRegistration.h"
//=============================================================================
RigidForceRegistration::RigidForceRegistration(ForceGenerator* forceGenerator, RigidBody* rigidBody)
{
	m_ForceGenerator = forceGenerator;
	m_RigidBody = rigidBody;
}

//-----------------------------------------------------------------------------
RigidForceRegistration::~RigidForceRegistration()
{
}

//-----------------------------------------------------------------------------
void RigidForceRegistration::Update()
{
	m_ForceGenerator->UpdateForce(m_RigidBody);
}
//=============================================================================