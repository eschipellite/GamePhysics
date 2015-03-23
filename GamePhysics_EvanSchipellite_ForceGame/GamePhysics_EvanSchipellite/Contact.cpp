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
Contact::Contact(float restitution, float penetration, Vector3D contactNormal, PhysicsObject* contactOne, PhysicsObject* contactTwo)
{
	m_Restitution = restitution;
	m_Penetration = penetration;
	m_ContactNormal = contactNormal;

	mp_ContactOne = contactOne;
	mp_ContactTwo = contactTwo;
}

//-----------------------------------------------------------------------------
Contact::~Contact()
{
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

	Vector3D acceleration = mp_ContactOne->GetCurrentAcceleration();
	if (mp_ContactTwo)
	{
		acceleration -= mp_ContactTwo->GetCurrentAcceleration();
	}

	float velocity = acceleration.Dot(m_ContactNormal) * deltaTime;
	if (velocity < 0)
	{
		separatingVelocity -= velocity;
	}

	float deltaVelocity = newSeparatingVelocity - separatingVelocity;

	float totalInverseMass = mp_ContactOne->GetInverseMass();
	if (mp_ContactTwo)
	{
		totalInverseMass += mp_ContactTwo->GetInverseMass();
	}

	if (totalInverseMass <= 0)
	{
		return;
	}

	float impulse = deltaVelocity / totalInverseMass;
	Vector3D impulsePerIMass = m_ContactNormal * impulse;

	mp_ContactOne->SetVelocity(mp_ContactOne->GetCurrentVelocity() + impulsePerIMass * mp_ContactOne->GetInverseMass());
	if (mp_ContactTwo)
	{
		mp_ContactTwo->SetVelocity(mp_ContactTwo->GetCurrentVelocity() + impulsePerIMass * -mp_ContactTwo->GetInverseMass());
	}
}

//-----------------------------------------------------------------------------
void Contact::resolveInterpenetration(float deltaTime)
{
	if (m_Penetration <= 0)
	{
		return;
	}

	float totalInverseMass = mp_ContactOne->GetInverseMass();
	if (mp_ContactTwo)
	{
		totalInverseMass += mp_ContactTwo->GetInverseMass();
	}

	if (totalInverseMass <= 0)
	{
		return;
	}

	Vector3D movementPerInverseMass = m_ContactNormal  * (m_Penetration / totalInverseMass);

	Vector3D contactOneMovement = movementPerInverseMass * mp_ContactOne->GetInverseMass();
	mp_ContactOne->SetPosition(mp_ContactOne->GetPosition() + contactOneMovement);
	if (mp_ContactTwo)
	{
		Vector3D contactTwoMovement = movementPerInverseMass * -mp_ContactTwo->GetInverseMass();
		mp_ContactTwo->SetPosition(mp_ContactTwo->GetPosition() + contactTwoMovement);
	}
}

//-----------------------------------------------------------------------------
float Contact::calculateSeparatingVelocity()
{
	Vector3D relativeVelocity = mp_ContactOne->GetCurrentVelocity();
	if (mp_ContactTwo)
	{
		relativeVelocity -= mp_ContactTwo->GetCurrentVelocity();
	}

	return relativeVelocity.Dot(m_ContactNormal);
}

//-----------------------------------------------------------------------------
void Contact::Resolve(float deltaTime)
{
	resolveVelocity(deltaTime);
	resolveInterpenetration(deltaTime);
}
//=============================================================================