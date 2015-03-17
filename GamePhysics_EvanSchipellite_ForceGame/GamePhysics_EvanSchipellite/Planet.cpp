//=============================================================================
//                              Planet
//
// Written by Evan Schipellite
//
// Base class for planets
//=============================================================================
#include "Planet.h"
//=============================================================================
Planet::Planet()
{
	m_PlanetName = "Empty";
}

//-----------------------------------------------------------------------------
Planet::~Planet()
{
}

//-----------------------------------------------------------------------------
void Planet::Initialize(float radius, float mass, Vector3D initialPosition, Vector3D initialVelocity, std::string planeName, std::string texture)
{
	PhysicsObject::Initialize(radius, mass, initialPosition, initialVelocity, Vector3D::Zero, Vector3D::Zero, .999999999999999999999f);

	m_PlanetName = planeName;

	loadTexture(texture);

	m_Quad = gluNewQuadric();
}

//-----------------------------------------------------------------------------
void Planet::Update(float deltaTime)
{
	deltaTime *= 86400; // Seconds per day

	PhysicsObject::updateForces(deltaTime);
}

//-----------------------------------------------------------------------------
// Code assistance from Robert Bethune
void Planet::loadTexture(std::string texture)
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
// Code assistance from Robert Bethune
void Planet::Draw()
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

	gluSphere(m_Quad, m_Radius, 10, 10);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
//=============================================================================