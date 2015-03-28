//=============================================================================
//                              Diamond Collectible
//
// Written by Evan Schipellite
//=============================================================================
#include "DiamondCollectible.h"
#include "RodContactGenerator.h"
//=============================================================================
DiamondCollectible::DiamondCollectible()
{
}

//-----------------------------------------------------------------------------
DiamondCollectible::~DiamondCollectible()
{
}

//-----------------------------------------------------------------------------
void DiamondCollectible::createContactGenerators()
{
	float fourOneDistance = mp_GameObjects[3]->GetPosition().GetDistance(mp_GameObjects[0]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[3], mp_GameObjects[0], fourOneDistance));
	float fourTwoDistance = mp_GameObjects[3]->GetPosition().GetDistance(mp_GameObjects[1]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[3], mp_GameObjects[1], fourTwoDistance));
	float fourThreeDistance = mp_GameObjects[3]->GetPosition().GetDistance(mp_GameObjects[2]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[3], mp_GameObjects[2], fourThreeDistance));
	float oneTwoDistance = mp_GameObjects[0]->GetPosition().GetDistance(mp_GameObjects[1]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[0], mp_GameObjects[1], oneTwoDistance));
	float oneThreeDistance = mp_GameObjects[0]->GetPosition().GetDistance(mp_GameObjects[2]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[0], mp_GameObjects[2], oneThreeDistance));
	float twoThreeDistance = mp_GameObjects[1]->GetPosition().GetDistance(mp_GameObjects[2]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[1], mp_GameObjects[2], twoThreeDistance));

	float fiveOneDistance = mp_GameObjects[4]->GetPosition().GetDistance(mp_GameObjects[0]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[4], mp_GameObjects[0], fiveOneDistance));
	float fiveTwoDistance = mp_GameObjects[4]->GetPosition().GetDistance(mp_GameObjects[1]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[4], mp_GameObjects[1], fiveTwoDistance));
	float fiveThreeDistance = mp_GameObjects[3]->GetPosition().GetDistance(mp_GameObjects[2]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[4], mp_GameObjects[2], fiveThreeDistance));

	float fourFiveDistance = mp_GameObjects[3]->GetPosition().GetDistance(mp_GameObjects[4]->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(mp_GameObjects[3], mp_GameObjects[4], fourFiveDistance));
}

//-----------------------------------------------------------------------------
void DiamondCollectible::Initialize(Vector3D centerPosition, std::string texture, float size, float mass)
{
	float halfSize = size * 0.5f;

	//Bot-Top
	GameObject* gameObjectOne = new GameObject();
	Vector3D positionOne = Vector3D(centerPosition.X, centerPosition.Y, centerPosition.Z + halfSize);
	gameObjectOne->Initialize(positionOne, texture, mass);
	mp_GameObjects.push_back(gameObjectOne);

	//Bot-Left
	GameObject* gameObjectTwo = new GameObject();
	Vector3D positionTwo = Vector3D(centerPosition.X - halfSize, centerPosition.Y, centerPosition.Z - halfSize);
	gameObjectTwo->Initialize(positionTwo, texture, mass);
	mp_GameObjects.push_back(gameObjectTwo);

	//Bot-Right
	GameObject* gameObjectThree = new GameObject();
	Vector3D positionThree = Vector3D(centerPosition.X + halfSize, centerPosition.Y, centerPosition.Z - halfSize);
	gameObjectThree->Initialize(positionThree, texture, mass);
	mp_GameObjects.push_back(gameObjectThree);

	//Top
	GameObject* gameObjectFour = new GameObject();
	Vector3D positionFour = Vector3D(centerPosition.X, centerPosition.Y + halfSize, centerPosition.Z);
	gameObjectFour->Initialize(positionFour, texture, mass);
	mp_GameObjects.push_back(gameObjectFour);

	//Bot
	GameObject* gameObjectFive = new GameObject();
	Vector3D positionFive = Vector3D(centerPosition.X, centerPosition.Y - halfSize, centerPosition.Z);
	gameObjectFive->Initialize(positionFive, texture, mass);
	mp_GameObjects.push_back(gameObjectFive);

	createContactGenerators();
}
//=============================================================================