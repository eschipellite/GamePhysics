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

	bool m_Attached;

protected:
	virtual void createContactGenerators();

public:
	Collectible();
	~Collectible();

	void Initialize(Vector3D initialPosition, std::string textureID, float mass = 1);
	void CleanUp();
	void Reset();

	void Update(float deltaTime);
	void Draw();

	inline std::vector<GameObject*> GetGameObjects() { return mp_GameObjects; };
	inline std::vector<ContactGenerator*> GetContactGenerators() { return mp_ContactGenerators; };

	inline void ToggleAttached(bool attached) { m_Attached = attached; };
	inline bool GetAttached() { return m_Attached;; }
};
//=============================================================================
#endif // COLLECTIBLE_H

