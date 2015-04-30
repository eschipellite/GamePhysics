//=============================================================================
//                              Collision Detector
//
// Written by Evan Schipellite
//
// Basis from: https://github.com/idmillington/cyclone-physics
//=============================================================================
#include "CollisionDetector.h"
#include "RigidContact.h"
#include "IntersectionTests.h"
//=============================================================================
float CollisionDetector::m_Mults[8][3] = { { 1, 1, 1 }, { -1, 1, 1 }, { 1, -1, 1 }, { -1, -1, 1 },
{ 1, 1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 } };
//=============================================================================
CollisionDetector::CollisionDetector()
{
}

//-----------------------------------------------------------------------------
CollisionDetector::~CollisionDetector()
{
}

//-----------------------------------------------------------------------------
void CollisionDetector::fillPointFaceBoxBox(const CollisionBox& boxOne, const CollisionBox& boxTwo, const Vector3D& toCenter, CollisionHandler* collisionHandler, unsigned int best, float penetration)
{
	Vector3D normal = boxOne.GetAxis(best);
	if (boxOne.GetAxis(best).Dot(toCenter) > 0)
		normal *= -1.0f;

	Vector3D vertex = boxTwo.GetHalfSize();
	if (boxTwo.GetAxis(0).Dot(normal) < 0) vertex.X *= -1.0f;
	if (boxTwo.GetAxis(1).Dot(normal) < 0) vertex.Y *= -1.0f;
	if (boxTwo.GetAxis(2).Dot(normal) < 0) vertex.Z *= -1.0f;

	RigidContact rigidContact = RigidContact();
	Vector3D contactPoint = boxTwo.GetTransform() * vertex;
	rigidContact.Initialize(boxOne.GetRigidBody(), boxTwo.GetRigidBody(), contactPoint, normal, penetration, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
}

//-----------------------------------------------------------------------------
Vector3D CollisionDetector::getContactPoint(const Vector3D& pointOne, const Vector3D& directionOne, float sizeOne, const Vector3D& pointTwo, const Vector3D directionTwo, float sizeTwo, bool useOne)
{
	Vector3D toSt, cOne, cTwo;
	float dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
	float denom, mua, mub;

	smOne = directionOne.MagnitudeSquared();
	smTwo = directionTwo.MagnitudeSquared();
	dpOneTwo = directionTwo.Dot(directionOne);

	toSt = pointOne - pointTwo;
	dpStaOne = directionOne.Dot(toSt);
	dpStaTwo = directionTwo.Dot(toSt);

	denom = smOne * smTwo - dpOneTwo, dpOneTwo;

	if (abs(denom) < 0.0001f)
		return useOne ? pointOne : pointTwo;

	mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
	mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

	if (mua > sizeOne || mua < -sizeOne || mub > sizeTwo || mub < -sizeTwo)
	{
		return useOne ? pointOne : pointTwo;
	}
	else
	{
		cOne = pointOne + directionOne * mua;
		cTwo = pointTwo + directionTwo * mub;

		return cOne * 0.5f + cTwo * 0.5f;
	}
}

//-----------------------------------------------------------------------------
unsigned int CollisionDetector::SphereAndSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo, CollisionHandler* collisionHandler)
{
	Vector3D positionOne = sphereOne.GetAxis(3);
	Vector3D positionTwo = sphereTwo.GetAxis(3);

	Vector3D midLine = positionOne - positionTwo;
	float size = midLine.Magnitude();

	if (size <= 0.0f || size >= sphereOne.GetRadius() + sphereTwo.GetRadius())
	{
		return 0;
	}

	Vector3D normal = midLine * 1.0f / size;

	RigidContact rigidContact = RigidContact();
	Vector3D contactPoint = positionOne + midLine * 0.5f;
	float penetration = sphereOne.GetRadius() + sphereTwo.GetRadius() - size;
	rigidContact.Initialize(sphereOne.GetRigidBody(), sphereTwo.GetRigidBody(), contactPoint, normal, penetration, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
	collisionHandler->AddContact(rigidContact);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int CollisionDetector::SphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionHandler* collisionHandler)
{
	Vector3D position = sphere.GetAxis(3);

	float sphereDistance = plane.GetDirection().Dot(position) - sphere.GetRadius() - plane.GetOffset();

	if (sphereDistance >= 0)
	{
		return 0;
	}

	RigidContact rigidContact = RigidContact();
	Vector3D contactPoint = position - plane.GetDirection() * (sphereDistance + sphere.GetRadius());
	rigidContact.Initialize(sphere.GetRigidBody(), nullptr, contactPoint, plane.GetDirection(), -sphereDistance, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
	collisionHandler->AddContact(rigidContact);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int CollisionDetector::SphereAndTruePlane(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionHandler* collisionHandler)
{
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

	RigidContact rigidContact = RigidContact();
	Vector3D contactPoint = position - plane.GetDirection() * centerDistance;
	rigidContact.Initialize(sphere.GetRigidBody(), nullptr, contactPoint, normal, penetration, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
	collisionHandler->AddContact(rigidContact);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int CollisionDetector::BoxAndHalfSpace(const CollisionBox& box, const CollisionPlane& plane, CollisionHandler* collisionHandler)
{
	if (!IntersectionTests::CheckBoxAndHalfSpace(box, plane))
	{
		return 0;
	}

	int contactsUsed = 0;
	for (unsigned int i = 0; i < 8; i++)
	{
		Vector3D vertexPos(m_Mults[i][0], m_Mults[i][1], m_Mults[i][2]);
		vertexPos *= box.GetHalfSize();
		vertexPos = box.GetTransform().Transform(vertexPos);

		float vertexDistance = vertexPos.Dot(plane.GetDirection());

		if (vertexDistance <= plane.GetOffset() * -1.0f)
		{
			Vector3D contactPoint = plane.GetDirection();
			contactPoint *= vertexDistance - plane.GetOffset();
			contactPoint += vertexPos;
			Vector3D contactNormal = plane.GetDirection();
			float penetration = plane.GetOffset() - vertexDistance;
			RigidContact rigidContact = RigidContact();
			rigidContact.Initialize(box.GetRigidBody(), NULL, contactPoint, contactNormal, penetration, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
			collisionHandler->AddContact(rigidContact);
			contactsUsed++;
		}
	}
	return contactsUsed;
}

//-----------------------------------------------------------------------------
unsigned int CollisionDetector::BoxAndSphere(const CollisionBox& box, const CollisionSphere& sphere, CollisionHandler* collisionHandler)
{
	Vector3D center = sphere.GetAxis(3);
	Vector3D relativeCenter = box.GetTransform().TransformInverse(center);

	bool xEval = abs(relativeCenter.X) - sphere.GetRadius() > box.GetHalfSize().X;
	bool yEval = abs(relativeCenter.Y) - sphere.GetRadius() > box.GetHalfSize().Y;
	bool zEval = abs(relativeCenter.Z) - sphere.GetRadius() > box.GetHalfSize().Z;

	if (xEval || yEval || zEval)
	{
		return 0;
	}

	Vector3D closestPoint = Vector3D::Zero;

	float xDistance = relativeCenter.X;
	if (xDistance > box.GetHalfSize().X)
		xDistance = box.GetHalfSize().X;
	if (xDistance < -box.GetHalfSize().X)
		xDistance = -box.GetHalfSize().X;
	closestPoint.X = xDistance;

	float yDistance = relativeCenter.Y;
	if (yDistance > box.GetHalfSize().Y)
		yDistance = box.GetHalfSize().Y;
	if (yDistance < -box.GetHalfSize().Y)
		yDistance = -box.GetHalfSize().Y;
	closestPoint.Y = yDistance;

	float zDistance = relativeCenter.Z;
	if (zDistance > box.GetHalfSize().Z)
		zDistance = box.GetHalfSize().Z;
	if (zDistance < -box.GetHalfSize().Z)
		zDistance = -box.GetHalfSize().Z;
	closestPoint.Z = zDistance;

	float distance = (closestPoint - relativeCenter).MagnitudeSquared();
	if (distance > sphere.GetRadius() * sphere.GetRadius())
		return 0;

	Vector3D closestWorldPoint = box.GetTransform().Transform(closestPoint);

	RigidContact rigidContact = RigidContact();
	Vector3D contactNormal = (closestWorldPoint - center);
	contactNormal.Normalize();
	Vector3D contactPoint = closestWorldPoint;
	float penetration = sphere.GetRadius() - sqrt(distance);
	rigidContact.Initialize(box.GetRigidBody(), sphere.GetRigidBody(), contactPoint, contactNormal, penetration, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
	collisionHandler->AddContact(rigidContact);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int CollisionDetector::BoxAndBox(const CollisionBox& boxOne, const CollisionBox& boxTwo, CollisionHandler* collisionHandler)
{
	Vector3D toCenter = boxTwo.GetAxis(3) - boxOne.GetAxis(3);

	float penetration = FLT_MAX;
	unsigned int best = 0xffffff;

	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0), toCenter, 0, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1), toCenter, 1, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2), toCenter, 2, penetration, best)) return 0;

	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxTwo.GetAxis(0), toCenter, 3, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxTwo.GetAxis(1), toCenter, 4, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxTwo.GetAxis(2), toCenter, 5, penetration, best)) return 0;

	unsigned int bestSingleAxis = best;

	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(0)), toCenter, 6, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(1)), toCenter, 7, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(2)), toCenter, 8, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(0)), toCenter, 9, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(1)), toCenter, 10, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(2)), toCenter, 11, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(0)), toCenter, 12, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(1)), toCenter, 13, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(2)), toCenter, 14, penetration, best)) return 0;

	if (best == 0xffffff)
		return 0;

	if (best < 3)
	{
		fillPointFaceBoxBox(boxOne, boxTwo, toCenter, collisionHandler, best, penetration);
		return 1;
	}
	else if (best < 6)
	{
		fillPointFaceBoxBox(boxTwo, boxOne, toCenter * -1.0f, collisionHandler, best - 3, penetration);
		return 1;
	}
	else
	{
		best -= 6;
		unsigned int axisOneIndex = best / 3;
		unsigned int axisTwoIndex = best % 3;
		Vector3D axisOne = boxOne.GetAxis(axisOneIndex);
		Vector3D axisTwo = boxTwo.GetAxis(axisTwoIndex);
		Vector3D axis = axisOne.Cross(axisTwo);
		axis.Normalize();

		if (axis.Dot(toCenter) > 0)
			axis *= 1.0f;

		Vector3D pointOnEdgeOne = boxOne.GetHalfSize();
		Vector3D pointOnEdgeTwo = boxTwo.GetHalfSize();
		for (unsigned i = 0; i < 3; i++)
		{
			if (i == axisOneIndex)
				pointOnEdgeOne.SetIndex(i, 0);
			else if (boxOne.GetAxis(i).Dot(axis) > 0)
				pointOnEdgeOne.SetIndex(i, pointOnEdgeOne.GetIndex(i) * -1.0f);
			if (i == axisTwoIndex)
				pointOnEdgeTwo.SetIndex(i, 0);
			else if (boxTwo.GetAxis(i).Dot(axis) < 0)
				pointOnEdgeTwo.SetIndex(i, pointOnEdgeOne.GetIndex(i) * -1.0f);
		}

		pointOnEdgeOne = boxOne.GetTransform() * pointOnEdgeOne;
		pointOnEdgeTwo = boxTwo.GetTransform() * pointOnEdgeTwo;

		Vector3D vertex = getContactPoint(pointOnEdgeOne, axisOne, boxOne.GetHalfSize().GetIndex(axisOneIndex),
			pointOnEdgeTwo, axisTwo, boxTwo.GetHalfSize().GetIndex(axisTwoIndex), bestSingleAxis > 2);

		RigidContact rigidContact = RigidContact();
		rigidContact.Initialize(boxOne.GetRigidBody(), boxTwo.GetRigidBody(), vertex, axis, penetration, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
		collisionHandler->AddContact(rigidContact);
		return 1;
	}

	return 0;
}

//-----------------------------------------------------------------------------
void CollisionDetector::CheckCollision(RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo, CollisionHandler* collisionHandler)
{
	if (rigidBodyOne->GetCollisionType() == CollisionType::SPHERE)
	{
		switch (rigidBodyTwo->GetCollisionType())
		{
		case CollisionType::SPHERE:
			SphereAndSphere(rigidBodyOne->GetCollisionSphere(), rigidBodyTwo->GetCollisionSphere(), collisionHandler);
			break;
		case CollisionType::BOX:
			BoxAndSphere(rigidBodyTwo->GetCollisionBox(), rigidBodyOne->GetCollisionSphere(), collisionHandler);
			break;
		}
	}
	else if (rigidBodyOne->GetCollisionType() == CollisionType::BOX)
	{
		switch (rigidBodyTwo->GetCollisionType())
		{
		case CollisionType::SPHERE:
			BoxAndSphere(rigidBodyOne->GetCollisionBox(), rigidBodyTwo->GetCollisionSphere(), collisionHandler);
			break;
		case CollisionType::BOX:
			BoxAndBox(rigidBodyOne->GetCollisionBox(), rigidBodyTwo->GetCollisionBox(), collisionHandler);
			break;
		}
	}
}
//=============================================================================
