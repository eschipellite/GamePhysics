//=============================================================================
//                              RigidBody Spring Force Generator
//
// Written by Evan Schipellite
//
// Allows for spring force resolution between physics objects
//=============================================================================
#include "RigidBodySpringForceGenerator.h"
#include <math.h>
//=============================================================================
RigidBodySpringForceGenerator::RigidBodySpringForceGenerator(const Vector3D &localConnectionPoint, RigidBody* anchorObject, const Vector3D &otherConnectionPoint, float springConstant, float restLength)
{
	m_ConnectionPoint = localConnectionPoint;
	m_AnchorRigidBody = anchorObject;
	m_OtherConnectionPoint = otherConnectionPoint;
	m_SpringConstant = springConstant;
	m_RestLength = restLength;
}

//-----------------------------------------------------------------------------
RigidBodySpringForceGenerator::~RigidBodySpringForceGenerator()
{
}

//-----------------------------------------------------------------------------
void RigidBodySpringForceGenerator::UpdateForce(RigidBody *rigidBodyOne, RigidBody *rigidBodyTwo)
{
	Vector3D lws = rigidBodyOne->GetPointInWorldSpace(m_ConnectionPoint);
	Vector3D ows = m_AnchorRigidBody->GetPointInWorldSpace(m_OtherConnectionPoint);

	Vector3D force = lws - ows;

	float magnitude = force.Magnitude();
	magnitude = abs(magnitude - m_RestLength);
	magnitude *= m_SpringConstant;

	force.Normalize();
	force *= -magnitude;
	rigidBodyOne->AddForceAtPoint(force, lws);
}
//=============================================================================