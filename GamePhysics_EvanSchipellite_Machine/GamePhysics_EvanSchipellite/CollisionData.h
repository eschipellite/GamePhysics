//=============================================================================
//                              Collision Data
//
// Written by Evan Schipellite
//
// Basis from: https://github.com/idmillington/cyclone-physics
//=============================================================================
#ifndef COLLISION_DATA_H
#define COLLISION_DATA_H
//=============================================================================
#include "RigidContact.h"
#include <vector>
//=============================================================================
class CollisionData
{
private:
	std::vector<RigidContact*> mp_RigidContacts;

	int m_ContactsLeft;

	float m_Restitution;
	float m_Friction;

public:
	CollisionData();
	~CollisionData();

	inline void AddContacts(int contacts) { m_ContactsLeft += contacts; };

	inline std::vector<RigidContact*> GetRigidContacts() { return mp_RigidContacts; };
	inline int GetContactsLeft() { return m_ContactsLeft; };

	inline float GetRestitution() { return m_Restitution; };
	inline float GetFriction() { return m_Friction; };
};
//=============================================================================
#endif COLLISION_DATA_H // COLLISION_DATA_H

