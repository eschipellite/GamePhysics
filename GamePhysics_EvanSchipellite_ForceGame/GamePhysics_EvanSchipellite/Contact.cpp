//=============================================================================
//                              Contact
//
// Written by Evan Schipellite
//
// Stores and resolves collisions
//=============================================================================
#include "Contact.h"
#include "PhysicsObject.h"
//=============================================================================
Contact::Contact()
{
}

//-----------------------------------------------------------------------------
Contact::~Contact()
{
}

//-----------------------------------------------------------------------------
void Contact::resolve(float deltaTime)
{
	resolveVelocity(deltaTime);
	//resolveInterpenetration(deltaTime);
}

//-----------------------------------------------------------------------------
void Contact::resolveVelocity(float deltaTime)
{
	float separatingVelocity = calculateSeparatingVelocity();

	if (separatingVelocity > 0)
	{
		return;
	}

	float newSeparatingVelocity = -separatingVelocity * m_Restitution;
	float deltaVelocity = newSeparatingVelocity - separatingVelocity;

	float totalInverseMass = mp_ContactOne->GetInverseMass();
	totalInverseMass += mp_ContactTwo->GetInverseMass();

	if (totalInverseMass <= 0)
	{
		return;
	}

	float impulse = deltaVelocity / totalInverseMass;
	Vector3D impulsePerIMass = m_ContactNormal * impulse;

	mp_ContactOne->SetVelocity(mp_ContactOne->GetCurrentVelocity() + impulsePerIMass * mp_ContactOne->GetInverseMass());
	mp_ContactTwo->SetVelocity(mp_ContactTwo->GetCurrentVelocity() + impulsePerIMass * -mp_ContactTwo->GetInverseMass());
}

//-----------------------------------------------------------------------------
float Contact::calculateSeparatingVelocity()
{
	Vector3D relativeVelocity = mp_ContactOne->GetCurrentVelocity();
	relativeVelocity -= mp_ContactTwo->GetCurrentVelocity();

	return relativeVelocity.Dot(m_ContactNormal);
}
//=============================================================================