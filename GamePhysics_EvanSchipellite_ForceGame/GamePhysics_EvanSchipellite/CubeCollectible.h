//=============================================================================
//                              Cube Collectible
//
// Written by Evan Schipellite
//=============================================================================
#ifndef CUBE_COLLECTIBLE_H
#define CUBE_COLLECTIBLE_H
//=============================================================================
#include "Collectible.h"
//=============================================================================
class CubeCollectible :
	public Collectible
{
public:
	CubeCollectible();
	~CubeCollectible();

	void Initialize(Vector3D centerPosition, std::string texture, float size = 1, float mass = 1);
};
//=============================================================================
#endif // CUBE_COLLECTIBLE_H