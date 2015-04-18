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

	Vector3D m_Position;
	Vector3D m_Velocity;
	Vector3D m_LastFrameAcceleration;
	Vector3D m_Acceleration;
	Vector3D m_Rotation;
	Vector3D m_ForceAccum;
	Vector3D m_TorqueAccum;

	Quaternion m_Orientation;

	Matrix m_TransformationMatrix;
	Matrix m_InverseInertiaTensor;
	Matrix m_InverseInertiaTensorWorld;

	bool m_IsAwake;

	float m_AngularDamping;

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

	void AddForceAtPoint(const Vector3D &force, const Vector3D &point);
	void AddForceAtBodyPoint(const Vector3D &force, const Vector3D &point);

	bool HasInfiniteMass();
	float GetMass();

	Vector3D GetPointInWorldSpace(const Vector3D point);
};
//=============================================================================
#endif // RIGIDBODY_H