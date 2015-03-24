//=============================================================================
//                              Collectible
//
// Written by Evan Schipellite
//=============================================================================
#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H
//=============================================================================
#include "GameObject.h"
#include <vector>

class ContactGenerator;
//=============================================================================
class Collectible
{
protected:
	std::vector<GameObject*> mp_GameObjects;
	std::vector<ContactGenerator*> mp_ContactGenerators;

public:
	Collectible();
	~Collectible();

	void Initialize(Vector3D initialPosition, std::string texture, float mass = 1);
	void CleanUp();
	void Reset();

	void Update(float deltaTime);
	void Draw();

	inline std::vector<GameObject*> GetGameObjects() { return mp_GameObjects; };
	inline std::vector<ContactGenerator*> GetContactGenerators() { return mp_ContactGenerators; };
};
//=============================================================================
#endif // COLLECTIBLE_H

