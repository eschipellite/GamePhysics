//=============================================================================
//                              Earth Gravity Generator
//
// Written by Evan Schipellite
//
// Applies constant acceleration force due to Earth gravity
//=============================================================================
#include "EarthGravityGenerator.h"
//=============================================================================
EarthGravityGenerator::EarthGravityGenerator(const Vector3D &gravity)
{
	m_Gravity = gravity;
}

//-----------------------------------------------------------------------------
EarthGravityGenerator::~EarthGravityGenerator()
{
}

//-----------------------------------------------------------------------------
void EarthGravityGenerator::UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	physicsObjectOne->AddForce(m_Gravity * physicsObjectOne->GetMass());
}

//-----------------------------------------------------------------------------
void EarthGravityGenerator::UpdateForce(RigidBody *rigidBodyOne, RigidBody *rigidBodyTwo)
{
	if (!rigidBodyOne->HasInfiniteMass())
	{
		return;
	}

	rigidBodyOne->AddForce(m_Gravity * rigidBodyOne->GetMass());
}
//=============================================================================
