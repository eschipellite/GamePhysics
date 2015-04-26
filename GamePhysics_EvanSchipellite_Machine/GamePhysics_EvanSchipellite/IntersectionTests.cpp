//=============================================================================
//                              Intersection Tests
//
// Written by Evan Schipellite
//
//=============================================================================
#include "IntersectionTests.h"
#include <math.h>
//=============================================================================
IntersectionTests::IntersectionTests()
{
}

//-----------------------------------------------------------------------------
IntersectionTests::~IntersectionTests()
{
}

//-----------------------------------------------------------------------------
float IntersectionTests::transformToAxis(const CollisionBox& box, const Vector3D& axis)
{
	float xEval = box.GetHalfSize().X * abs(axis.Dot(box.GetAxis(0)));
	float yEval = box.GetHalfSize().Y * abs(axis.Dot(box.GetAxis(1)));
	float zEval = box.GetHalfSize().Z * abs(axis.Dot(box.GetAxis(2)));

	return xEval + yEval + zEval;
}

//-----------------------------------------------------------------------------
bool IntersectionTests::checkOverlapOnAxis(const CollisionBox& boxOne, const CollisionBox& boxTwo, const Vector3D& axis, const Vector3D& toCenter)
{
	float projectOne = transformToAxis(boxOne, axis);
	float projectTwo = transformToAxis(boxTwo, axis);

	float distance = abs(toCenter.Dot(axis));

	return distance < (projectOne + projectTwo);
}

//-----------------------------------------------------------------------------
float IntersectionTests::penetrationOnAxis(const CollisionBox& boxOne, const CollisionBox& boxTwo, const Vector3D& axis, const Vector3D& toCenter)
{
	float projectOne = transformToAxis(boxOne, axis);
	float projectTwo = transformToAxis(boxTwo, axis);

	float distance = abs(toCenter.Dot(axis));

	return projectOne + projectTwo - distance;
}

//-----------------------------------------------------------------------------
bool IntersectionTests::CheckSphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane)
{
	float sphereDistance = plane.GetDirection().Dot(sphere.GetAxis(3)) - sphere.GetRadius();

	return sphereDistance <= plane.GetOffset();
}

//-----------------------------------------------------------------------------
bool IntersectionTests::CheckSphereAndSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo)
{
	Vector3D midLine = sphereOne.GetAxis(3) - sphereTwo.GetAxis(3);
	float radiiSum = sphereOne.GetRadius() + sphereTwo.GetRadius();

	return midLine.MagnitudeSquared() < (radiiSum * radiiSum);
}

//-----------------------------------------------------------------------------
bool IntersectionTests::CheckBoxAndBox(const CollisionBox& boxOne, const CollisionBox& boxTwo)
{
	Vector3D toCenter = boxTwo.GetAxis(3) - boxOne.GetAxis(3);

	return 
	{
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(0), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(1), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(2), toCenter) &&

		checkOverlapOnAxis(boxOne, boxTwo, boxTwo.GetAxis(0), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxTwo.GetAxis(1), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxTwo.GetAxis(2), toCenter) &&

		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(0)), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(1)), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(2)), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(0)), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(1)), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(2)), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(0)), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(1)), toCenter) &&
		checkOverlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(2)), toCenter)
	};
}

//-----------------------------------------------------------------------------
bool IntersectionTests::CheckBoxAndHalfSpace(const CollisionBox& box, const CollisionPlane& plane)
{
	float projectedRadius = transformToAxis(box, plane.GetDirection());

	float boxDistance = plane.GetDirection().Dot(box.GetAxis(3)) - projectedRadius;

	return boxDistance <= plane.GetOffset();
}

//-----------------------------------------------------------------------------
bool IntersectionTests::TryAxis(const CollisionBox& boxOne, const CollisionBox& boxTwo, Vector3D axis, const Vector3D& toCenter, unsigned int index, float& smallestPenetration, unsigned int& smallestCase)
{
	if (axis.MagnitudeSquared() < 0.0001)
		return true;
	axis.Normalize();

	float penetration = penetrationOnAxis(boxOne, boxTwo, axis, toCenter);

	if (penetration < 0)
		return false;

	if (penetration < smallestPenetration)
	{
		smallestPenetration = penetration;
		smallestCase = index;
	}

	return true;
}
//=============================================================================