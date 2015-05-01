//=============================================================================
//                              Collision Sphere
//
// Written by Evan Schipellite
//
//=============================================================================
#include "CollisionSphere.h"
//=============================================================================
CollisionSphere::CollisionSphere(RigidBody* rigidBody, float radius, Matrix44f offset)
	:CollisionPrimitive(rigidBody, offset)
{
	m_Radius = radius;
}

//-----------------------------------------------------------------------------
CollisionSphere::~CollisionSphere()
{
}
//=============================================================================