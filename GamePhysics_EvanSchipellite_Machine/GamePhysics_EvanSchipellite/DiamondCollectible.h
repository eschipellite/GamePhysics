//=============================================================================
//                              Diamond Collectible
//
// Written by Evan Schipellite
//=============================================================================
#ifndef DIAMOND_COLLECTIBLE_H
#define DIAMOND_COLLECTIBLE_H
//=============================================================================
#include "Collectible.h"
//=============================================================================
class DiamondCollectible :
	public Collectible
{
protected:
	void createContactGenerators();

public:
	DiamondCollectible();
	~DiamondCollectible();

	void Initialize(Vector3D centerPosition, std::string texture, float size = 1, float mass = 1);
};
//=============================================================================
#endif // DIAMOND_COLLECTIBLE_H