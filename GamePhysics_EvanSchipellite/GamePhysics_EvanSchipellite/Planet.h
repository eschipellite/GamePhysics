//=============================================================================
//                              Planet
//
// Written by Evan Schipellite
//
// Base class for planets
//=============================================================================
#ifndef PLANET_H
#define PLANET_H
//=============================================================================
#include "PhysicsObject.h"
#include <iostream>
//=============================================================================
class Planet :
	public PhysicsObject
{
private:
	std::string m_PlanetName;
public:
	Planet();
	~Planet();

	void Initialize(float radius, float mass, Vector3D initialPosition, Vector3D initialVelocity, std::string planeName);
};
//=============================================================================
#endif //PLANET_H

