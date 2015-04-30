//=============================================================================
//                              Rigid Render Contact Generator
//
// Written by Evan Schipellite
//
//=============================================================================
#include "RigidRenderContactGenerator.h"
#include "RigidBody.h"
#include "CollisionHandler.h"
#include "CollisionDetector.h"
//=============================================================================
RigidRenderContactGenerator::RigidRenderContactGenerator()
{
}

//-----------------------------------------------------------------------------
RigidRenderContactGenerator::~RigidRenderContactGenerator()
{
}

//-----------------------------------------------------------------------------
void RigidRenderContactGenerator::AddContact(CollisionHandler* collisionHandler)
{
	std::vector<RigidBody*> rigidBodies = collisionHandler->GetRigidBodies();

	for (unsigned int i = 0; i < rigidBodies.size(); ++i)
	{
		for (unsigned int j = i + 1; j < rigidBodies.size(); j++)
		{
			RigidBody* rigidBodyOne = rigidBodies[i];
			RigidBody* rigidBodyTwo = rigidBodies[j];

			collisionHandler->GetCollisionDetector()->CheckCollision(rigidBodyOne, rigidBodyTwo, collisionHandler);
		}
	}
}
//=============================================================================