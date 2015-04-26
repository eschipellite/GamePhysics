//=============================================================================
//                              Level
//
// Written by Evan Schipellite
//
// Manages physics objects within the level
//=============================================================================
#include "Level.h"
#include "Vector3D.h"
#include "Ground.h"
#include "Player.h"
#include <vector>
#include "PhysicsHandler.h"
#include "PhysicsObject.h"
#include "Collectible.h"
#include "CubeCollectible.h"
#include "DiamondCollectible.h"
#include "TetrahedronCollectible.h"
#include "RodContactGenerator.h"
#include "CableContactGenerator.h"
#include "SpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "EarthGravityGenerator.h"
#include "CollectibleContactGenerator.h"
#include "WallContactGenerator.h"
#include "RigidRender.h"
#include "RigidSphere.h"
#include "RigidBody.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
//=============================================================================
Level::Level()
{
	mp_Ground = new Ground();
	mp_Player = new Player();
}

//-----------------------------------------------------------------------------
Level::~Level()
{
}

//-----------------------------------------------------------------------------
void Level::drawCollectibles()
{
	std::vector<Collectible*>::iterator collectibleObjectIter;
	for (collectibleObjectIter = mp_CollectibleObjects.begin(); collectibleObjectIter != mp_CollectibleObjects.end(); collectibleObjectIter++)
	{
		(*collectibleObjectIter)->Draw();
	}
}

//-----------------------------------------------------------------------------
void Level::drawRigidRenders()
{
	std::vector<RigidRender*>::iterator rigidRenderIter;
	for (rigidRenderIter = mp_RigidRenders.begin(); rigidRenderIter != mp_RigidRenders.end(); rigidRenderIter++)
	{
		(*rigidRenderIter)->Draw();
	}
}

//-----------------------------------------------------------------------------
void Level::updateCollectibles(float deltaTime)
{
	std::vector<Collectible*>::iterator collectibleObjectIter;
	for (collectibleObjectIter = mp_CollectibleObjects.begin(); collectibleObjectIter != mp_CollectibleObjects.end(); collectibleObjectIter++)
	{
		(*collectibleObjectIter)->Update(deltaTime);
	}
}

//-----------------------------------------------------------------------------
void Level::resetCollectibles()
{
	std::vector<Collectible*>::iterator collectibleObjectIter;
	for (collectibleObjectIter = mp_CollectibleObjects.begin(); collectibleObjectIter != mp_CollectibleObjects.end(); collectibleObjectIter++)
	{
		(*collectibleObjectIter)->Reset();
	}
}

//-----------------------------------------------------------------------------
void Level::resetRigidRenders()
{
	std::vector<RigidRender*>::iterator rigidRenderIter;
	for (rigidRenderIter = mp_RigidRenders.begin(); rigidRenderIter != mp_RigidRenders.end(); rigidRenderIter++)
	{
		(*rigidRenderIter)->Reset();
	}
}

//-----------------------------------------------------------------------------
std::vector<ForceRegister> Level::getCollectibleForceRegisters()
{
	std::vector<ForceRegister> forceRegisters;
	std::vector<Collectible*>::iterator collectibleObjectIter;
	for (collectibleObjectIter = mp_CollectibleObjects.begin(); collectibleObjectIter != mp_CollectibleObjects.end(); collectibleObjectIter++)
	{
		std::vector<GameObject*> collectibleObjects = (*collectibleObjectIter)->GetGameObjects();
		std::vector<GameObject*>::iterator gameObjectIter;
		for (gameObjectIter = collectibleObjects.begin(); gameObjectIter != collectibleObjects.end(); gameObjectIter++)
		{
			forceRegisters.push_back(ForceRegister(new EarthGravityGenerator(Vector3D(0, -9.8f, 0)), (*gameObjectIter)));
		}
	}

	return forceRegisters;
}

//-----------------------------------------------------------------------------
std::vector<RigidForceRegister> Level::getRigidRenderRegisters()
{
	std::vector<RigidForceRegister> rigidForceRegisters;
	std::vector<RigidRender*>::iterator rigidRenderIter;
	for (rigidRenderIter = mp_RigidRenders.begin(); rigidRenderIter != mp_RigidRenders.end(); rigidRenderIter++)
	{
		rigidForceRegisters.push_back(RigidForceRegister(new EarthGravityGenerator(Vector3D(0, -9.8f, 0)), (*rigidRenderIter)));
	}

	return rigidForceRegisters;
}

//-----------------------------------------------------------------------------
std::vector<PhysicsObject*> Level::getCollectibleCollisionObjects()
{
	std::vector<PhysicsObject*> collectibleCollisiobObjects;
	std::vector<Collectible*>::iterator collectibleObjectIter;
	for (collectibleObjectIter = mp_CollectibleObjects.begin(); collectibleObjectIter != mp_CollectibleObjects.end(); collectibleObjectIter++)
	{
		std::vector<GameObject*> collectibleObjects = (*collectibleObjectIter)->GetGameObjects();
		std::vector<GameObject*>::iterator gameObjectIter;
		for (gameObjectIter = collectibleObjects.begin(); gameObjectIter != collectibleObjects.end(); gameObjectIter++)
		{
			collectibleCollisiobObjects.push_back((*gameObjectIter));
		}
	}

	return collectibleCollisiobObjects;
}

