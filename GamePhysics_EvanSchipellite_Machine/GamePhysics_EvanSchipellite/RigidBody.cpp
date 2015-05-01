//=============================================================================
//                              RigidBody
//
// Written by Evan Schipellite
//=============================================================================
#include "RigidBody.h"
#include <math.h>
#include <iostream>
//=============================================================================
RigidBody::RigidBody()
{
	m_TransformationMatrix = Matrix44f();
	m_InverseInertiaTensor = Matrix33f();
	m_InverseInertiaTensorWorld = Matrix33f();
	m_CollisionType = CollisionType::SPHERE;
}

//-----------------------------------------------------------------------------
RigidBody::~RigidBody()
{
}

//-----------------------------------------------------------------------------
void RigidBody::CalculateDerivedData()
{
	m_Orientation.Normalize();

	calculateTransformMatrix(m_TransformationMatrix, m_Position, m_Orientation);

	transformInertiaTensor(m_InverseInertiaTensorWorld, m_Orientation, m_InverseInertiaTensor, m_TransformationMatrix);
}

//-----------------------------------------------------------------------------
void RigidBody::calculateTransformMatrix(Matrix44f &transformMatrix, const Vector3D &position, const Quaternion &orientation)
{
	float val1 = 1 - 2 * orientation.J * orientation.J - 2 * orientation.K * orientation.K;
	transformMatrix[0] = val1;
	float val2 = 2 * orientation.I * orientation.J - 2 * orientation.R * orientation.K;
	transformMatrix[1] = val2;
	float val3 = 2 * orientation.I * orientation.K + 2 * orientation.R * orientation.J;
	transformMatrix[2]= val3;
	float val4 = position.X;
	transformMatrix[3]  =val4;

	float val5 = 2 * orientation.I * orientation.J + 2 * orientation.R * orientation.K;
	transformMatrix[4] = val5;
	float val6 = 1 - 2 * orientation.I * orientation.I - 2 * orientation.K * orientation.K;
	transformMatrix[5] = val6;
	float val7 = 2 * orientation.J * orientation.K - 2 * orientation.R * orientation.I;
	transformMatrix[6] = val7;
	float val8 = position.Y;
	transformMatrix[7] = val8;

	float val9 = 2 * orientation.I * orientation.K - 2 * orientation.R * orientation.J;
	transformMatrix[8] = val9;
	float val10 = 2 * orientation.J * orientation.K + 2 * orientation.R * orientation.I;
	transformMatrix[9] = val10;
	float val11 = 1 - 2 * orientation.I * orientation.I - 2 * orientation.J * orientation.J;
	transformMatrix[10] = val11;
	float val12 = position.Z;
	transformMatrix[11] = val12;
}

//-----------------------------------------------------------------------------
void RigidBody::transformInertiaTensor(Matrix33f &iitWorld, const Quaternion &quaternion, const Matrix33f &iitBody, const Matrix44f &rotationMatrix)
{
	float t4 = rotationMatrix[0] * iitBody[0] + rotationMatrix[1] * iitBody[3] + rotationMatrix[2] * iitBody[6];
	float t9 = rotationMatrix[0] * iitBody[1] + rotationMatrix[1] * iitBody[4] + rotationMatrix[2] * iitBody[7];
	float t14 = rotationMatrix[0] * iitBody[2] + rotationMatrix[1] * iitBody[5] + rotationMatrix[2] * iitBody[8];
	float t28 = rotationMatrix[4] * iitBody[0] + rotationMatrix[5] * iitBody[3] + rotationMatrix[6] * iitBody[6];
	float t33 = rotationMatrix[4] * iitBody[1] + rotationMatrix[5] * iitBody[4] + rotationMatrix[6] * iitBody[7];
	float t38 = rotationMatrix[4] * iitBody[2] + rotationMatrix[5] * iitBody[5] + rotationMatrix[6] * iitBody[8];
	float t52 = rotationMatrix[8] * iitBody[0] + rotationMatrix[9] * iitBody[3] + rotationMatrix[10] * iitBody[6];
	float t57 = rotationMatrix[8] * iitBody[1] + rotationMatrix[9] * iitBody[4] + rotationMatrix[10] * iitBody[7];
	float t62 = rotationMatrix[8] * iitBody[2] + rotationMatrix[9] * iitBody[5] + rotationMatrix[10] * iitBody[8];

	float val0 = t4 * rotationMatrix[0] + t9 * rotationMatrix[1] + t14 * rotationMatrix[2];
	iitWorld[0] = val0;
	float val1 = t4 * rotationMatrix[4] + t9 * rotationMatrix[5] + t14 * rotationMatrix[6];
	iitWorld[1] = val1;
	float val2 = t4 * rotationMatrix[8] + t9 * rotationMatrix[9] + t14 * rotationMatrix[10];
	iitWorld[2] = val2;
	float val3 = t28 * rotationMatrix[0] + t33 * rotationMatrix[1] + t38 * rotationMatrix[2];
	iitWorld[3] = val3;
	float val4 = t28 * rotationMatrix[4] + t33 * rotationMatrix[5] + t38 * rotationMatrix[6];
	iitWorld[4] = val4;
	float val5 = t28 * rotationMatrix[8] + t33 * rotationMatrix[9] + t38 * rotationMatrix[10];
	iitWorld[5] = val5;
	float val6 = t52 * rotationMatrix[0] + t57 * rotationMatrix[1] + t62 * rotationMatrix[2];
	iitWorld[6] = val6;
	float val7 = t52 * rotationMatrix[4] + t57 * rotationMatrix[5] + t62 * rotationMatrix[6];
	iitWorld[7] = val7;
	float val8 = t52 * rotationMatrix[8] + t57 * rotationMatrix[9] + t62 * rotationMatrix[10];
	iitWorld[8] = val8;
}

