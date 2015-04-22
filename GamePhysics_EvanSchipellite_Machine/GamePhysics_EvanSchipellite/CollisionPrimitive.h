//=============================================================================
//                              Collision Primitive
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef COLLISION_PRIMITIVE_H
#define COLLISION_PRIMITIVE_H
//=============================================================================
#include "RigidBody.h"
#include "Matrix.h"
//=============================================================================
class CollisionPrimitive
{
protected:
	RigidBody* mp_RigidBody;

	Matrix m_Offset;
	Matrix m_Transform;

public:
	CollisionPrimitive();
	~CollisionPrimitive();

	inline void CalculateInternals() { m_Transform = mp_RigidBody->GetTransform() * m_Offset; };

	inline Vector3D GetAxis(unsigned int index) const { return m_Transform.GetAxisVector(index); };
	inline Matrix GetTransform() const { return m_Transform; };
	inline RigidBody* GetRigidBody() const { return mp_RigidBody; };
};
//=============================================================================
#endif // COLLISION_PRIMITIVE_H