//=============================================================================
//                              RigidBody
//
// Written by Evan Schipellite
//=============================================================================
#ifndef RIGIDBODY_H
#define RIGIDBODY_H
//=============================================================================
class RigidBody
{
protected:
	float m_InverseMass;
	float m_LinearDampening;

public:
	RigidBody();
	~RigidBody();
};
//=============================================================================
#endif // RIGIDBODY_H