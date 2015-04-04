//=============================================================================
//                              Gravity Generator
//
// Written by Evan Schipellite
//
// Handles gravity between two objects
//=============================================================================
#include "GravityGenerator.h"
#include <math.h>
//=============================================================================
float const GravityGenerator::GRAVITY_CONSTANT = 3.965f * pow(10.0f, -14.0f); // AU^3 / Solar Mass * S^2
//=============================================================================
GravityGenerator::GravityGenerator()
{
}

//-----------------------------------------------------------------------------
GravityGenerator::~GravityGenerator()
{
}

//-----------------------------------------------------------------------------
// Vector equation from: http://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation
// Assistance from Jake Ellenberg, implementing equation structure
void GravityGenerator::UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	float distanceSqred = physicsObjectOne->GetPosition().GetDistanceSquared(physicsObjectTwo->GetPosition());
	Vector3D direction = physicsObjectOne->GetPosition() - physicsObjectTwo->GetPosition();
	direction.Normalize();
	Vector3D resultingForce = direction * (-GRAVITY_CONSTANT * ((physicsObjectOne->GetMass() * physicsObjectTwo->GetMass()) / distanceSqred));

	physicsObjectOne->AddForce(resultingForce);
	physicsObjectTwo->AddForce(resultingForce * -1);
}
//=============================================================================
