//=============================================================================
//                              Particle
//
// Written by Evan Schipellite
//
// Contains all information to be shared by particles
//=============================================================================
#ifndef PARTCILE_H
#define PARTCILE_H
//=============================================================================
#include "PhysicsObject.h"
//=============================================================================
class Particle :
	public PhysicsObject
{
private:
	int m_ActiveTime;

public:
	Particle();
	~Particle();

	virtual void Initialize(int activeTime, float size, Vector3D initialPosition, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initialRotation = Vector3D::Zero);
	virtual void Update(int deltaTime);
	bool GetIsActive();
};
//=============================================================================
#endif // PARTICLE_H

