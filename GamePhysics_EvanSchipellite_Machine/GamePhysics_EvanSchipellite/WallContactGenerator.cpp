//=============================================================================
//                              Wall Contact Generator
//
// Written by Evan Schipellite
//
// Handles wall Contacts around a perimeter
//=============================================================================
#include "WallContactGenerator.h"
#include "PhysicsObject.h"
#include "CollisionHandler.h"
#include "Contact.h"
//=============================================================================
WallContactGenerator::WallContactGenerator(float minX, float maxX, float minZ, float maxZ)
{
	m_MinX = minX;
	m_MaxX = maxX;
	m_MinZ = minZ;
	m_MaxZ = maxZ;
}

//-----------------------------------------------------------------------------
WallContactGenerator::~WallContactGenerator()
{
}

//-----------------------------------------------------------------------------
void WallContactGenerator::AddContact(CollisionHandler* collisionHandler)
{
	std::vector<PhysicsObject*> physicsObjects = collisionHandler->GetPhysicsObjects();
	std::vector<PhysicsObject*>::iterator physicsObjectIter;
	for (physicsObjectIter = physicsObjects.begin(); physicsObjectIter != physicsObjects.end(); physicsObjectIter++)
	{
		float physicsObjectMinX = (*physicsObjectIter)->GetPosition().X;
		if (physicsObjectMinX - (*physicsObjectIter)->GetRadius() < m_MinX)
		{
			float minXPenetration = m_MinX - physicsObjectMinX;
			collisionHandler->AddContact(Contact((*physicsObjectIter)->GetRestitution(), minXPenetration, Vector3D(1, 0, 0), (*physicsObjectIter)));
		}

		float physicsObjectMaxX = (*physicsObjectIter)->GetPosition().X - (*physicsObjectIter)->GetRadius();
		if (physicsObjectMaxX  + (*physicsObjectIter)->GetRadius() * 2 > m_MaxX)
		{
			float maxXPenetration = m_MaxX - physicsObjectMaxX;
			collisionHandler->AddContact(Contact((*physicsObjectIter)->GetRestitution(), maxXPenetration, Vector3D(-1, 0, 0), (*physicsObjectIter)));
		}

		float physicsObjectMinZ = (*physicsObjectIter)->GetPosition().Z - (*physicsObjectIter)->GetRadius();
		if (physicsObjectMinZ < m_MinZ)
		{
			float minZPenetration = m_MinZ - physicsObjectMinZ;
			collisionHandler->AddContact(Contact((*physicsObjectIter)->GetRestitution(), minZPenetration, Vector3D(0, 0, 1), (*physicsObjectIter)));
		}

		float physicsObjectMaxZ = (*physicsObjectIter)->GetPosition().Z - (*physicsObjectIter)->GetRadius();
		if (physicsObjectMaxZ + (*physicsObjectIter)->GetRadius() * 2 > m_MaxZ)
		{
			float maxZPenetration = m_MaxZ - physicsObjectMaxZ;
			collisionHandler->AddContact(Contact((*physicsObjectIter)->GetRestitution(), maxZPenetration, Vector3D(0, 0, -1), (*physicsObjectIter)));
		}
	}
}
//=============================================================================
