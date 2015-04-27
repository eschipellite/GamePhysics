//=============================================================================
//                              Rigid Ground Contact Generator
//
// Written by Evan Schipellite
//
//=============================================================================
#include "RigidGroundContactGenerator.h"
#include "RigidBody.h"
#include "CollisionHandler.h"
#include "RigidContact.h"
#include "CollisionDetector.h"
//=============================================================================
RigidGroundContactGenerator::RigidGroundContactGenerator(float groundY)
{
	m_CollisionPlane = CollisionPlane();
	m_CollisionPlane.SetDirection(Vector3D(0, 1, 0));

	SetGroundY(groundY);
}

//-----------------------------------------------------------------------------
RigidGroundContactGenerator::~RigidGroundContactGenerator()
{
}

//-----------------------------------------------------------------------------
void RigidGroundContactGenerator::AddContact(CollisionHandler* collisionHandler)
{
	std::vector<RigidBody*> rigidBodies = collisionHandler->GetRigidBodies();
	std::vector<RigidBody*>::iterator rigidBodyIter;
	for (rigidBodyIter = rigidBodies.begin(); rigidBodyIter != rigidBodies.end(); rigidBodyIter++)
	{
		collisionHandler->GetCollisionDetector()->SphereAndHalfSpace((*rigidBodyIter)->GetCollisionSphere(), m_CollisionPlane, collisionHandler);
	}
}

//-----------------------------------------------------------------------------
void RigidGroundContactGenerator::SetGroundY(float groundY)
{
	m_CollisionPlane.SetOffset(groundY);
}
//=============================================================================