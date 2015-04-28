//=============================================================================
//                              Rigid Box
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef RIGID_BOX_H
#define RIGID_BOX_H
//=============================================================================
#include "RigidRender.h"
//=============================================================================
class RigidBox :
	public RigidRender
{
protected:
	Vector3D m_HalfSize;

protected:
	void drawObject();

public:
	RigidBox();
	~RigidBox();

	void Initialize(std::string textureID, Vector3D halfSize, float mass, Vector3D initialPosition);

	CollisionBox GetCollisionBox() { return CollisionBox(this, m_HalfSize); };
};
//=============================================================================
#endif // RIGID_BOX_H

