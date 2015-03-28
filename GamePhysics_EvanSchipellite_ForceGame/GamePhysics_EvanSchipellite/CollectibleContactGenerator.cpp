//=============================================================================
//                              Collectible Contact Generator
//
// Written by Evan Schipellite
//
// Detects Collectible Collisions with Player
//=============================================================================
#include "CollectibleContactGenerator.h"
#include "GameObject.h"
#include "CollisionHandler.h"
#include "CableContactGenerator.h"
//=============================================================================
CollectibleContactGenerator::CollectibleContactGenerator(Player* player, Collectible* collectible, float minDistance)
{
	mp_Player = player;
	mp_Collectible = collectible;

	m_MinDistance = minDistance;
}

//-----------------------------------------------------------------------------
CollectibleContactGenerator::~CollectibleContactGenerator()
{
}

//-----------------------------------------------------------------------------
void CollectibleContactGenerator::AddContact(CollisionHandler* collisionHandler)
{
	if (!mp_Collectible->GetAttached())
	{
		std::vector<GameObject*> gameObjects = mp_Collectible->GetGameObjects();
		std::vector<GameObject*>::iterator gameObjectIter;
		for (gameObjectIter = gameObjects.begin(); gameObjectIter != gameObjects.end(); gameObjectIter++)
		{
			float distance = mp_Player->GetPosition().GetDistance((*gameObjectIter)->GetPosition());

			if (distance <= m_MinDistance)
			{
				//collisionHandler->AddRunTimeContactGenerator(new CableContactGenerator((*gameObjectIter), mp_Player, m_MinDistance));
				//mp_Collectible->ToggleAttached(true);
				break;
			}
		}
	}
}
//=============================================================================