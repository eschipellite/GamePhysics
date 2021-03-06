//=============================================================================
//                              Collision Primitive
//
// Written by Evan Schipellite
//
//=============================================================================
#include "CollisionPrimitive.h"
#include "RigidBody.h"
//=============================================================================
CollisionPrimitive::CollisionPrimitive(RigidBody* rigidBody, Matrix44f offset)
{
	mp_RigidBody = rigidBody;
	m_Offset = offset;

	CalculateInternals();
}

//-----------------------------------------------------------------------------
CollisionPrimitive::~CollisionPrimitive()
{
}

void CollisionPrimitive::CalculateInternals()
{
	m_Transform = mp_RigidBody->GetTransform();
	m_Transform *= m_Offset;
}
//=============================================================================