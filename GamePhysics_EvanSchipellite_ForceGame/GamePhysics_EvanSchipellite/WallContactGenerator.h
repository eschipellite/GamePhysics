//=============================================================================
//                              Wall Contact Generator
//
// Written by Evan Schipellite
//
// Handles wall Contacts around a perimeter
//=============================================================================
#ifndef WALL_CONTACT_GENERATOR_H
#define WALL_CONTACT_GENERATOR_H
//=============================================================================
#include "ContactGenerator.h"
//=============================================================================
class WallContactGenerator :
	public ContactGenerator
{
private:
	float m_MinX;
	float m_MaxX;
	float m_MinZ;
	float m_MaxZ;

public:
	WallContactGenerator(float minX, float maxX, float minZ, float maxZ);
	~WallContactGenerator();

	void AddContact(CollisionHandler* collisionHandler);
};
//=============================================================================
#endif // WALL_CONTACT_GENERATOR_H