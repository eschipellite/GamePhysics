//=============================================================================
//                              Rigid Contact
//
// Written by Evan Schipellite
//
// Basis from: https://github.com/idmillington/cyclone-physics
//=============================================================================
#include "RigidContact.h"
#include <math.h>
//=============================================================================
RigidContact::RigidContact()
{
}

//-----------------------------------------------------------------------------
RigidContact::~RigidContact()
{
}

//-----------------------------------------------------------------------------
void RigidContact::calculateContactBasis()
{
	Vector3D contactTangentX;
	Vector3D contactTangentY;
	float scale;

	if (abs(m_ContactNormal.X) > abs(m_ContactNormal.Y))
	{
		scale = 1.0f / sqrtf(m_ContactNormal.Z * m_ContactNormal.Z + m_ContactNormal.X * m_ContactNormal.X);

		contactTangentX.X = m_ContactNormal.Z * scale;
		contactTangentX.Y = 0;
		contactTangentX.Z = -m_ContactNormal.X * scale;

		contactTangentY.X = m_ContactNormal.Y * contactTangentX.X;
		contactTangentY.Y = m_ContactNormal.Z * contactTangentX.X - m_ContactNormal.X * contactTangentX.Z;
		contactTangentY.Z = -m_ContactNormal.Y * contactTangentX.X;
	}
	else
	{
		scale = 1.0f / sqrtf(m_ContactNormal.Z * m_ContactNormal.Z + m_ContactNormal.Y * m_ContactNormal.Y);

		contactTangentX.X = 0;
		contactTangentX.Y = -m_ContactNormal.Z * scale;
		contactTangentX.Z = m_ContactNormal.Y * scale;

		contactTangentY.X = m_ContactNormal.Y * contactTangentX.Z - m_ContactNormal.Z * contactTangentX.Y;
		contactTangentY.Y = -m_ContactNormal.X * contactTangentX.Z;
		contactTangentY.Z = m_ContactNormal.X * contactTangentX.Y;
	}

	m_ContactToWorld = Matrix(3, 3);
	m_ContactToWorld.Set(0, m_ContactNormal.X);
	m_ContactToWorld.Set(1, contactTangentX.X);
	m_ContactToWorld.Set(2, contactTangentY.X);
	m_ContactToWorld.Set(3, m_ContactNormal.Y);
	m_ContactToWorld.Set(4, contactTangentX.Y);
	m_ContactToWorld.Set(5, contactTangentY.Y);
	m_ContactToWorld.Set(6, m_ContactNormal.Z);
	m_ContactToWorld.Set(7, contactTangentX.Z);
	m_ContactToWorld.Set(8, contactTangentY.Z);
}

//-----------------------------------------------------------------------------
Vector3D RigidContact::calculateLocalVelocity(unsigned int rigidBodyIndex, float deltaTime)
{
	RigidBody* rigidBody;
	Vector3D relativePosition;
	if (rigidBodyIndex == 0)
	{
		rigidBody = mp_RigidBodyOne;
		relativePosition = m_RelativeContactPositionOne;
	}
	else
	{
		rigidBody = mp_RigidBodyTwo;
		relativePosition = m_RelativeContactPositionTwo;
	}

	Vector3D velocity = rigidBody->GetRotation().Cross(relativePosition);
	velocity += rigidBody->GetVelocity();

	Vector3D contactVelocity = m_ContactToWorld.TransformTranspose(velocity);
	Vector3D accVelocity = rigidBody->GetLastFrameAcceleration() * deltaTime;
	accVelocity = m_ContactToWorld.TransformTranspose(accVelocity);
	accVelocity.X = 0;

	m_ContactVelocity += accVelocity;

	return contactVelocity;
}

//-----------------------------------------------------------------------------
void RigidContact::CalculateDesiredDeltavelocity(float deltaTime)
{
	const float velocityLimit = 0.25f;
	float velocityFromAcc = 0;

	if (mp_RigidBodyOne->GetAwake())
	{
		velocityFromAcc += mp_RigidBodyOne->GetLastFrameAcceleration().Dot(m_ContactNormal) * deltaTime;
	}

	if (mp_RigidBodyTwo && mp_RigidBodyTwo->GetAwake())
	{
		velocityFromAcc -= mp_RigidBodyTwo->GetLastFrameAcceleration().Dot(m_ContactNormal) * deltaTime;
	}

	float thisRestitution = m_Restitution;
	if (abs(m_ContactVelocity.X) < velocityLimit)
		thisRestitution = 0.0f;

	m_DesiredDeltaVelocity = -m_ContactVelocity.X - thisRestitution * (m_ContactVelocity.X - velocityFromAcc);
}

