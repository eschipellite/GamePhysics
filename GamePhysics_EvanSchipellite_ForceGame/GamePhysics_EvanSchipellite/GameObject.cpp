//=============================================================================
//                              Game Object
//
// Written by Evan Schipellite
//
// Extends Physics Object, allows for Rendering
//=============================================================================
#include "GameObject.h"
//=============================================================================
GameObject::GameObject()
{
}

//-----------------------------------------------------------------------------
GameObject::~GameObject()
{
}

//-----------------------------------------------------------------------------
// Code assistance from Robert Bethune
void GameObject::loadTexture(std::string texture)
{
	int width;
	int height;

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	unsigned char* image = SOIL_load_image(texture.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
}

//-----------------------------------------------------------------------------
void GameObject::Draw()
{
	glPushMatrix();
	glTranslatef(m_CurrentPosition.X, m_CurrentPosition.Y, m_CurrentPosition.Z);
	gluSphere(m_Quad, m_Radius, 100, 100);
	glPopMatrix();
}
//=============================================================================