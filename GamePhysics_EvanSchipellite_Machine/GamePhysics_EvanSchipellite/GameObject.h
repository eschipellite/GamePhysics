//=============================================================================
//                              Game Object
//
// Written by Evan Schipellite
//
// Extends Physics Object, allows for Rendering
//=============================================================================
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
//=============================================================================
#include "PhysicsObject.h"
#include <iostream>
//=============================================================================
class GameObject :
	public PhysicsObject
{
protected:
	GLuint m_Texture;

	GLUquadric* m_Quad;

protected:
	void loadTexture(std::string textureID);

public:
	GameObject();
	~GameObject();

	void Initialize(Vector3D initialPosition, std::string texture, float mass = 1);

	virtual void Draw();
};
//=============================================================================
#endif // GAME_OBJECT_H

