//=============================================================================
//                              Contact
//
// Written by Evan Schipellite
//
// Stores and resolves collisions
//=============================================================================
#ifndef CONTACT_H
#define CONTACT_H
//=============================================================================
#include "Vector3D.h"

class PhysicsObject;
//=============================================================================
class Contact
{
private:
	PhysicsObject* mp_ContactOne;
	PhysicsObject* mp_ContactTwo;

	float m_Restitution;
	float m_Penetration;

	Vector3D m_ContactNormal;

private:
	void resolveVelocity(float deltaTime);
	void resolveInterpenetration(float deltaTime);
	float calculateSeparatingVelocity();

public:
	Contact(float restitution, float penetration, Vector3D contactNormal, PhysicsObject* contactOne, PhysicsObject* contactTwo = nullptr);
	~Contact();

	void Resolve(float deltaTime);
};
//=============================================================================
#endif // CONTACT_H