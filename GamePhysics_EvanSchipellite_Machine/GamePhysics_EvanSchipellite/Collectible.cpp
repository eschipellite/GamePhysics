//=============================================================================
//                              Collectible
//
// Written by Evan Schipellite
//=============================================================================
#include "Collectible.h"
#include "GameObject.h"
//=============================================================================
Collectible::Collectible()
{
}

//-----------------------------------------------------------------------------
Collectible::~Collectible()
{
}

//-----------------------------------------------------------------------------
void Collectible::createContactGenerators()
{

}

//-----------------------------------------------------------------------------
void Collectible::Initialize(Vector3D initialPosition, std::string textureID, float mass)
{
	GameObject* gameObject = new GameObject();
	gameObject->Initialize(initialPosition, textureID, mass);
	mp_GameObjects.push_back(gameObject);
}

//-----------------------------------------------------------------------------
void Collectible::CleanUp()
{
	std::vector<GameObject*>::iterator gameObjectIter;
	for (gameObjectIter = mp_GameObjects.begin(); gameObjectIter != mp_GameObjects.end(); gameObjectIter++)
	{
		(*gameObjectIter)->CleanUp();
		delete (*gameObjectIter);
		(*gameObjectIter) = nullptr;
	}
	mp_GameObjects.clear();
}

//-----------------------------------------------------------------------------
void Collectible::Reset()
{
	std::vector<GameObject*>::iterator gameObjectIter;
	for (gameObjectIter = mp_GameObjects.begin(); gameObjectIter != mp_GameObjects.end(); gameObjectIter++)
	{
		(*gameObjectIter)->Reset();
	}

	m_Attached = false;

	mp_ContactGenerators.clear();

	createContactGenerators();
}

//-----------------------------------------------------------------------------
void Collectible::Update(float deltaTime)
{
	std::vector<GameObject*>::iterator gameObjectIter;
	for (gameObjectIter = mp_GameObjects.begin(); gameObjectIter != mp_GameObjects.end(); gameObjectIter++)
	{
		(*gameObjectIter)->Update(deltaTime);
	}
}

//-----------------------------------------------------------------------------
void Collectible::Draw()
{
	std::vector<GameObject*>::iterator gameObjectIter;
	for (gameObjectIter = mp_GameObjects.begin(); gameObjectIter != mp_GameObjects.end(); gameObjectIter++)
	{
		(*gameObjectIter)->Draw();
	}
}
//=============================================================================