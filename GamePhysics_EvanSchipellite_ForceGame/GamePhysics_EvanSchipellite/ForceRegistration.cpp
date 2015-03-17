//=============================================================================
//                              Force Registration
//
// Written by Evan Schipellite
//
// Registers Physics Objects with Generators
//=============================================================================
#include "ForceRegistration.h"
//=============================================================================
ForceRegistration::ForceRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject)
{
	m_ForceGenerator = forceGenerator;
	m_PhysicsObject = physicsObject;
}

//-----------------------------------------------------------------------------
ForceRegistration::~ForceRegistration()
{
}

//-----------------------------------------------------------------------------
void ForceRegistration::Update()
{
	m_ForceGenerator->UpdateForce(m_PhysicsObject);
}
//=============================================================================
