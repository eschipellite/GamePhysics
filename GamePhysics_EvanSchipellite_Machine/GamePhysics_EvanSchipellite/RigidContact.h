//=============================================================================
//                              Rigid Contact
//
// Written by Evan Schipellite
//
// Basis from: https://github.com/idmillington/cyclone-physics
//=============================================================================
#ifndef RIGID_CONTACT_H
#define RIGID_CONTACT_H
//=============================================================================
#include "Vector3D.h"
#include "RigidBody.h"
//=============================================================================
class RigidContact
{
private:
	RigidBody* mp_RigidBodyOne;
	RigidBody* mp_RigidBodyTwo;

	Vector3D m_ContactPoint;
	Vector3D m_ContactNormal;
	Vector3D m_ContactVelocity;

	float m_Penetration;
	float m_Restitution;
	float m_Friction;
	float m_DesiredDeltaVelocity;

	Matrix m_ContactToWorld;

	Vector3D m_RelativeContactPositionOne;
	Vector3D m_RelativeContactPositionTwo;

private:
	void calculateContactBasis();
	Vector3D calculateLocalVelocity(unsigned int rigidBodyIndex, float deltaTime);
	Vector3D calculateFrictionlessImpulse(Matrix* inverseInertiaTensor);
	Vector3D calculateFrictionImpulse(Matrix* inverseInertiaTensor);

public:
	RigidContact();
	~RigidContact();

	void Initialize(RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo, Vector3D contactPoint, Vector3D contactNormal, float penetration, float restitution, float friction);

	void CalculateInternals(float deltaTime);
	void CalculateDesiredDeltavelocity(float deltaTime);

	void MatchAwakeState();

	void ApplyPositionChange(Vector3D linearChange[2], Vector3D angularChange[2], float penetration);
	void ApplyVelocityChange(Vector3D velocityChange[2], Vector3D rotationChange[2]);

	void SetPenetration(float penetration) { m_Penetration = penetration; };
	float GetPenetration() { return m_Penetration; };

	Vector3D GetContactNormal() { return m_ContactNormal; };
	RigidBody* GetRigidBody(int index);
	Vector3D GetRelativeContactPosition(int index);

	float GetDesiredDeltaVelocity() { return m_DesiredDeltaVelocity; };

	void SetContactVelocity(Vector3D contactVelocity) { m_ContactVelocity = contactVelocity; };
	Vector3D GetContactVelocity() { return m_ContactVelocity; };
	Matrix GetContactToWorld() { return m_ContactToWorld; };
};
//=============================================================================
#endif // RIGID_CONTACT_H

