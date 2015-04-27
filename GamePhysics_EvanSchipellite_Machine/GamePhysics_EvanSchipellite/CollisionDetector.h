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
//=============================================================================
class CollisionDetector
{
private:
	static float m_Mults[8][3];

private:
	void fillPointFaceBoxBox(const CollisionBox& boxOne, const CollisionBox& boxTwo, const Vector3D& toCenter, CollisionData* collisionData, unsigned int best, float penetration);
	Vector3D getContactPoint(const Vector3D& pointOne, const Vector3D& directionOne, float sizeOne, const Vector3D& pointTwo, const Vector3D directionTwo, float sizeTwo, bool useOne);

public:
	CollisionDetector();
	~CollisionDetector();

	unsigned int SphereAndSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo, CollisionHandler* collisionData);
	unsigned int SphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionHandler* collisionData);
	unsigned int SphereAndTruePlane(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionHandler* collisionData);
	unsigned int BoxAndHalfSpace(const CollisionBox& box, const CollisionPlane& plane, CollisionHandler* collisionData);
	unsigned int BoxAndSphere(const CollisionBox& box, const CollisionSphere& sphere, CollisionHandler* collisionData);
	unsigned int BoxAndBox(const CollisionBox& boxOne, const CollisionBox& boxTwo, CollisionHandler* collisionData);
};
//=============================================================================
#endif // COLLISION_DETECTOR_H