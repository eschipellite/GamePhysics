//=============================================================================
//                              Collision Box
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H
//=============================================================================
#include "CollisionPrimitive.h"
//=============================================================================
class CollisionBox :
	public CollisionPrimitive
{
protected:
	Vector3D m_HalfSize;
	Vector3D m_Vertices[8];

public:
	CollisionBox(RigidBody* rigidBody, Vector3D halfSize, Matrix44f offset = Matrix44f());
	~CollisionBox();

	inline Vector3D GetHalfSize() const { return m_HalfSize; };
};
//=============================================================================
#endif COLLISION_BOX_H

