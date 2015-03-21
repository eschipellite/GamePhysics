//=============================================================================
//                              Collision Handler
//
// Written by Evan Schipellite
//
// Holds a list of physics objects to test for collisions
// Checks and resolves collisions
//=============================================================================
#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
//=============================================================================
#include <vector>
#include "Contact.h"

class PhysicsObject;
class ContactGenerator;
//=============================================================================
class CollisionHandler
{
private:
	std::vector<PhysicsObject*> mp_PhysicsObjects;

	std::vector<ContactGenerator*> mp_ContactGenerators;
	std::vector<Contact> m_Contacts;

private:
	int checkCollisions();
	void resolveContacts(float deltaTime);

public:
	CollisionHandler();
	~CollisionHandler();

	void Initialize();
	void CleanUp();
	void Update(float deltaTime);

	void AddGround(PhysicsObject* groundObject);
	void AddCollisionObject(PhysicsObject* physicsObject);
	void AddCollisionObjects(std::vector<PhysicsObject*> physicsObjects);

	void AddContactGenerators(std::vector<ContactGenerator*> contactGenerators);

	std::vector<PhysicsObject*> GetPhysicsObjects() { return mp_PhysicsObjects; };

	void AddContact(Contact contact) { m_Contacts.push_back(contact); };
};
//=============================================================================
#endif // COLLISION_HANDLER_H