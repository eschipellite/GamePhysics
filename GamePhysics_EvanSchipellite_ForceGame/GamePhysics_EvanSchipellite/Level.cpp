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
void Level::createLevel()
{
	std::string line;
	std::ifstream levelFile("Content/Files/Level.txt");
	if (levelFile.is_open())
	{
		while (std::getline(levelFile, line))
		{
			std::string buffer;
			std::stringstream stringStream(line);

			std::vector<std::string> tokens; // Create vector to hold our words

			while (stringStream >> buffer)
			{
				tokens.push_back(buffer);
			}

			int collectibleType = atoi(tokens[0].c_str());
			float x = float(atoi(tokens[1].c_str()));
			float y = float(atoi(tokens[2].c_str()));
			float z = float(atoi(tokens[3].c_str()));
			float size = float(atoi(tokens[4].c_str()));

			switch (collectibleType)
			{
			case 0:
			{
				CubeCollectible* cubeCollectible = new CubeCollectible();
				cubeCollectible->Initialize(Vector3D(x, y, z), m_CollectibleTexture, size);
				mp_CollectibleObjects.push_back(cubeCollectible);
			}
				break;
			case 1:
			{
				TetrahedronCollectible* tetrahedronCollectible = new TetrahedronCollectible();
				tetrahedronCollectible->Initialize(Vector3D(x, y, z), m_CollectibleTexture, size);
				mp_CollectibleObjects.push_back(tetrahedronCollectible);
			}
				break;
			case 2:
			{
				DiamondCollectible* diamondCollectible = new DiamondCollectible();
				diamondCollectible->Initialize(Vector3D(x, y, z), m_CollectibleTexture, size);
				mp_CollectibleObjects.push_back(diamondCollectible);
			}
				break;
			default:
			{
				Collectible* sphereCollectible = new Collectible();
				sphereCollectible->Initialize(Vector3D(x, y, z), m_CollectibleTexture, size);
				mp_CollectibleObjects.push_back(sphereCollectible);
			}
				break;
			}
		}
		levelFile.close();
	}
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
			forceRegisters.push_back(ForceRegister(new EarthGravityGenerator(Vector3D(0, -9.8f, 0)), (*gameObjectIter)));
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
	mp_Player->Initialize(playerPosition, playerTexture, 20, 400);

	m_CollectibleTexture = collectibleTexture;

	createLevel();
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
std::vector<ForceRegister> Level::GetForceRegisters()
{
	std::vector<ForceRegister> forceRegisters = getCollectibleForceRegisters();

	forceRegisters.push_back(ForceRegister(new EarthGravityGenerator(Vector3D(0, -9.8f, 0)), mp_Player));

	return forceRegisters;
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
	mp_Player->HandleKeyPressed(key);
}

//-----------------------------------------------------------------------------
void Level::HandleKeyReleased(unsigned char key)
{
	mp_Player->HandleKeyReleased(key);
}
//=============================================================================
