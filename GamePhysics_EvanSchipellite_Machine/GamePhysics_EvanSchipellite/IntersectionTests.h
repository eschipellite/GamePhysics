//=============================================================================
//                              Intersection Tests
//
// Written by Evan Schipellite
//
// Basis from: https://github.com/idmillington/cyclone-physics
//=============================================================================
#ifndef INTERSECTION_TESTS_H
#define INTERSECTION_TESTS_H
//=============================================================================
#include "CollisionSphere.h"
#include "CollisionPlane.h"
#include "CollisionBox.h"
//=============================================================================
class IntersectionTests
{
private:
	static float transformToAxis(const CollisionBox& box, const Vector3D& axis);
	static bool checkOverlapOnAxis(const CollisionBox& boxOne, const CollisionBox& boxTwo, const Vector3D& axis, const Vector3D& toCenter);
	static float penetrationOnAxis(const CollisionBox& boxOne, const CollisionBox& boxTwo, const Vector3D& axis, const Vector3D& toCenter);

public:
	IntersectionTests();
	~IntersectionTests();

	static bool CheckSphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane);
	static bool CheckSphereAndSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo);
	static bool CheckBoxAndBox(const CollisionBox& boxOne, const CollisionBox& boxTwo);
	static bool CheckBoxAndHalfSpace(const CollisionBox& box, const CollisionPlane& plane);

	static bool TryAxis(const CollisionBox& boxOne, const CollisionBox& boxTwo, Vector3D axis, const Vector3D& toCenter, unsigned int index, float& smallestPenetration, unsigned int& smallestCase);
};
//=============================================================================
#endif // INTERSECTION_TESTS_H
