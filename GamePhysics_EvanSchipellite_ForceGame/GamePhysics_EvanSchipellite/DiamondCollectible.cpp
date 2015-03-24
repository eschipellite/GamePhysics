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

	float fourOneDistance = gameObjectFour->GetPosition().GetDistance(gameObjectOne->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFour, gameObjectOne, fourOneDistance));
	float fourTwoDistance = gameObjectFour->GetPosition().GetDistance(gameObjectTwo->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFour, gameObjectTwo, fourTwoDistance));
	float fourThreeDistance = gameObjectFour->GetPosition().GetDistance(gameObjectThree->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFour, gameObjectThree, fourThreeDistance));
	float oneTwoDistance = gameObjectOne->GetPosition().GetDistance(gameObjectTwo->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectOne, gameObjectTwo, oneTwoDistance));
	float oneThreeDistance = gameObjectOne->GetPosition().GetDistance(gameObjectThree->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectOne, gameObjectThree, oneThreeDistance));
	float twoThreeDistance = gameObjectTwo->GetPosition().GetDistance(gameObjectThree->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectTwo, gameObjectThree, twoThreeDistance));

	float fiveOneDistance = gameObjectFive->GetPosition().GetDistance(gameObjectOne->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFive, gameObjectOne, fiveOneDistance));
	float fiveTwoDistance = gameObjectFive->GetPosition().GetDistance(gameObjectTwo->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFive, gameObjectTwo, fiveTwoDistance));
	float fiveThreeDistance = gameObjectFour->GetPosition().GetDistance(gameObjectThree->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFive, gameObjectThree, fiveThreeDistance));

	float fourFiveDistance = gameObjectFour->GetPosition().GetDistance(gameObjectFive->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFour, gameObjectFive, fourFiveDistance));
}
//=============================================================================