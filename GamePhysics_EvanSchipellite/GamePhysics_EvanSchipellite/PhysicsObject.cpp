//=============================================================================
//                              PhysicsObject
//
// Written by Evan Schipellite
//
// Class for applying physics to game objects
//=============================================================================
#include "PhysicsObject.h"
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

	m_CurrentSize = 1;
}

//-----------------------------------------------------------------------------
PhysicsObject::~PhysicsObject()
{
}

//-----------------------------------------------------------------------------
void PhysicsObject::Initialize(float size, Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initialRotation)
{
	m_CurrentPosition = initialPosition;
	m_CurrentVelocity = initialVelocity;
	m_CurrentAcceleration = initialAcceleration;
	m_CurrentRotation = initialRotation;

	m_InitialPosition = initialPosition;
	m_InitialVelocity = initialVelocity;
	m_InitialAcceleration = initialAcceleration;
	m_InitialRotation = initialRotation;

	m_CurrentSize = size;
}

//-----------------------------------------------------------------------------
void PhysicsObject::Update(int deltaTime)
{
	m_CurrentPosition += m_CurrentVelocity;
	m_CurrentVelocity += m_CurrentAcceleration;
}

//-----------------------------------------------------------------------------
void PhysicsObject::Draw()
{
	glPushMatrix();
	glTranslatef(m_CurrentPosition.X, m_CurrentPosition.Y, m_CurrentPosition.Z);
	glutSolidSphere(m_CurrentSize, 100, 100);
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
void PhysicsObject::SetSize(float size)
{
	m_CurrentSize = size;
}

//-----------------------------------------------------------------------------
Vector3D PhysicsObject::GetPosition()
{
	return m_CurrentPosition;
}
//=============================================================================
