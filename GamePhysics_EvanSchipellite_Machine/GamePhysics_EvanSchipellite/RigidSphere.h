//=============================================================================
//                              Rigid Sphere
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef RIGID_SPHERE_H
#define RIGID_SPHERE_H
//=============================================================================
#include "RigidRender.h"
//=============================================================================
class RigidSphere :
	public RigidRender
{
protected:
	float m_Radius;

protected:
	void drawObject();

public:
	RigidSphere();
	~RigidSphere();

	void Initialize(std::string textureID, float radius, float mass, Vector3D initialPosition);
};
//=============================================================================
#endif // RIGID_SPHERE_H