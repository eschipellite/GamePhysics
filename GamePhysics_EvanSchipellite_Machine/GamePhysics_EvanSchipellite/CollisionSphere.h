//=============================================================================
//                              Collision Sphere
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef COLLISION_SPHERE_H
#define COLLISION_SPHERE_H
//=============================================================================
#include "CollisionPrimitive.h"
//=============================================================================
class CollisionSphere :
	public CollisionPrimitive
{
protected:
	float m_Radius;

public:
	CollisionSphere();
	~CollisionSphere();

	inline void SetRadius(float radius) { m_Radius = radius; };
	inline float GetRadius() const { return m_Radius; };
};
//=============================================================================
#endif // COLLISION_SPHERE_H