//-----------------------------------------------------------------------------
Vector3D RigidBody::GetPointInWorldSpace(const Vector3D point)
{
	return m_TransformationMatrix.Transform(point);
}

//-----------------------------------------------------------------------------
void RigidBody::SetIntertiaTensor(const Matrix33f &intertiaTensor)
{
	m_InverseInertiaTensor = intertiaTensor.Inverse();
}

//-----------------------------------------------------------------------------
void RigidBody::AddForce(const Vector3D &force)
{
	m_ForceAccum += force;
	m_IsAwake = true;
}

//-----------------------------------------------------------------------------
void RigidBody::ClearAccumulators()
{
	m_ForceAccum = Vector3D::Zero;
	m_TorqueAccum = Vector3D::Zero;
}

//-----------------------------------------------------------------------------
void RigidBody::Integrate(float duration)
{
	m_LastFrameAcceleration = m_Acceleration;
	m_LastFrameAcceleration += (m_ForceAccum * m_InverseMass);

	Vector3D angularAcceleration = m_InverseInertiaTensorWorld.Transform(m_TorqueAccum);

	m_Velocity += (m_LastFrameAcceleration * duration);

	m_Rotation += (angularAcceleration * duration);

	m_Velocity *= (pow(m_LinearDampening, duration));
	m_Rotation *= (pow(m_AngularDampening, duration));

	m_Position += (m_Velocity * duration);

	m_Orientation.AddScaledVector(m_Rotation, duration);

	CalculateDerivedData();

	ClearAccumulators();
}

//-----------------------------------------------------------------------------
void RigidBody::Initialize(float mass, Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initialRotation, float dampening, float angularDampening)
{
	m_InverseMass = 1 / mass;

	m_LinearDampening = dampening;
	m_AngularDampening = angularDampening;

	m_InitialPosition = initialPosition;
	m_Position = m_InitialPosition;
	m_InitialVelocity = initialVelocity;
	m_Velocity = m_InitialVelocity;
	m_InitialAcceleration = initialAcceleration;
	m_LastFrameAcceleration = m_InitialAcceleration;
	m_Acceleration = m_InitialAcceleration;
	m_InitialRotation = initialRotation;
	m_Rotation = m_InitialRotation;

	m_IsAwake = false;

	m_TransformationMatrix = Matrix44f();
}

//-----------------------------------------------------------------------------
void RigidBody::Reset()
{
	m_Position = m_InitialPosition;
	m_Velocity = m_InitialVelocity;
	m_LastFrameAcceleration = m_InitialAcceleration;
	m_Acceleration = m_InitialAcceleration;
	m_Rotation = m_InitialRotation;
}

//-----------------------------------------------------------------------------
void RigidBody::AddForceAtPoint(const Vector3D &force, const Vector3D &point)
{
	Vector3D worldPoint = point;
	worldPoint -= m_Position;

	m_ForceAccum += force;
	m_TorqueAccum += worldPoint.Cross(force);

	m_IsAwake = true;
}

//-----------------------------------------------------------------------------
void RigidBody::AddForceAtBodyPoint(const Vector3D &force, const Vector3D &point)
{
	Vector3D worldPoint = GetPointInWorldSpace(point);
	AddForceAtPoint(force, worldPoint);
	m_IsAwake = true;
}

//-----------------------------------------------------------------------------
bool RigidBody::HasInfiniteMass()
{
	return m_InverseMass == 1;
}

//-----------------------------------------------------------------------------
float RigidBody::GetMass()
{
	return 1.0f / m_InverseMass;
}

//-----------------------------------------------------------------------------
void RigidBody::GetInverseInertiaTensorWorld(Matrix33f& inverseInertiaTensor) const
{
	inverseInertiaTensor = m_InverseInertiaTensorWorld;
}

//-----------------------------------------------------------------------------
void RigidBody::AddVelocity(const Vector3D& deltaVelocity)
{
	m_Velocity += deltaVelocity;
}

//-----------------------------------------------------------------------------
void RigidBody::AddRotation(const Vector3D& deltaRotation)
{
	m_Rotation += deltaRotation;
}
//=============================================================================