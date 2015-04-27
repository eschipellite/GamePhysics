//=============================================================================
//                              Rigid Sphere
//
// Written by Evan Schipellite
//
//=============================================================================
#include "RigidSphere.h"
//=============================================================================
RigidSphere::RigidSphere()
{
}

//-----------------------------------------------------------------------------
RigidSphere::~RigidSphere()
{
}

//-----------------------------------------------------------------------------
void RigidSphere::drawObject()
{
	glTranslatef(m_Position.X, m_Position.Y, m_Position.Z);
	gluSphere(m_Quad, m_Radius, 32, 32);
}

//-----------------------------------------------------------------------------
void RigidSphere::Initialize(std::string textureID, float radius, float mass, Vector3D initialPosition)
{
	m_Radius = radius;

	RigidRender::Initialize(textureID, mass, initialPosition);
}
//=============================================================================