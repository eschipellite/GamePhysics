//=============================================================================
//                              Collision Detector
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H
//=============================================================================
#include "CollisionData.h"
#include "CollisionSphere.h"
#include "CollisionPlane.h"
//=============================================================================
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	unsigned int SphereAndSphere(const CollisionSphere &sphereOne, const CollisionSphere &sphereTwo, CollisionData *collisionData);
	unsigned int SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *collisionData);
	unsigned int SphereAndTruePlane(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *collisionData);
};
//=============================================================================
#endif // COLLISION_DETECTOR_H