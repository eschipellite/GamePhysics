//=============================================================================
//                              Collision Primitive
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef COLLISION_PRIMITIVE_H
#define COLLISION_PRIMITIVE_H
//=============================================================================
#include "Matrix.h"

class RigidBody;
//=============================================================================
class CollisionPrimitive
{
protected:
	RigidBody* mp_RigidBody;

	Matrix m_Offset;
	Matrix m_Transform;

public:
	CollisionPrimitive(RigidBody* rigidBody, Matrix offset = Matrix());
	~CollisionPrimitive();

	void CalculateInternals();

	inline Vector3D GetAxis(unsigned int index) const { return m_Transform.GetAxisVector(index); };
	inline Matrix GetTransform() const { return m_Transform; };
	inline RigidBody* GetRigidBody() const { return mp_RigidBody; };
};
//=============================================================================
//=============================================================================
//                              Collision Type
//
// Written by Evan Schipellite
//
//=============================================================================
enum CollisionType
{
	SPHERE,
	BOX
};
//=============================================================================
#endif // COLLISION_PRIMITIVE_H