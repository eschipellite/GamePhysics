//=============================================================================
//                              Firework
//
// Written by Evan Schipellite
//
// A Firework particle in charge of detonating and launching further Fireworks
//=============================================================================
#ifndef FIREWORK_H
#define FIREWORK_H
//=============================================================================
#include "Particle.h"
//=============================================================================
class Firework :
	public Particle
{
private:
	bool m_ShouldExplode;
	int m_CurrentLevel;
public:
	Firework();
	~Firework();

	virtual void Initialize(bool shouldExplode, int currentLevel, float activeTime, float radius, Vector3D initialPosition, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initialRotation = Vector3D::Zero);

	bool GetShouldExplode();
	int GetCurrentLevel();
};
//=============================================================================
#endif // FIREWORK_H

