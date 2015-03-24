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
#include "SpringContactGenerator.h"
#include "BungeeContactGenerator.h"
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
			forceRegisters.push_back(ForceRegister(GeneratorType::EARTH_GRAVITY_GENERATOR, (*gameObjectIter)));
		}
	}

	return forceRegisters;
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
void Level::Initialize(Vector3D dimensions, std::string groundTexture, Vector3D playerPosition, std::string playerTexture, std::string collectibleTexture)
{
	mp_Ground->Initialize(dimensions, 1, Vector3D(0, -dimensions.Y, 0), groundTexture);
	mp_Player->Initialize(playerPosition, playerTexture);

	TetrahedronCollectible* collectibleOne = new TetrahedronCollectible();
	collectibleOne->Initialize(Vector3D(5, 5, 0), collectibleTexture, 5);
	mp_CollectibleObjects.push_back(collectibleOne);

	CubeCollectible* collectibleTwo = new CubeCollectible();
	collectibleTwo->Initialize(Vector3D(-15, 5, 0), collectibleTexture, 5);
	mp_CollectibleObjects.push_back(collectibleTwo);

	DiamondCollectible* collectibleThree = new DiamondCollectible();
	collectibleThree->Initialize(Vector3D(20, 5, 0), collectibleTexture, 5);
	mp_CollectibleObjects.push_back(collectibleThree);

	//mp_ContactGenerators.push_back(new BungeeContactGenerator(mp_Player, collectibleOne, .5f, 1));
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
}

//-----------------------------------------------------------------------------
std::vector<ForceRegister> Level::GetForceRegisters()
{
	std::vector<ForceRegister> forceRegisters = getCollectibleForceRegisters();

	forceRegisters.push_back(ForceRegister(GeneratorType::EARTH_GRAVITY_GENERATOR, mp_Player));

	return forceRegisters;
}

//-----------------------------------------------------------------------------
PhysicsObject* Level::GetGround()
{
	return dynamic_cast <PhysicsObject*>(mp_Ground);
}

//-----------------------------------------------------------------------------
std::vector<PhysicsObject*> Level::GetCollisionObjects()
{
	std::vector<PhysicsObject*> collisionObjects = getCollectibleCollisionObjects();

	collisionObjects.push_back(mp_Player);

	return collisionObjects;
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
	}

	return contactGenerators;
}
//=============================================================================
