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
#include <SOIL.h>
#include <iostream>
//=============================================================================
class GameObject :
	public PhysicsObject
{
protected:
	GLuint m_Texture;

	GLUquadric* m_Quad;

protected:
	void loadTexture(std::string texture);

public:
	GameObject();
	~GameObject();

	virtual void Draw();
};
//=============================================================================
#endif // GAME_OBJECT_H

