//=============================================================================
//                              RigidBody Spring Force Generator
//
// Written by Evan Schipellite
//
// Allows for spring force resolution between physics objects
//=============================================================================
#ifndef RIGIDBODY_SPRING_FORCE_GENERATOR_H
#define RIGIDBODY_SPRING_FORCE_GENERATOR_H
//=============================================================================
#include "ForceGenerator.h"
//=============================================================================
class RigidBodySpringForceGenerator :
	public ForceGenerator
{
private:
	Vector3D m_ConnectionPoint;
	Vector3D m_OtherConnectionPoint;

	RigidBody* m_AnchorRigidBody;

	float m_SpringConstant;
	float m_RestLength;

public:
	RigidBodySpringForceGenerator(const Vector3D &localConnectionPoint, RigidBody* anchorObject, const Vector3D &otherConnectionPoint, float springConstant, float restLength);
	~RigidBodySpringForceGenerator();

	void UpdateForce(RigidBody *rigidBodyOne, RigidBody *rigidBodyTwo = NULL);
};
//=============================================================================
#endif // RIGIDBODY_SPRING_FORCE_GENERATOR_H