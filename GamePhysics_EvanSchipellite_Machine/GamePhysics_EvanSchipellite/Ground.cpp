//=============================================================================
//                              Ground
//
// Written by Evan Schipellite
//
// Physics Object representing the game surface
//=============================================================================
#include "Ground.h"
//=============================================================================
Ground::Ground()
{
}

//-----------------------------------------------------------------------------
Ground::~Ground()
{
}

//-----------------------------------------------------------------------------
void Ground::Initialize(Vector3D dimensions, float mass, Vector3D initialPosition, std::string texture)
{
	PhysicsObject::Initialize(mass, initialPosition, Vector3D::Zero, Vector3D::Zero, Vector3D::Zero, 1);

	m_Dimensions = dimensions;

	loadTexture(texture);
}

//-----------------------------------------------------------------------------
void Ground::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-m_Dimensions.X, -m_Dimensions.Y, -m_Dimensions.Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(m_Dimensions.X, -m_Dimensions.Y, -m_Dimensions.Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(m_Dimensions.X, -m_Dimensions.Y, m_Dimensions.Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-m_Dimensions.X, -m_Dimensions.Y, m_Dimensions.Z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
//=============================================================================