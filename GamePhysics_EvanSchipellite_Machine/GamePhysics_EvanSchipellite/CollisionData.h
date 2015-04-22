//=============================================================================
//                              Collision Data
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef COLLISION_DATA_H
#define COLLISION_DATA_H
//=============================================================================
#include "RigidContact.h"
//=============================================================================
class CollisionData
{
private:
	RigidContact* mp_RigidContact;

	int m_ContactsLeft;

	float m_Restitution;
	float m_Friction;

public:
	CollisionData();
	~CollisionData();

	inline void AddContacts(int contacts) { m_ContactsLeft += contacts; };

	inline RigidContact* GetRigidContact() { return mp_RigidContact; };
	inline int GetContactsLeft() { return m_ContactsLeft; };

	inline float GetRestitution() { return m_Restitution; };
	inline float GetFriction() { return m_Friction; };
};
//=============================================================================
#endif COLLISION_DATA_H // COLLISION_DATA_H

