//=============================================================================
//                              Collision Handler
//
// Written by Evan Schipellite
//
// Holds a list of physics objects to test for collisions
// Checks and resolves collisions
//=============================================================================
#include "CollisionHandler.h"
#include "PhysicsObject.h"
#include "Contact.h"
#include "GroundContactGenerator.h"
//=============================================================================
CollisionHandler::CollisionHandler()
{
	m_MaxChecks = 25;
}

//-----------------------------------------------------------------------------
CollisionHandler::~CollisionHandler()
{
}

//-----------------------------------------------------------------------------
int CollisionHandler::checkCollisions()
{
	int contactCount = 0;
	std::vector<ContactGenerator*>::iterator contactGeneratorIter;
	for (contactGeneratorIter = mp_ContactGenerators.begin(); contactGeneratorIter != mp_ContactGenerators.end(); contactGeneratorIter++)
	{
		(*contactGeneratorIter)->AddContact(this);
		contactCount++;
	}

	return contactCount;
}

//-----------------------------------------------------------------------------
void CollisionHandler::resolveContacts(float deltaTime)
{
	std::vector<Contact>::iterator contactIter;
	for (contactIter = m_Contacts.begin(); contactIter != m_Contacts.end(); contactIter++)
	{
		(*contactIter).Resolve(deltaTime);
	}

	m_Contacts.clear();
}

//-----------------------------------------------------------------------------
void CollisionHandler::Initialize()
{
}

//-----------------------------------------------------------------------------
void CollisionHandler::CleanUp()
{

}

//-----------------------------------------------------------------------------
void CollisionHandler::Update(float deltaTime)
{
	int checkCount = checkCollisions() * 2 - 1;
	resolveContacts(deltaTime);
	if (checkCount > m_MaxChecks)
	{
		checkCount = m_MaxChecks;
	}

	for (int index = 0; index < checkCount; index++)
	{
		checkCollisions();
		resolveContacts(deltaTime);
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddGround(PhysicsObject* groundObject)
{
	mp_ContactGenerators.push_back(new GroundContactGenerator(groundObject->GetPosition().Y));
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddCollisionObject(PhysicsObject* physicsObject)
{
	mp_PhysicsObjects.push_back(physicsObject);
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddCollisionObjects(std::vector<PhysicsObject*> physicsObjects)
{
	std::vector<PhysicsObject*>::iterator physicsObjectIter;
	for (physicsObjectIter = physicsObjects.begin(); physicsObjectIter != physicsObjects.end(); physicsObjectIter++)
	{
		mp_PhysicsObjects.push_back(*physicsObjectIter);
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddContactGenerators(std::vector<ContactGenerator*> contactGenerators)
{
	mp_ContactGenerators.insert(mp_ContactGenerators.end(), contactGenerators.begin(), contactGenerators.end());
}
//=============================================================================