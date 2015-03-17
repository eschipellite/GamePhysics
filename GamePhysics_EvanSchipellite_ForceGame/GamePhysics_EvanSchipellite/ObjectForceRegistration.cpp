//=============================================================================
//                              Object Force Registration
//
// Written by Evan Schipellite
//
// Registers two Physics Objects with Generators
//=============================================================================
#include "ObjectForceRegistration.h"
//=============================================================================
ObjectForceRegistration::ObjectForceRegistration(ObjectForceGenerator* objectForceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	m_ObjectForceGenerator = objectForceGenerator;
	m_PhysicsObjectOne = physicsObjectOne;
	m_PhysicsObjectTwo = physicsObjectTwo;
}

//-----------------------------------------------------------------------------
ObjectForceRegistration::~ObjectForceRegistration()
{
}

//-----------------------------------------------------------------------------
void ObjectForceRegistration::Update()
{
	m_ObjectForceGenerator->UpdateForce(m_PhysicsObjectOne, m_PhysicsObjectTwo);
}
//=============================================================================