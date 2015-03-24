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

	//Center Top-Left
	GameObject* gameObjectOne = new GameObject();
	Vector3D positionOne = Vector3D(centerPosition.X - halfSize, centerPosition.Y, centerPosition.Z + halfSize);
	gameObjectOne->Initialize(positionOne, texture, mass);
	mp_GameObjects.push_back(gameObjectOne);

	//Center Top-Right
	GameObject* gameObjectTwo = new GameObject();
	Vector3D positionTwo = Vector3D(centerPosition.X + halfSize, centerPosition.Y, centerPosition.Z + halfSize);
	gameObjectTwo->Initialize(positionTwo, texture, mass);
	mp_GameObjects.push_back(gameObjectTwo);

	//Center Bot-Left
	GameObject* gameObjectThree = new GameObject();
	Vector3D positionThree = Vector3D(centerPosition.X - halfSize, centerPosition.Y, centerPosition.Z - halfSize);
	gameObjectThree->Initialize(positionThree, texture, mass);
	mp_GameObjects.push_back(gameObjectThree);

	//Center Bot-Right
	GameObject* gameObjectFour = new GameObject();
	Vector3D positionFour = Vector3D(centerPosition.X + halfSize, centerPosition.Y, centerPosition.Z - halfSize);
	gameObjectFour->Initialize(positionFour, texture, mass);
	mp_GameObjects.push_back(gameObjectFour);

	//Top
	GameObject* gameObjectFive = new GameObject();
	Vector3D positionFive = Vector3D(centerPosition.X, centerPosition.Y + halfSize, centerPosition.Z);
	gameObjectFive->Initialize(positionFive, texture, mass);
	mp_GameObjects.push_back(gameObjectFive);

	//Bottom
	GameObject* gameObjectSix = new GameObject();
	Vector3D positionSix = Vector3D(centerPosition.X, centerPosition.Y - halfSize, centerPosition.Z);
	gameObjectSix->Initialize(positionSix, texture, mass);
	mp_GameObjects.push_back(gameObjectSix);

	float fiveOneDistance = gameObjectFive->GetPosition().GetDistance(gameObjectOne->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFive, gameObjectOne, fiveOneDistance));
	float fiveTwoDistance = gameObjectFive->GetPosition().GetDistance(gameObjectTwo->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFive, gameObjectTwo, fiveTwoDistance));
	float fiveThreeDistance = gameObjectFive->GetPosition().GetDistance(gameObjectThree->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFive, gameObjectThree, fiveThreeDistance));
	float fiveFourDistance = gameObjectFive->GetPosition().GetDistance(gameObjectFour->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectFive, gameObjectFour, fiveFourDistance));

	float sixOneDistance = gameObjectSix->GetPosition().GetDistance(gameObjectOne->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectSix, gameObjectOne, sixOneDistance));
	float sixTwoDistance = gameObjectSix->GetPosition().GetDistance(gameObjectTwo->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectSix, gameObjectTwo, sixTwoDistance));
	float sixThreeDistance = gameObjectSix->GetPosition().GetDistance(gameObjectThree->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectSix, gameObjectThree, sixThreeDistance));
	float sixFourDistance = gameObjectSix->GetPosition().GetDistance(gameObjectFour->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectSix, gameObjectFour, sixFourDistance));

	float oneTwoDistance = gameObjectOne->GetPosition().GetDistance(gameObjectTwo->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectOne, gameObjectTwo, oneTwoDistance));
	float oneThreeDistance = gameObjectOne->GetPosition().GetDistance(gameObjectThree->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectOne, gameObjectThree, oneThreeDistance));
	float oneFourDistance = gameObjectOne->GetPosition().GetDistance(gameObjectFour->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectOne, gameObjectFour, oneFourDistance));
	float twoThreeDistance = gameObjectTwo->GetPosition().GetDistance(gameObjectThree->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectTwo, gameObjectThree, twoThreeDistance));
	float twoFourDistance = gameObjectTwo->GetPosition().GetDistance(gameObjectFour->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectTwo, gameObjectFour, twoFourDistance));
	float threeFourDistance = gameObjectThree->GetPosition().GetDistance(gameObjectFour->GetPosition());
	mp_ContactGenerators.push_back(new RodContactGenerator(gameObjectThree, gameObjectFour, threeFourDistance));
}
//=============================================================================