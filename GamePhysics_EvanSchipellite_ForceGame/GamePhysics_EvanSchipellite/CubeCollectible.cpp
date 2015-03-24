//=============================================================================
//                              Cube Collectible
//
// Written by Evan Schipellite
//=============================================================================
#include "CubeCollectible.h"
#include "RodContactGenerator.h"
#include "CableContactGenerator.h"
//=============================================================================
CubeCollectible::CubeCollectible()
{
}

//-----------------------------------------------------------------------------
CubeCollectible::~CubeCollectible()
{
}

//-----------------------------------------------------------------------------
void CubeCollectible::Initialize(Vector3D centerPosition, std::string texture, float size, float mass)
{
	float halfSize = size * 0.5f;

	//Left-Up-Front
	GameObject* gameObjectOne = new GameObject();
	Vector3D positionOne = Vector3D(centerPosition.X - halfSize, centerPosition.Y + halfSize, centerPosition.Z + halfSize);
	gameObjectOne->Initialize(positionOne, texture, mass);
	mp_GameObjects.push_back(gameObjectOne);

	//Right-Up-Front
	GameObject* gameObjectTwo = new GameObject();
	Vector3D positionTwo = Vector3D(centerPosition.X + halfSize, centerPosition.Y + halfSize, centerPosition.Z + halfSize);
	gameObjectTwo->Initialize(positionTwo, texture, mass);
	mp_GameObjects.push_back(gameObjectTwo);

	//Left-Up-Back
	GameObject* gameObjectThree = new GameObject();
	Vector3D positionThree = Vector3D(centerPosition.X - halfSize, centerPosition.Y + halfSize, centerPosition.Z - halfSize);
	gameObjectThree->Initialize(positionThree, texture, mass);
	mp_GameObjects.push_back(gameObjectThree);

	//Right-Up-Back
	GameObject* gameObjectFour = new GameObject();
	Vector3D positionFour = Vector3D(centerPosition.X + halfSize, centerPosition.Y + halfSize, centerPosition.Z - halfSize);
	gameObjectFour->Initialize(positionFour, texture, mass);
	mp_GameObjects.push_back(gameObjectFour);

	//Left-Bottom-Front
	GameObject* gameObjectFive = new GameObject();
	Vector3D positionFive = Vector3D(centerPosition.X - halfSize, centerPosition.Y - halfSize, centerPosition.Z + halfSize);
	gameObjectFive->Initialize(positionFive, texture, mass);
	mp_GameObjects.push_back(gameObjectFive);

	//Right-Bottom-Front
	GameObject* gameObjectSix = new GameObject();
	Vector3D positionSix = Vector3D(centerPosition.X + halfSize, centerPosition.Y - halfSize, centerPosition.Z + halfSize);
	gameObjectSix->Initialize(positionSix, texture, mass);
	mp_GameObjects.push_back(gameObjectSix);

	//Left-Bottom-Back
	GameObject* gameObjectSeven = new GameObject();
	Vector3D positionSeven = Vector3D(centerPosition.X - halfSize, centerPosition.Y - halfSize, centerPosition.Z - halfSize);
	gameObjectSeven->Initialize(positionSeven, texture, mass);
	mp_GameObjects.push_back(gameObjectSeven);

	//Right-Bottom-Back
	GameObject* gameObjectEight = new GameObject();
	Vector3D positionEight = Vector3D(centerPosition.X + halfSize, centerPosition.Y - halfSize, centerPosition.Z - halfSize);
	gameObjectEight->Initialize(positionEight, texture, mass);
	mp_GameObjects.push_back(gameObjectEight);

	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectOne, gameObjectTwo, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectOne, gameObjectThree, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectOne, gameObjectFive, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectTwo, gameObjectFour, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectTwo, gameObjectSix, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectThree, gameObjectFour, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectThree, gameObjectSeven, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFour, gameObjectEight, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFive, gameObjectSeven, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFive, gameObjectSix, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectSix, gameObjectEight, size));
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectSeven, gameObjectEight, size));
}
//=============================================================================