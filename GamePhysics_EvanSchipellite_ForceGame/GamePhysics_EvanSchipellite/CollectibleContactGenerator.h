//=============================================================================
//                              Collectible Contact Generator
//
// Written by Evan Schipellite
//
// Detects Collectible Collisions with Player
//=============================================================================
#ifndef COLLECTIBLE_CONTACT_GENERATOR_H
#define COLLECTIBLE_CONTACT_GENERATOR_H
//=============================================================================
#include "ContactGenerator.h"
#include "Player.h"
#include "Collectible.h"
//=============================================================================
class CollectibleContactGenerator :
	public ContactGenerator
{
private:
	Player* mp_Player;
	Collectible* mp_Collectible;

	float m_MinDistance;
public:
	CollectibleContactGenerator(Player* player, Collectible* collectible, float minDistance);
	~CollectibleContactGenerator();

	void AddContact(CollisionHandler* collisionHandler);
};
//=============================================================================
#endif // COLLECTIBLE_CONTACT_GENERATOR_H