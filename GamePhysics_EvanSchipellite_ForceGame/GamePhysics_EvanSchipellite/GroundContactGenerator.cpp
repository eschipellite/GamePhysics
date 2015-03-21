//=============================================================================
//                              Ground Contact Generator
//
// Written by Evan Schipellite
//
// Handles Ground Contact at a Y position
//=============================================================================
#include "GroundContactGenerator.h"
#include "PhysicsObject.h"
#include "CollisionHandler.h"
#include "Contact.h"
//=============================================================================
GroundContactGenerator::GroundContactGenerator(float groundY)
{
	m_GroundY = groundY;
}

//-----------------------------------------------------------------------------
GroundContactGenerator::~GroundContactGenerator()
{
}

//-----------------------------------------------------------------------------
void GroundContactGenerator::AddContact(CollisionHandler* collisionHandler)
{
	std::vector<PhysicsObject*> physicsObjects = collisionHandler->GetPhysicsObjects();
	std::vector<PhysicsObject*>::iterator physicsObjectIter;
	for (physicsObjectIter = physicsObjects.begin(); physicsObjectIter != physicsObjects.end(); physicsObjectIter++)
	{
		float physicsObjectY = (*physicsObjectIter)->GetPosition().Y - (*physicsObjectIter)->GetRadius();
		if (physicsObjectY < m_GroundY)
		{
			float penetration = m_GroundY - physicsObjectY;
			collisionHandler->AddContact(Contact((*physicsObjectIter)->GetRestitution(), penetration, Vector3D::Up, (*physicsObjectIter)));
		}
	}
}
//=============================================================================