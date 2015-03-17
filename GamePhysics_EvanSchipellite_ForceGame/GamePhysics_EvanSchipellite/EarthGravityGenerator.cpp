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
	m_GeneratorType = GeneratorType::EARTH_GRAVITY_GENERATOR;

	m_Gravity = gravity;
}

//-----------------------------------------------------------------------------
EarthGravityGenerator::~EarthGravityGenerator()
{
}

//-----------------------------------------------------------------------------
void EarthGravityGenerator::UpdateForce(PhysicsObject* physicsObject)
{
	physicsObject->AddForce(m_Gravity * physicsObject->GetMass());
}
//=============================================================================
