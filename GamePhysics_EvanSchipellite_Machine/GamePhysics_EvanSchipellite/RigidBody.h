//=============================================================================
//                              RigidBody
//
// Written by Evan Schipellite
//=============================================================================
#ifndef RIGIDBODY_H
#define RIGIDBODY_H
//=============================================================================
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix.h"
//=============================================================================
class RigidBody
{
protected:
	float m_InverseMass;
	float m_LinearDampening;
	float m_AngularDampening;

	Vector3D m_Position;
	Vector3D m_InitialPosition;
	Vector3D m_Velocity;
	Vector3D m_InitialVelocity;
	Vector3D m_LastFrameAcceleration;
	Vector3D m_Acceleration;
	Vector3D m_InitialAcceleration;
	Vector3D m_Rotation;
	Vector3D m_InitialRotation;
	Vector3D m_ForceAccum;
	Vector3D m_TorqueAccum;

	Quaternion m_Orientation;

	Matrix m_TransformationMatrix;
	Matrix m_InverseInertiaTensor;
	Matrix m_InverseInertiaTensorWorld;

	bool m_IsAwake;

protected:
	void calculateDerivedData();
	static void calculateTransformMatrix(Matrix &transformMatrix, const Vector3D &position, const Quaternion &orientation);
	static void transformInertiaTensor(Matrix &iitWorld, const Quaternion &quaternion, const Matrix &iitBody, const Matrix &rotationMatrix);

public:
	RigidBody();
	~RigidBody();

	void SetIntertiaTensor(const Matrix &intertiaTensor);
	void AddForce(const Vector3D &force);
	void ClearAccumulators();
	void Integrate(float duration);

	virtual void Initialize(float mass, Vector3D initialPosition, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initialRotation = Vector3D::Zero, float linearDampening = 1, float angularDampening = 1);
	void Reset();

	void AddForceAtPoint(const Vector3D &force, const Vector3D &point);
	void AddForceAtBodyPoint(const Vector3D &force, const Vector3D &point);

	bool HasInfiniteMass();
	float GetMass();

	Vector3D GetPointInWorldSpace(const Vector3D point);
	Matrix GetTransform() const { return m_TransformationMatrix; };
};
//=============================================================================
#endif // RIGIDBODY_H