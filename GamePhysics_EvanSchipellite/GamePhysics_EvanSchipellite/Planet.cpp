//=============================================================================
//                              Planet
//
// Written by Evan Schipellite
//
// Base class for planets
//=============================================================================
#include "Planet.h"
//=============================================================================
Planet::Planet()
{
	m_PlanetName = "Empty";
}

//-----------------------------------------------------------------------------
Planet::~Planet()
{
}

//-----------------------------------------------------------------------------
void Planet::Initialize(float radius, float mass, Vector3D initialPosition, Vector3D initialVelocity, std::string planeName)
{
	PhysicsObject::Initialize(radius, mass, initialPosition, initialVelocity);

	m_PlanetName = planeName;
}
//=============================================================================