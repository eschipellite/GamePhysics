//=============================================================================
//                              Collision Detector
//
// Written by Evan Schipellite
//
// Basis from: https://github.com/idmillington/cyclone-physics
//=============================================================================
#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H
//=============================================================================
#include "CollisionData.h"
#include "CollisionSphere.h"
#include "CollisionPlane.h"
#include "CollisionBox.h"
#include "CollisionHandler.h"
#include "RigidBody.h"
//=============================================================================
class CollisionDetector
{
private:
	static float m_Mults[8][3];

private:
	void fillPointFaceBoxBox(const CollisionBox& boxOne, const CollisionBox& boxTwo, const Vector3D& toCenter, CollisionHandler* collisionHandler, unsigned int best, float penetration);
	Vector3D getContactPoint(const Vector3D& pointOne, const Vector3D& directionOne, float sizeOne, const Vector3D& pointTwo, const Vector3D directionTwo, float sizeTwo, bool useOne);

public:
	CollisionDetector();
	~CollisionDetector();

	unsigned int SphereAndSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo, CollisionHandler* collisionHandler);
	unsigned int SphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionHandler* collisionHandler);
	unsigned int SphereAndTruePlane(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionHandler* collisionHandler);
	unsigned int BoxAndHalfSpace(const CollisionBox& box, const CollisionPlane& plane, CollisionHandler* collisionHandler);
	unsigned int BoxAndSphere(const CollisionBox& box, const CollisionSphere& sphere, CollisionHandler* collisionHandler);
	unsigned int BoxAndBox(const CollisionBox& boxOne, const CollisionBox& boxTwo, CollisionHandler* collisionHandler);

	void CheckCollision(RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo, CollisionHandler* collisionHandler);
};
//=============================================================================
#endif // COLLISION_DETECTOR_H