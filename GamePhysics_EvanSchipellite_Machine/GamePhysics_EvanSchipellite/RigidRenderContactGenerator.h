//=============================================================================
//                              Rigid Render Contact Generator
//
// Written by Evan Schipellite
//
//=============================================================================
#ifndef RIGID_RENDER_CONTACT_GENRATOR_H
#define RIGID_RENDER_CONTACT_GENRATOR_H
//=============================================================================
#include "ContactGenerator.h"
//=============================================================================
class RigidRenderContactGenerator :
	public ContactGenerator
{
public:
	RigidRenderContactGenerator();
	~RigidRenderContactGenerator();

	void AddContact(CollisionHandler* collisionHandler);
};
//=============================================================================
#endif // RIGID_RENDER_CONTACT_GENERATOR_H

