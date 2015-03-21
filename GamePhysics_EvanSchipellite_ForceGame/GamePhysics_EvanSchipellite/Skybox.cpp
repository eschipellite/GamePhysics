//=============================================================================
//                              Skybox
//
// Written by Evan Schipellite
//
// Renders the Skybox
//=============================================================================
#include "Skybox.h"
#include <SOIL.h>
//=============================================================================
Skybox::Skybox()
{
}

//-----------------------------------------------------------------------------
Skybox::~Skybox()
{
}

//-----------------------------------------------------------------------------
void Skybox::Initialize(std::string frontPath, std::string backPath, std::string topPath, std::string bottomPath, std::string rightPath, std::string leftPath)
{
	loadTexture(frontPath, &m_Texture_Front);
	loadTexture(backPath, &m_Texture_Back);
	loadTexture(topPath, &m_Texture_Top);
	loadTexture(bottomPath, &m_Texture_Bottom);
	loadTexture(rightPath, &m_Texture_Right);
	loadTexture(leftPath, &m_Texture_Left);
}

//-----------------------------------------------------------------------------
void Skybox::CleanUp()
{
	
}

//-----------------------------------------------------------------------------
void Skybox::loadTexture(std::string texturePath, GLuint* texture)
{
	int width;
	int height;

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
}

//-----------------------------------------------------------------------------
// Cube map Coordinates: https://www.opengl.org/discussion_boards/showthread.php/182361-Skybox
void Skybox::Draw()
{
	GLfloat width = 40;
	GLfloat height = 40;
	GLfloat length = 40;

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, m_Texture_Back);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(width, -height, -length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-width, -height, -length);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-width, height, -length);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(width, height, -length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Texture_Bottom);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-width, -height, -length);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(width, -height, -length);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(width, -height, length);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-width, -height, length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Texture_Top);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(width, height, -length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-width, height, -length);
	glTexCoord2d(0.0, 1.0f);	
	glVertex3f(-width, height, length);
	glTexCoord2d(0.0, 0.0f);	
	glVertex3f(width, height, length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Texture_Front);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(width, height, length);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-width, height, length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-width, -height, length);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(width, -height, length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Texture_Left);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-width, height, -length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-width, -height, -length);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-width, -height, length);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-width, height, length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_Texture_Right);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(width, height, -length);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(width, height, length);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(width, -height, length);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(width, -height, -length);
	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
//=============================================================================