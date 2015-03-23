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
#include "RodContactGenerator.h"
#include "CableContactGenerator.h"
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
		forceRegisters.push_back(ForceRegister(GeneratorType::EARTH_GRAVITY_GENERATOR, (*collectibleObjectIter)));
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
		collectibleCollisiobObjects.push_back((*collectibleObjectIter));
	}

	return collectibleCollisiobObjects;
}

//-----------------------------------------------------------------------------
void Level::Initialize(Vector3D dimensions, std::string groundTexture, Vector3D playerPosition, std::string playerTexture, std::string collectibleTexture)
{
	mp_Ground->Initialize(dimensions, 1, Vector3D(0, -dimensions.Y, 0), groundTexture);
	mp_Player->Initialize(playerPosition, playerTexture);

	Collectible* collectibleOne = new Collectible();
	collectibleOne->Initialize(Vector3D(5, 5, 0), collectibleTexture);
	mp_CollectibleObjects.push_back(collectibleOne);
	mp_ContactGenerators.push_back(new CableContactGenerator(mp_Player, collectibleOne, 3));
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
	return mp_ContactGenerators;
}
//=============================================================================
