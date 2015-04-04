//=============================================================================
//                              Ground
//
// Written by Evan Schipellite
//
// Physics Object representing the game surface
//=============================================================================
#ifndef GROUND_H
#define GROUND_H
//=============================================================================
#include "GameObject.h"
#include <iostream>
//=============================================================================
class Ground :
	public GameObject
{
private:
	Vector3D m_Dimensions;

public:
	Ground();
	~Ground();

	void Initialize(Vector3D dimensions, float mass, Vector3D initialPosition, std::string texture);
	void Draw();
};
//=============================================================================
#endif // GROUND_H

