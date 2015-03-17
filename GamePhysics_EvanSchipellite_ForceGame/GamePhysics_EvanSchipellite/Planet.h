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
#include "GameObject.h"
#include <iostream>
//=============================================================================
class Planet :
	public GameObject
{
private:
	std::string m_PlanetName;

public:
	Planet();
	~Planet();

	void Initialize(float radius, float mass, Vector3D initialPosition, Vector3D initialVelocity, std::string planeName, std::string texture);
	void Update(float deltaTime);

	void Draw();

	inline std::string GetPlanetName() { return m_PlanetName; };
};
//=============================================================================
#endif //PLANET_H

