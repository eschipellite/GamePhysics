//=============================================================================
//                              PhysicsObject
//
// Written by Evan Schipellite
//
// Class for applying physics to game objects
//=============================================================================
#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
//=============================================================================
#include "Vector3D.h"
#include <GL\glut.h>
//=============================================================================
class PhysicsObject
{
protected:
	Vector3D m_CurrentPosition;
	Vector3D m_CurrentVelocity;
	Vector3D m_CurrentAcceleration;
	Vector3D m_CurrentRotation;

	Vector3D m_InitialPosition;
	Vector3D m_InitialVelocity;
	Vector3D m_InitialAcceleration;
	Vector3D m_InitialRotation;

	float m_Radius;
	float m_InverseMass;

	Vector3D m_TotalForce;

	float m_Dampening;

protected:
	void updateForces(float deltaTime);

public:
	PhysicsObject();
	~PhysicsObject();

	virtual void Initialize(float radius, float mass, Vector3D initialPosition, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initialRotation = Vector3D::Zero, float dampening = 1);
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void Reset();
	virtual void CleanUp();

	void SetPosition(Vector3D position);
	void SetVelocity(Vector3D velocity);
	void SetAcceleration(Vector3D acceleration);
	void SetRotation(Vector3D rotation);
	void SetRadius(float radius);
	void SetInverseMass(float mass);

	void AddForce(const Vector3D force);

	Vector3D GetPosition();
	float GetMass();
};
//=============================================================================
#endif // PHYSICSOBJECT_H
