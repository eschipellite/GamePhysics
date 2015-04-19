//=============================================================================
//                              Game Object
//
// Written by Evan Schipellite
//
// Extends Physics Object, allows for Rendering
//=============================================================================
#include "GameObject.h"
#include <SOIL.h>
#include "ImageHandler.h"
//=============================================================================
GameObject::GameObject()
{
}

//-----------------------------------------------------------------------------
GameObject::~GameObject()
{
}

void GameObject::Initialize(Vector3D initialPosition, std::string texture, float mass)
{
	PhysicsObject::Initialize(mass, initialPosition);

	loadTexture(texture);
}

//-----------------------------------------------------------------------------
// Code assistance from Robert Bethune
void GameObject::loadTexture(std::string textureID)
{
	m_Texture = *(ImageHandler::GetInstance()->GetImage(textureID));

	m_Quad = gluNewQuadric();
}

//-----------------------------------------------------------------------------
void GameObject::Draw()
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