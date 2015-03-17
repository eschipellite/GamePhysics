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

	Vector3D m_ContactNormal;

private:
	void resolve(float deltaTime);
	void resolveVelocity(float deltaTime);
	float calculateSeparatingVelocity();

public:
	Contact();
	~Contact();
};
//=============================================================================
#endif // CONTACT_H