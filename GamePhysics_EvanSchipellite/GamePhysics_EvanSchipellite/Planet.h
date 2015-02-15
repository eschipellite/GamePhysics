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
#include <SOIL.h>
//=============================================================================
class Planet :
	public PhysicsObject
{
private:
	std::string m_PlanetName;
	GLuint m_Texture;

private:
	void loadTexture(std::string texture);

public:
	Planet();
	~Planet();

	void Initialize(float radius, float mass, Vector3D initialPosition, Vector3D initialVelocity, std::string planeName, std::string texture);

	void Draw();

	inline std::string GetPlanetName() { return m_PlanetName; };
};
//=============================================================================
#endif //PLANET_H