//-----------------------------------------------------------------------------
void Level::Initialize(Vector3D dimensions, Vector3D playerPosition, std::string groundID, std::string playerID, std::string collectibleID)
{
	mp_Ground->Initialize(dimensions, 1, Vector3D(0, -dimensions.Y, 0), groundID);
	mp_Player->Initialize(playerPosition, playerID, 20, 400);

	m_CollectibleTextureID = collectibleID;

	RigidSphere* rigidRenderSphere = new RigidSphere();
	rigidRenderSphere->Initialize(m_CollectibleTextureID, 1, 1, Vector3D(0, 10, 0));
	mp_RigidRenders.push_back(rigidRenderSphere);
}

//-----------------------------------------------------------------------------
void Level::CleanUp()
{
	if (mp_Player != NULL)
	{
		mp_Player->CleanUp();
	}
	delete mp_Player;
	mp_Player = nullptr;

	if (mp_Ground != NULL)
	{
		mp_Ground->CleanUp();
	}
	delete mp_Ground;
	mp_Ground = nullptr;

	std::vector<RigidRender*>::iterator rigidRenderIter;
	for (rigidRenderIter = mp_RigidRenders.begin(); rigidRenderIter != mp_RigidRenders.end(); rigidRenderIter++)
	{
		delete (*rigidRenderIter);
		(*rigidRenderIter) = nullptr;
	}

	std::vector<Collectible*>::iterator collectibleObjectIter;
	for (collectibleObjectIter = mp_CollectibleObjects.begin(); collectibleObjectIter != mp_CollectibleObjects.end(); collectibleObjectIter++)
	{
		(*collectibleObjectIter)->CleanUp();
		delete (*collectibleObjectIter);
		(*collectibleObjectIter) = nullptr;
	}
	mp_CollectibleObjects.clear();
	mp_ContactGenerators.clear();
}

//-----------------------------------------------------------------------------
void Level::Draw()
{
	mp_Ground->Draw();
	mp_Player->Draw();
	drawCollectibles();
	drawRigidRenders();
}

//-----------------------------------------------------------------------------
void Level::Update(float deltaTime)
{
	mp_Ground->Update(deltaTime);
	mp_Player->Update(deltaTime);
	updateCollectibles(deltaTime);
}

//-----------------------------------------------------------------------------
void Level::Reset()
{
	mp_Ground->Reset();
	mp_Player->Reset();
	resetCollectibles();
	resetRigidRenders();
}

//-----------------------------------------------------------------------------
PhysicsObject* Level::GetGround()
{
	return dynamic_cast <PhysicsObject*>(mp_Ground);
}

//-----------------------------------------------------------------------------
PhysicsObject* Level::GetPlayer()
{
	return dynamic_cast <PhysicsObject*>(mp_Player);
}

//-----------------------------------------------------------------------------
std::vector<PhysicsObject*> Level::GetCollisionObjects()
{
	std::vector<PhysicsObject*> collisionObjects = getCollectibleCollisionObjects();

	collisionObjects.push_back(mp_Player);

	return collisionObjects;
}

//-----------------------------------------------------------------------------
std::vector<RigidBody*> Level::GetRigidBodies()
{
	std::vector<RigidBody*> rigidBodies;
	std::vector<RigidRender*>::iterator rigidRenderIter;
	for (rigidRenderIter = mp_RigidRenders.begin(); rigidRenderIter != mp_RigidRenders.end(); rigidRenderIter++)
	{
		rigidBodies.push_back((*rigidRenderIter));
	}

	return rigidBodies;
}

//-----------------------------------------------------------------------------
std::vector<ForceRegister> Level::GetForceRegisters()
{
	std::vector<ForceRegister> forceRegisters = getCollectibleForceRegisters();

	forceRegisters.push_back(ForceRegister(new EarthGravityGenerator(Vector3D(0, -9.8f, 0)), mp_Player));

	return forceRegisters;
}

//-----------------------------------------------------------------------------
std::vector<RigidForceRegister> Level::GetRigidForceRegisters()
{
	std::vector<RigidForceRegister> rigidRenderRegisters = getRigidRenderRegisters();
	
	return rigidRenderRegisters;
}

//-----------------------------------------------------------------------------
std::vector<ContactGenerator*> Level::GetContactGenerators()
{
	std::vector<ContactGenerator*> contactGenerators;
	contactGenerators.insert(contactGenerators.end(), mp_ContactGenerators.begin(), mp_ContactGenerators.end());

	std::vector<Collectible*>::iterator collectibleObjectIter;
	for (collectibleObjectIter = mp_CollectibleObjects.begin(); collectibleObjectIter != mp_CollectibleObjects.end(); collectibleObjectIter++)
	{
		std::vector<ContactGenerator*> collectibleContactGenerators = (*collectibleObjectIter)->GetContactGenerators();
		contactGenerators.insert(contactGenerators.end(), collectibleContactGenerators.begin(), collectibleContactGenerators.end());
		contactGenerators.push_back(new CollectibleContactGenerator(mp_Player, (*collectibleObjectIter), 3));
	}

	contactGenerators.push_back(new WallContactGenerator(-60, 60, -60, 60));

	return contactGenerators;
}

//-----------------------------------------------------------------------------
void Level::HandleKeyPressed(unsigned char key)
{
}

//-----------------------------------------------------------------------------
void Level::HandleKeyReleased(unsigned char key)
{
}

//-----------------------------------------------------------------------------
int Level::GetObjectsCollected()
{
	int objectsCollected = 0;
	std::vector<Collectible*>::iterator collectibleObjectIter;
	for (collectibleObjectIter = mp_CollectibleObjects.begin(); collectibleObjectIter != mp_CollectibleObjects.end(); collectibleObjectIter++)
	{
		if ((*collectibleObjectIter)->GetAttached())
		{
			objectsCollected++;
		}
	}

	return objectsCollected;
}
//=============================================================================
