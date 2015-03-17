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
#include "GameObject.h"
//=============================================================================
class Particle :
	public GameObject
{
private:
	float m_ActiveTime;

public:
	Particle();
	~Particle();

	virtual void Initialize(float activeTime, float radius, Vector3D initialPosition, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initialRotation = Vector3D::Zero);
	virtual void Update(float deltaTime);
	bool GetIsActive();
};
//=============================================================================
#endif // PARTICLE_H

