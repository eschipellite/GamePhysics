//=============================================================================
//                              Earth Gravity Generator
//
// Written by Evan Schipellite
//
// Applies constant acceleration force due to Earth gravity
//=============================================================================
#ifndef EARTH_GRAVITY_GENERATOR_H
#define EARTH_GRAVITY_GENERATOR_H
//=============================================================================
#include "ForceGenerator.h"

class Vector3D;
//=============================================================================
class EarthGravityGenerator :
	public ForceGenerator
{
private:
	Vector3D m_Gravity;
public:
	EarthGravityGenerator(const Vector3D &gravity);
	~EarthGravityGenerator();

	void UpdateForce(PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo = NULL);
};
//=============================================================================
#endif // EARTH_GRAVITY_GENERATOR_H