//-----------------------------------------------------------------------------
Vector3D RigidContact::calculateFrictionlessImpulse(Matrix* inverseInertiaTensor)
{
	Vector3D impulseContact;

	Vector3D deltaVelWorld = m_RelativeContactPositionOne.Cross(m_ContactNormal);
	deltaVelWorld = inverseInertiaTensor[0].Transform(deltaVelWorld);
	deltaVelWorld = deltaVelWorld.Cross(m_RelativeContactPositionOne);

	float deltaVelocity = deltaVelWorld.Dot(m_ContactNormal);
	deltaVelocity += mp_RigidBodyOne->GetInverseMass();

	if (mp_RigidBodyTwo)
	{
		Vector3D deltaVelWorld = m_RelativeContactPositionTwo.Cross(m_ContactNormal);
		deltaVelWorld = inverseInertiaTensor[1].Transform(deltaVelWorld);
		deltaVelWorld = deltaVelWorld.Cross(m_RelativeContactPositionTwo);

		deltaVelocity += deltaVelWorld.Dot(m_ContactNormal);
		deltaVelocity += mp_RigidBodyTwo->GetInverseMass();
	}

	impulseContact.X = m_DesiredDeltaVelocity / deltaVelocity;
	impulseContact.Y = 0;
	impulseContact.Z = 0;
	
	return impulseContact;
}

//-----------------------------------------------------------------------------
Vector3D RigidContact::calculateFrictionImpulse(Matrix* inverseInertiaTensor)
{
	Vector3D impulseContact;
	float inverseMass = mp_RigidBodyOne->GetInverseMass();

	Matrix impulseToTorque = Matrix(3, 3);
	impulseToTorque.SetSkewSymmetric(m_RelativeContactPositionOne);

	Matrix deltaVelWorld = impulseToTorque;
	deltaVelWorld = deltaVelWorld * inverseInertiaTensor[0];
	deltaVelWorld = deltaVelWorld * impulseToTorque;
	deltaVelWorld = deltaVelWorld * -1;

	if (mp_RigidBodyTwo)
	{
		impulseToTorque.SetSkewSymmetric(m_RelativeContactPositionTwo);

		Matrix deltaVelWorld2 = impulseToTorque;
		deltaVelWorld2 = deltaVelWorld2 * inverseInertiaTensor[1];
		deltaVelWorld2 = deltaVelWorld2 * impulseToTorque;
		deltaVelWorld2 = deltaVelWorld2 * -1;

		deltaVelWorld = deltaVelWorld + deltaVelWorld2;

		inverseMass += mp_RigidBodyTwo->GetInverseMass();
	}

	Matrix deltaVelocity = m_ContactToWorld.GetTranspose();
	deltaVelocity = deltaVelocity * deltaVelWorld;
	deltaVelocity = deltaVelocity * m_ContactToWorld;

	deltaVelocity.Set(0, deltaVelocity.Get(0) + inverseMass);
	deltaVelocity.Set(4, deltaVelocity.Get(4) + inverseMass);
	deltaVelocity.Set(8, deltaVelocity.Get(8) + inverseMass);

	Matrix impulseMatrix = deltaVelocity.GetInverse();

	Vector3D velKill(m_DesiredDeltaVelocity, -m_ContactVelocity.Y, -m_ContactVelocity.Z);

	impulseContact = impulseMatrix.Transform(velKill);

	float planarImpulse = sqrt(impulseContact.Y * impulseContact.Y + impulseContact.Z * impulseContact.Z);

	if (planarImpulse > impulseContact.X * m_Friction)
	{
		impulseContact.Y /= planarImpulse;
		impulseContact.Z /= planarImpulse;

		impulseContact.X = deltaVelocity.Get(0) + deltaVelocity.Get(1) * m_Friction * impulseContact.Y +
			deltaVelocity.Get(2) * m_Friction * impulseContact.Z;
		impulseContact.X = m_DesiredDeltaVelocity / impulseContact.X;
		impulseContact.Y *= m_Friction * impulseContact.X;
		impulseContact.Z *= m_Friction * impulseContact.X;
	}

	return impulseContact;
}

