//=============================================================================
//                              Collectible
//
// Written by Evan Schipellite
//=============================================================================
#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H
//=============================================================================
#include "GameObject.h"
//=============================================================================
class Collectible :
	public GameObject
{
public:
	Collectible();
	~Collectible();

	void Initialize(Vector3D initialPosition, std::string texture);
	void Draw();
};
//=============================================================================
#endif // COLLECTIBLE_H

