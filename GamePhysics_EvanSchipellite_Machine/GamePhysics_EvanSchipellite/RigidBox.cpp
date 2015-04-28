//=============================================================================
//                              Rigid Box
//
// Written by Evan Schipellite
//
//=============================================================================
#include "RigidBox.h"
//=============================================================================
RigidBox::RigidBox()
{
	m_CollisionType = CollisionType::BOX;
}

//-----------------------------------------------------------------------------
RigidBox::~RigidBox()
{
}

//-----------------------------------------------------------------------------
void RigidBox::drawObject()
{
	glTranslatef(m_Position.X, m_Position.Y, m_Position.Z);
	glRotatef(m_Orientation.R, m_Orientation.I, m_Orientation.J, m_Orientation.K);
	gluSphere(m_Quad, m_HalfSize.X, 32, 32);
}

//-----------------------------------------------------------------------------
void RigidBox::Initialize(std::string textureID, Vector3D halfSize, float mass, Vector3D initialPosition)
{
	m_HalfSize = halfSize;

	RigidRender::Initialize(textureID, mass, initialPosition);
}
//=============================================================================