//=============================================================================
//                              Collision Detector
//
// Written by Evan Schipellite
//
//=============================================================================
#include "CollisionDetector.h"
#include "RigidContact.h"
//=============================================================================
CollisionDetector::CollisionDetector()
{
}

//-----------------------------------------------------------------------------
CollisionDetector::~CollisionDetector()
{
}

//-----------------------------------------------------------------------------
unsigned int CollisionDetector::SphereAndSphere(const CollisionSphere &sphereOne, const CollisionSphere &sphereTwo, CollisionData *collisionData)
{
	if (collisionData->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D positionOne = sphereOne.GetAxis(3);
	Vector3D positionTwo = sphereTwo.GetAxis(3);

	Vector3D midLine = positionOne - positionTwo;
	float size = midLine.Magnitude();

	if (size <= 0.0f || size >= sphereOne.GetRadius() + sphereTwo.GetRadius())
	{
		return 0;
	}

	Vector3D normal = midLine * 1.0f / size;

	RigidContact* rigidContact = collisionData->GetRigidContact();
	Vector3D contactPoint = positionOne + midLine * 0.5f;
	float penetration = sphereOne.GetRadius() + sphereTwo.GetRadius() - size;
	rigidContact->Initialize(sphereOne.GetRigidBody(), sphereTwo.GetRigidBody(), contactPoint, normal, penetration, collisionData->GetRestitution(), collisionData->GetFriction());
	collisionData->AddContacts(1);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int CollisionDetector::SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *collisionData)
{
	if (collisionData->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D position = sphere.GetAxis(3);

	float sphereDistance = plane.GetDirection().Dot(position) - sphere.GetRadius() - plane.GetOffset();

	if (sphereDistance >= 0)
	{
		return 0;
	}

	RigidContact* rigidContact = collisionData->GetRigidContact();
	Vector3D contactPoint = position - plane.GetDirection() * (sphereDistance + sphere.GetRadius());
	rigidContact->Initialize(sphere.GetRigidBody(), nullptr, contactPoint, plane.GetDirection(), -sphereDistance, collisionData->GetRestitution(), collisionData->GetFriction());
	collisionData->AddContacts(1);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int CollisionDetector::SphereAndTruePlane(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *collisionData)
{
	if (collisionData->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D position = sphere.GetAxis(3);

	float centerDistance = plane.GetDirection().Dot(position) - plane.GetOffset();

	if (centerDistance * centerDistance >= sphere.GetRadius() * sphere.GetRadius())
	{
		return 0;
	}

	Vector3D normal = plane.GetDirection();
	float penetration = -centerDistance;

	if (centerDistance < 0)
	{
		normal *= -1;
		penetration = -penetration;
	}
	penetration += sphere.GetRadius();

	RigidContact* rigidContact = collisionData->GetRigidContact();
	Vector3D contactPoint = position - plane.GetDirection() * centerDistance;
	rigidContact->Initialize(sphere.GetRigidBody(), nullptr, contactPoint, normal, penetration, collisionData->GetRestitution(), collisionData->GetFriction());
	collisionData->AddContacts(1);
	return 1;
}
//=============================================================================
