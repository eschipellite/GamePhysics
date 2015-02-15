//=============================================================================
//                              PhysicsObject
//
// Written by Evan Schipellite
//
// Class for applying physics to game objects
//=============================================================================
#include "PhysicsObject.h"
#include <GL\glut.h>
//=============================================================================
PhysicsObject::PhysicsObject()
{
	m_CurrentPosition = Vector3D::Zero;
	m_CurrentVelocity = Vector3D::Zero;
	m_CurrentAcceleration = Vector3D::Zero;
	m_CurrentRotation = Vector3D::Zero;

	m_InitialPosition = Vector3D::Zero;
	m_InitialVelocity = Vector3D::Zero;
	m_InitialAcceleration = Vector3D::Zero;
	m_InitialRotation = Vector3D::Zero;

	m_TotalForce = Vector3D::Zero;
	m_PreviousTotalForce = Vector3D::Zero;

	m_Radius = 1;

	m_Dampening = 1;
}

//-----------------------------------------------------------------------------
PhysicsObject::~PhysicsObject()
{
}

//-----------------------------------------------------------------------------
void PhysicsObject::Initialize(float radius, float mass, Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initialRotation, float dampening)
{
	m_CurrentPosition = initialPosition;
	m_CurrentVelocity = initialVelocity;
	m_CurrentAcceleration = initialAcceleration;
	m_CurrentRotation = initialRotation;

	m_InitialPosition = initialPosition;
	m_InitialVelocity = initialVelocity;
	m_InitialAcceleration = initialAcceleration;
	m_InitialRotation = initialRotation;

	m_Radius = radius;

	m_Dampening = dampening;

	SetInverseMass(mass);

	m_Quad = gluNewQuadric();
}

//-----------------------------------------------------------------------------
void PhysicsObject::Update(float deltaTime)
{
	updateForces(deltaTime);
}

//-----------------------------------------------------------------------------
void PhysicsObject::Draw()
{
	glPushMatrix();
	glTranslatef(m_CurrentPosition.X, m_CurrentPosition.Y, m_CurrentPosition.Z);
	gluSphere(m_Quad, m_Radius, 100, 100);
	glPopMatrix();
}

//-----------------------------------------------------------------------------
void PhysicsObject::Reset()
{
	m_CurrentPosition = m_InitialPosition;
	m_CurrentVelocity = m_InitialVelocity;
	m_CurrentAcceleration = m_InitialAcceleration;
}

//-----------------------------------------------------------------------------
void PhysicsObject::CleanUp()
{
}

//-----------------------------------------------------------------------------
void PhysicsObject::updateForces(float deltaTime)
{
	deltaTime *= 86400; // Seconds per day

	m_CurrentPosition += (m_CurrentVelocity * deltaTime);
	m_CurrentAcceleration = (m_TotalForce * m_InverseMass);
	m_CurrentVelocity += (m_CurrentAcceleration * deltaTime);

	m_CurrentVelocity *= m_Dampening;

	m_PreviousTotalForce = m_TotalForce;

	m_TotalForce = Vector3D::Zero;
}

//-----------------------------------------------------------------------------
void PhysicsObject::SetPosition(Vector3D position)
{
	m_CurrentPosition = position;
}

//-----------------------------------------------------------------------------
void PhysicsObject::SetVelocity (Vector3D velocity)
{
	m_CurrentVelocity = velocity;
}

//-----------------------------------------------------------------------------
void PhysicsObject::SetAcceleration(Vector3D acceleration)
{
	m_CurrentAcceleration = acceleration;
}

//-----------------------------------------------------------------------------
void PhysicsObject::SetRotation(Vector3D rotation)
{
	m_CurrentRotation = rotation;
}

//-----------------------------------------------------------------------------
void PhysicsObject::SetRadius(float radius)
{
	m_Radius = radius;
}

//-----------------------------------------------------------------------------
void PhysicsObject::SetInverseMass(float mass)
{
	if (mass == 0)
	{
		m_InverseMass = 1;
	}
	else
	{
		m_InverseMass = 1.0f / mass;
	}
}

//-----------------------------------------------------------------------------
void PhysicsObject::AddForce(const Vector3D force)
{
	m_TotalForce += force;
}

//-----------------------------------------------------------------------------
Vector3D PhysicsObject::GetPosition()
{
	return m_CurrentPosition;
}

//-----------------------------------------------------------------------------
float PhysicsObject::GetMass()
{
	return 1.0f / m_InverseMass;
}

//-----------------------------------------------------------------------------
Vector3D PhysicsObject::GetCurrentVelocity()
{
	return m_CurrentVelocity;
}

//-----------------------------------------------------------------------------
Vector3D PhysicsObject::GetCurrentAcceleration()
{
	return m_CurrentAcceleration;
}

//-----------------------------------------------------------------------------
Vector3D PhysicsObject::GetPreviousTotalForce()
{
	return m_PreviousTotalForce;
}
//=============================================================================
