//=============================================================================
//                              Contact Generator
//
// Written by Evan Schipellite
//
// Base for Contact Generation
//=============================================================================
#ifndef CONTACT_GENERATOR_H
#define CONTACT_GENERATOR_H
//=============================================================================
#include <vector>

class CollisionHandler;
//=============================================================================
class ContactGenerator
{
public:
	ContactGenerator();
	~ContactGenerator();

	virtual void AddContact(CollisionHandler* collisionHandler) = 0;
};
//=============================================================================
#endif // CONTACT_GENERATOR_H

