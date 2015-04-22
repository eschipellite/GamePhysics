//=============================================================================
//                              Collision Plane
//
// Written by Evan Schipellite
//=============================================================================
#ifndef COLLISION_PLANE_H
#define COLLISION_PLANE_H
//=============================================================================
#include "Vector3D.h"
//=============================================================================
class CollisionPlane
{
private:
	Vector3D m_Direction;

	float m_Offset;

public:
	CollisionPlane();
	~CollisionPlane();

	inline void SetDirection(Vector3D direction) { m_Direction = direction; };
	inline Vector3D GetDirection() const { return m_Direction; };

	inline void SetOffset(float offset) { m_Offset = offset; };
	inline float GetOffset() const { return m_Offset; };
};
//=============================================================================
#endif // COLLISION_PLANE_H

