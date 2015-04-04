//=============================================================================
//                              Tetrahedron Collectible
//
// Written by Evan Schipellite
//=============================================================================
#ifndef TETRAHEDRON_COLLECTIBLE_H
#define TETRAHEDRON_COLLECTIBLE_H
//=============================================================================
#include "Collectible.h"
//=============================================================================
class TetrahedronCollectible :
	public Collectible
{
protected:
	void createContactGenerators();

public:
	TetrahedronCollectible();
	~TetrahedronCollectible();

	void Initialize(Vector3D centerPosition, std::string texture, float size = 1, float mass = 1);
};
//=============================================================================
#endif // TETRAHEDRON_COLLECTIBLE_H