//-----------------------------------------------------------------------------
void RigidContact::Initialize(RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo, Vector3D contactPoint, Vector3D contactNormal, float penetration, float restitution, float friction)
{
	mp_RigidBodyOne = rigidBodyOne;
	mp_RigidBodyTwo = rigidBodyTwo;

	m_ContactPoint = contactPoint;
	m_ContactNormal = contactNormal;

	m_Penetration = penetration;
	m_Restitution = restitution;
	m_Friction = friction;
}

//-----------------------------------------------------------------------------
void RigidContact::CalculateInternals(float deltaTime)
{
	calculateContactBasis();

	m_RelativeContactPositionOne = m_ContactPoint - mp_RigidBodyOne->GetPosition();

	if (mp_RigidBodyTwo)
		m_RelativeContactPositionTwo = m_ContactPoint - mp_RigidBodyTwo->GetPosition();

	m_ContactVelocity = calculateLocalVelocity(0, deltaTime);
	if (mp_RigidBodyTwo)
		m_ContactVelocity -= calculateLocalVelocity(1, deltaTime);

	CalculateDesiredDeltavelocity(deltaTime);
}

//-----------------------------------------------------------------------------
void RigidContact::MatchAwakeState()
{
	if (!mp_RigidBodyTwo)
		return;

	bool bodyOneAwake = mp_RigidBodyOne->GetAwake();
	bool bodyTwoAwake = mp_RigidBodyTwo->GetAwake();

	if (!bodyOneAwake && bodyTwoAwake)
	{
		mp_RigidBodyOne->SetAwake();
	}
	else if (bodyOneAwake && !bodyTwoAwake)
	{
		mp_RigidBodyTwo->SetAwake();
	}
}

//-----------------------------------------------------------------------------
void RigidContact::ApplyPositionChange(Vector3D linearChange[2], Vector3D angularChange[2], float penetration, float deltaTime)
{
	const float angularLimit = 0.2f;
	float angularMove[2];
	float linearMove[2];

	float totalInertia = 0;
	float linearInertia[2];
	float angularInertia[2];

	for (unsigned int i = 0; i < 2; i++)
	{
		if (i == 0 && mp_RigidBodyOne || i == 1 && mp_RigidBodyTwo)
		{
			RigidBody* rigidBody;
			Vector3D relativeContactPosition;
			if (i == 0)
			{
				rigidBody = mp_RigidBodyOne;
				relativeContactPosition = m_RelativeContactPositionOne;
			}
			else
			{
				rigidBody = mp_RigidBodyTwo;
				relativeContactPosition = m_RelativeContactPositionTwo;
			}

			Matrix inverseInertiaTensor = Matrix(3, 3);
			rigidBody->GetInverseInertiaTensorWorld(inverseInertiaTensor);

			Vector3D angularInertiaWorld = relativeContactPosition.Cross(m_ContactNormal);
			angularInertiaWorld = inverseInertiaTensor.Transform(angularInertiaWorld);
			angularInertiaWorld = angularInertiaWorld.Cross(relativeContactPosition);
			angularInertia[i] = angularInertiaWorld.Dot(m_ContactNormal);

			linearInertia[i] = rigidBody->GetInverseMass();

			totalInertia += linearInertia[i] + angularInertia[i];
		}
	}

	for (unsigned int i = 0; i < 2; i++)
	{
		if (i == 0 && mp_RigidBodyOne || i == 1 && mp_RigidBodyTwo)
		{
			RigidBody* rigidBody;
			Vector3D relativeContactPosition;
			if (i == 0)
			{
				rigidBody = mp_RigidBodyOne;
				relativeContactPosition = m_RelativeContactPositionOne;
			}
			else
			{
				rigidBody = mp_RigidBodyTwo;
				relativeContactPosition = m_RelativeContactPositionTwo;
			}

			int sign = (i == 0) ? 1 : -1;
			angularMove[i] = sign * m_Penetration * (angularInertia[i] / totalInertia);
			linearMove[i] = sign * penetration * (linearInertia[i] / totalInertia);

			Vector3D projection = relativeContactPosition;
			projection += m_ContactNormal * ((relativeContactPosition * -1) * m_ContactNormal);

			float maxMagnitude = angularLimit * projection.Magnitude();

			if (angularMove[i] < -maxMagnitude)
			{
				float totalMove = angularMove[i] + linearMove[i];
				angularMove[i] = -maxMagnitude;
				linearMove[i] = totalMove - angularMove[i];
			}
			else if (angularMove[i] > maxMagnitude)
			{
				float totalMove = angularMove[i] + linearMove[i];
				angularMove[i] = maxMagnitude;
				linearMove[i] = totalMove - angularMove[i];
			}

			if (angularMove[i] == 0)
			{
				angularChange[i] = Vector3D::Zero;
			}
			else
			{
				Vector3D targetAngularDirection = relativeContactPosition * m_ContactNormal;

				Matrix inverseInertiaTensor = Matrix(3, 3);
				rigidBody->GetInverseInertiaTensorWorld(inverseInertiaTensor);

				angularChange[i] = inverseInertiaTensor.Transform(targetAngularDirection) * (angularMove[i] / angularInertia[i]);
			}

			linearChange[i] = m_ContactNormal * linearMove[i];

			Vector3D position = rigidBody->GetPosition();
			position += m_ContactNormal * linearMove[i] * deltaTime;
			rigidBody->SetPosition(position);

			Quaternion q;
			q = rigidBody->GetOrientation();
			q.AddScaledVector(angularChange[i] * deltaTime, 1.0f);
			rigidBody->SetOrientation(q);

			if (!rigidBody->GetAwake())
				rigidBody->CalculateDerivedData();
		}
	}
}

