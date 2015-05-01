//=============================================================================
//                              Collision Primitive
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef COLLISION_PRIMITIVE_H
#define COLLISION_PRIMITIVE_H
//=============================================================================
#include "Matrix44f.h"

class RigidBody;
//=============================================================================
class CollisionPrimitive
{
protected:
	RigidBody* mp_RigidBody;

	Matrix44f m_Offset;
	Matrix44f m_Transform;

public:
	CollisionPrimitive(RigidBody* rigidBody, Matrix44f offset = Matrix44f());
	~CollisionPrimitive();

	void CalculateInternals();

	inline Vector3D GetAxis(unsigned int index) const { return m_Transform.GetAxisVector(index); };
	inline Matrix44f GetTransform() const { return m_Transform; };
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