//=============================================================================
//                              Tetrahedron Collectible
//
// Written by Evan Schipellite
//=============================================================================
#include "TetrahedronCollectible.h"
#include "RodContactGenerator.h"
//=============================================================================
TetrahedronCollectible::TetrahedronCollectible()
{
}

//-----------------------------------------------------------------------------
TetrahedronCollectible::~TetrahedronCollectible()
{
}

//-----------------------------------------------------------------------------
void TetrahedronCollectible::Initialize(Vector3D centerPosition, std::string texture, float size, float mass)
{
	float halfSize = size * 0.5f;

	//Bot-Top
	GameObject* gameObjectOne = new GameObject();
	Vector3D positionOne = Vector3D(centerPosition.X, centerPosition.Y - halfSize, centerPosition.Z + halfSize);
	gameObjectOne->Initialize(positionOne, texture, mass);
	mp_GameObjects.push_back(gameObjectOne);

	//Bot-Left
	GameObject* gameObjectTwo = new GameObject();
	Vector3D positionTwo = Vector3D(centerPosition.X - halfSize, centerPosition.Y - halfSize, centerPosition.Z - halfSize);
	gameObjectTwo->Initialize(positionTwo, texture, mass);
	mp_GameObjects.push_back(gameObjectTwo);

	//Bot-Right
	GameObject* gameObjectThree = new GameObject();
	Vector3D positionThree = Vector3D(centerPosition.X + halfSize, centerPosition.Y - halfSize, centerPosition.Z - halfSize);
	gameObjectThree->Initialize(positionThree, texture, mass);
	mp_GameObjects.push_back(gameObjectThree);

	//Top
	GameObject* gameObjectFour = new GameObject();
	Vector3D positionFour = Vector3D(centerPosition.X, centerPosition.Y + halfSize, centerPosition.Z);
	gameObjectFour->Initialize(positionFour, texture, mass);
	mp_GameObjects.push_back(gameObjectFour);

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
}
//=============================================================================