//-----------------------------------------------------------------------------
void RigidContact::ApplyVelocityChange(Vector3D velocityChange[2], Vector3D rotationChange[2], float deltaTime)
{
	Matrix inverseInertiaTensor[2];
	mp_RigidBodyOne->GetInverseInertiaTensorWorld(inverseInertiaTensor[0]);
	if (mp_RigidBodyTwo)
		mp_RigidBodyTwo->GetInverseInertiaTensorWorld(inverseInertiaTensor[1]);

	Vector3D impulseContact;

	if (m_Friction = 0.0f)
	{
		impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
	}
	else
	{
		impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
		//impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
	}

	Vector3D impulse = m_ContactToWorld.Transform(impulseContact);

	Vector3D impulsiveTorque = m_RelativeContactPositionOne.Cross(impulse);
	rotationChange[0] = inverseInertiaTensor[0].Transform(impulsiveTorque);
	velocityChange[0] = Vector3D::Zero;
	velocityChange[0] += impulse * mp_RigidBodyOne->GetInverseMass();

	mp_RigidBodyOne->AddVelocity(velocityChange[0]);
	mp_RigidBodyOne->AddRotation(rotationChange[0]);

	if (mp_RigidBodyTwo)
	{
		Vector3D impulsiveTorque = impulse.Cross(m_RelativeContactPositionTwo);
		rotationChange[1] = inverseInertiaTensor[1].Transform(impulsiveTorque);
		velocityChange[1] = Vector3D::Zero;
		velocityChange[1] += impulse * mp_RigidBodyTwo->GetInverseMass();

		mp_RigidBodyTwo->AddVelocity(velocityChange[1] * deltaTime);
		mp_RigidBodyTwo->AddRotation(rotationChange[1] * deltaTime);
	}
}

//-----------------------------------------------------------------------------
RigidBody* RigidContact::GetRigidBody(int index)
{
	if (index == 0)
	{
		return mp_RigidBodyOne;
	}
	else
	{
		return mp_RigidBodyTwo;
	}
}

//-----------------------------------------------------------------------------
Vector3D RigidContact::GetRelativeContactPosition(int index)
{
	if (index == 0)
	{
		return m_RelativeContactPositionOne;
	}
	else
	{
		return m_RelativeContactPositionTwo;
	}
}
//=============================================================================