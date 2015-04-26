//=============================================================================
//                              Rigid Render
//
// Written by Evan Schipellite
//=============================================================================
#include "RigidRender.h"
#include "ImageHandler.h"
//=============================================================================
RigidRender::RigidRender()
{
}

//-----------------------------------------------------------------------------
RigidRender::~RigidRender()
{
}

//-----------------------------------------------------------------------------
void RigidRender::loadTexture(std::string textureID)
{
	m_Texture = *(ImageHandler::GetInstance()->GetImage(textureID));

	m_Quad = gluNewQuadric();
}

//-----------------------------------------------------------------------------
void RigidRender::Initialize(std::string textureID, float mass, Vector3D initialPosition)
{
	loadTexture(textureID);

	RigidBody::Initialize(mass, initialPosition);
}

//-----------------------------------------------------------------------------
void RigidRender::Draw()
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
	drawObject();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
//=============================================================================