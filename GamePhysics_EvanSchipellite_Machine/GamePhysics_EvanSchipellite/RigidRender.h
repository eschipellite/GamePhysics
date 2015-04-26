//=============================================================================
//                              Rigid Render
//
// Written by Evan Schipellite
//=============================================================================
#ifndef RIGID_RENDER_H
#define RIGID_RENDER_H
//=============================================================================
#include "RigidBody.h"
#include "GL/glut.h"
#include <string>
//=============================================================================
class RigidRender :
	public RigidBody
{
protected:
	GLuint m_Texture;

	GLUquadric* m_Quad;

protected:
	void loadTexture(std::string textureID);
	virtual void drawObject() = 0;

public:
	RigidRender();
	~RigidRender();

	void Initialize(std::string textureID, float mass, Vector3D initialPosition);
	void Draw();
};
//=============================================================================
#endif // RIGID_RENDER_H