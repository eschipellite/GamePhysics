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
void CubeCollectible::createContactGenerators()
{
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[0], mp_GameObjects[1], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[0], mp_GameObjects[2], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[0], mp_GameObjects[4], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[1], mp_GameObjects[3], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[1], mp_GameObjects[5], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[2], mp_GameObjects[3], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[2], mp_GameObjects[6], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[3], mp_GameObjects[7], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[4], mp_GameObjects[6], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[4], mp_GameObjects[5], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[5], mp_GameObjects[7], m_Size));
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[6], mp_GameObjects[7], m_Size));

	float oneFourDistance = mp_GameObjects[0]->GetPosition().GetDistance(mp_GameObjects[3]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[0], mp_GameObjects[3], oneFourDistance));
	float oneEightDistance = mp_GameObjects[0]->GetPosition().GetDistance(mp_GameObjects[7]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[0], mp_GameObjects[7], oneEightDistance));
	float twoSevenDistance = mp_GameObjects[1]->GetPosition().GetDistance(mp_GameObjects[6]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[1], mp_GameObjects[6], twoSevenDistance));
	float threeSixDistance = mp_GameObjects[2]->GetPosition().GetDistance(mp_GameObjects[5]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[2], mp_GameObjects[5], threeSixDistance));
	float fourFiveDistance = mp_GameObjects[3]->GetPosition().GetDistance(mp_GameObjects[4]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[3], mp_GameObjects[4], fourFiveDistance));
	float fiveEightDistance = mp_GameObjects[4]->GetPosition().GetDistance(mp_GameObjects[7]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[4], mp_GameObjects[7], fiveEightDistance));
	float twoEightDistance = mp_GameObjects[1]->GetPosition().GetDistance(mp_GameObjects[7]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[1], mp_GameObjects[7], twoEightDistance));
	float oneSevenDistance = mp_GameObjects[0]->GetPosition().GetDistance(mp_GameObjects[6]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[0], mp_GameObjects[6], oneSevenDistance));
}

//-----------------------------------------------------------------------------
void CubeCollectible::Initialize(Vector3D centerPosition, std::string texture, float size, float mass)
{
	m_Size = size;
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

	createContactGenerators();
}
//=============================================================================