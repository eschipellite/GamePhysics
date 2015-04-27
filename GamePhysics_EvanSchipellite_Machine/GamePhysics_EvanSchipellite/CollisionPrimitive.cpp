//=============================================================================
//                              Collision Primitive
//
// Written by Evan Schipellite
//
//=============================================================================
#include "CollisionPrimitive.h"
//=============================================================================
CollisionPrimitive::CollisionPrimitive(RigidBody* rigidBody, Matrix offset)
{
	mp_RigidBody = rigidBody;
	m_Offset = offset;
}

//-----------------------------------------------------------------------------
CollisionPrimitive::~CollisionPrimitive()
{
}
//=============================================================================