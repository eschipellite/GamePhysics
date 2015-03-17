//=============================================================================
//                              Player
//
// Written by Evan Schipellite
//
// Contains Player Object and Player Values
//=============================================================================
#include "Player.h"
//=============================================================================
Player::Player()
{
}

//-----------------------------------------------------------------------------
Player::~Player()
{
}

//-----------------------------------------------------------------------------
void Player::Initialize(Vector3D initialPosition, std::string texture)
{
	PhysicsObject::Initialize(1, initialPosition, Vector3D::Zero, Vector3D::Zero, Vector3D::Zero, .99f);

	loadTexture(texture);
}

//-----------------------------------------------------------------------------
void Player::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	gluQuadricTexture(m_Quad, m_Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricDrawStyle(m_Quad, GLU_FILL);
	gluQuadricTexture(m_Quad, GL_TRUE);
	gluQuadricNormals(m_Quad, GLU_SMOOTH);

	glPushMatrix();
	glTranslatef(m_CurrentPosition.X, m_CurrentPosition.Y, m_CurrentPosition.Z);
	gluSphere(m_Quad, m_Radius, 36, 36);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
//=============================================================================
