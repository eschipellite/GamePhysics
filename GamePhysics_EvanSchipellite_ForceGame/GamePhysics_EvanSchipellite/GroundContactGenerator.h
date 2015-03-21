//=============================================================================
//                              Ground Contact Generator
//
// Written by Evan Schipellite
//
// Handles Ground Contact at a Y position
//=============================================================================
#ifndef GROUND_CONTACT_GENERATOR
#define GROUND_CONTACT_GENERATOR
//=============================================================================
#include "ContactGenerator.h"
//=============================================================================
class GroundContactGenerator :
	public ContactGenerator
{
private:
	float m_GroundY;
public:
	GroundContactGenerator(float groundY = 0);
	~GroundContactGenerator();

	void AddContact(CollisionHandler* collisionHandler);
	inline void SetGroundY(float groundY) { m_GroundY = groundY; };
};
//=============================================================================
#endif // GROUND_CONTACT_GENERATOR