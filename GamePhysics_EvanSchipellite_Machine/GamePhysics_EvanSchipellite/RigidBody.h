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
#include "Matrix44f.h"
#include "Matrix33f.h"
#include "CollisionSphere.h"
#include "CollisionBox.h"
//=============================================================================

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

	Matrix44f m_TransformationMatrix;
	Matrix33f m_InverseInertiaTensor;
	Matrix33f m_InverseInertiaTensorWorld;

	bool m_IsAwake;

	int m_CollisionType;

protected:
	static void calculateTransformMatrix(Matrix44f &transformMatrix, const Vector3D &position, const Quaternion &orientation);
	static void transformInertiaTensor(Matrix33f &iitWorld, const Quaternion &quaternion, const Matrix33f &iitBody, const Matrix44f &rotationMatrix);

public:
	RigidBody();
	~RigidBody();

	void CalculateDerivedData();
	void SetIntertiaTensor(const Matrix33f &intertiaTensor);
	void AddForce(const Vector3D &force);
	void ClearAccumulators();
	void Integrate(float duration);

	virtual void Initialize(float mass, Vector3D initialPosition, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initialRotation = Vector3D::Zero, float linearDampening = 1, float angularDampening = 1);
	void Reset();

	void AddForceAtPoint(const Vector3D &force, const Vector3D &point);
	void AddForceAtBodyPoint(const Vector3D &force, const Vector3D &point);

	float GetMass();

	bool HasInfiniteMass();
	bool GetAwake() { return m_IsAwake; };
	void SetAwake() { m_IsAwake = true; };

	void SetPosition(Vector3D position) { m_Position = position; };
	void SetOrientation(Quaternion orientation) { m_Orientation = orientation; };

	Quaternion GetOrientation() { return m_Orientation; };

	Vector3D GetPointInWorldSpace(const Vector3D point);
	Matrix44f GetTransform() const { return m_TransformationMatrix; };
	Vector3D GetPosition() { return m_Position; };
	Vector3D GetRotation() { return m_Rotation; };
	Vector3D GetVelocity() { return m_Velocity; };
	Vector3D GetLastFrameAcceleration() { return m_LastFrameAcceleration; };
	virtual CollisionSphere GetCollisionSphere() { return CollisionSphere(this, 1); };
	virtual CollisionBox GetCollisionBox() { return CollisionBox(this, Vector3D(1, 1, 1)); };

	void GetInverseInertiaTensorWorld(Matrix33f& inverseInertiaTensor) const;

	float GetInverseMass() { return m_InverseMass; };

	void AddVelocity(const Vector3D& deltaVelocity);
	void AddRotation(const Vector3D& deltaRotation);

	int GetCollisionType() { return m_CollisionType; };
};
//=============================================================================
#endif // RIGIDBODY_H