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
	std::vector<ContactGenerator*> mp_ToAddContactGenerators;
	std::vector<Contact> m_Contacts;

	int m_MaxChecks;
	int m_Collisions;

private:
	int checkCollisions();
	void resolveContacts(float deltaTime);
	void addRunTimeContactGenerators();

public:
	CollisionHandler();
	~CollisionHandler();

	void Initialize();
	void CleanUp();
	void Update(float deltaTime);
	void Reset();

	void AddGround(PhysicsObject* groundObject);
	void AddCollisionObject(PhysicsObject* physicsObject);
	void AddCollisionObjects(std::vector<PhysicsObject*> physicsObjects);

	void AddRunTimeContactGenerator(ContactGenerator* contactGeneraor);
	void AddContactGenerators(std::vector<ContactGenerator*> contactGenerators);

	std::vector<PhysicsObject*> GetPhysicsObjects() { return mp_PhysicsObjects; };

	void AddContact(Contact contact) { m_Contacts.push_back(contact); };

	inline int GetCollisions() { return m_Collisions; };
};
//=============================================================================
#endif // COLLISION_HANDLER_H