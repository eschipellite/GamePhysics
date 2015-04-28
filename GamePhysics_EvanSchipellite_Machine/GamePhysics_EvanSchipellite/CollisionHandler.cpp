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
#include "WallContactGenerator.h"
#include "CollisionDetector.h"
#include "RigidGroundContactGenerator.h"
//=============================================================================
CollisionHandler::CollisionHandler()
{
	m_MaxChecks = 4;
	m_Collisions = 0;

	m_PositionIterations = 1;
	m_PositionEpsilon = 0.01f;
	m_VelocityIterations = 1;
	m_VelocityEpsilon = 0.01f;

	m_Restitution = 0.5f;
	m_Friction = 0.5f;

	mp_CollisionDetector = new CollisionDetector();
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

	int rigidContactCount = 0;
	std::vector<ContactGenerator*>::iterator rigidContactGeneratorIter;
	for (rigidContactGeneratorIter = mp_RigidContactGenerators.begin(); rigidContactGeneratorIter != mp_RigidContactGenerators.end(); rigidContactGeneratorIter++)
	{
		(*rigidContactGeneratorIter)->AddContact(this);
		rigidContactCount++;
	}

	return contactCount + rigidContactCount;
}

//-----------------------------------------------------------------------------
void CollisionHandler::resolveContacts(float deltaTime)
{
	std::vector<Contact>::iterator contactIter;
	for (contactIter = m_Contacts.begin(); contactIter != m_Contacts.end(); contactIter++)
	{
		(*contactIter).Resolve(deltaTime);
	}

	resolveRigidBodyContacts(deltaTime);

	m_RigidContacts.clear();
	m_Contacts.clear();
}

//-----------------------------------------------------------------------------
void CollisionHandler::resolveRigidBodyContacts(float deltaTime)
{
	prepareRigidBodyContacts(deltaTime);
	//adjustPositions(deltaTime);
	adjustVelocities(deltaTime);
}

//-----------------------------------------------------------------------------
void CollisionHandler::prepareRigidBodyContacts(float deltaTime)
{
	std::vector<RigidContact>::iterator rigidContactIter;
	for (rigidContactIter = m_RigidContacts.begin(); rigidContactIter != m_RigidContacts.end(); rigidContactIter++)
	{
		(*rigidContactIter).CalculateInternals(deltaTime);
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::adjustPositions(float deltaTime)
{
	unsigned int i;
	unsigned int index;
	Vector3D linearChange[2];
	Vector3D angularChange[2];
	float max;
	Vector3D deltaPosition;

	m_PositionIterationsUsed = 0;
	while (m_PositionIterationsUsed < m_PositionIterations)
	{
		max = m_PositionEpsilon;
		index = m_RigidContacts.size();

		for (i = 0; i < m_RigidContacts.size(); i++)
		{
			float penetration = m_RigidContacts[i].GetPenetration();
			if (penetration > max)
			{
				max = penetration;
				index = i;
			}
		}
		if (index == m_RigidContacts.size())
			break;

		m_RigidContacts[index].MatchAwakeState();
		m_RigidContacts[index].ApplyPositionChange(linearChange, angularChange, max);

		for (i = 0; i < m_RigidContacts.size(); i++)
		{
			for (unsigned int body = 0; body < 2; body++)
			{
				if (m_RigidContacts[i].GetRigidBody(body))
				{
					for (unsigned int d = 0; d < 2; d++)
					{
						if (m_RigidContacts[i].GetRigidBody(body) == m_RigidContacts[index].GetRigidBody(d))
						{
							deltaPosition = linearChange[d] + angularChange[d] * m_RigidContacts[i].GetRelativeContactPosition(body);

							float penetration = m_RigidContacts[i].GetPenetration();
							penetration += deltaPosition.Dot(m_RigidContacts[i].GetContactNormal()) * (body ? 1 : -1);
							m_RigidContacts[i].SetPenetration(penetration);
						}
					}
				}
			}
		}
		m_PositionIterationsUsed++;
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::adjustVelocities(float deltaTime)
{
	Vector3D velocityChange[2];
	Vector3D rotationChange[2];
	Vector3D deltaVelocity;

	m_VelocityIterationsUsed = 0;
	while (m_VelocityIterationsUsed < m_VelocityIterations)
	{
		float max = m_VelocityEpsilon;
		unsigned int index = m_RigidContacts.size();
		for (unsigned int i = 0; i < m_RigidContacts.size(); i++)
		{
			if (m_RigidContacts[i].GetDesiredDeltaVelocity() > max)
			{
				max = m_RigidContacts[i].GetDesiredDeltaVelocity();
				index = i;
			}
		}

		if (index == m_RigidContacts.size())
			break;

		m_RigidContacts[index].MatchAwakeState();
		m_RigidContacts[index].ApplyVelocityChange(velocityChange, rotationChange);

		for (unsigned int i = 0; i < m_RigidContacts.size(); i++)
		{
			for (unsigned int b = 0; b < 2; b++)
			{
				if (m_RigidContacts[i].GetRigidBody(b))
				{
					for (unsigned d = 0; d < 2; d++)
					{
						if (m_RigidContacts[i].GetRigidBody(b) == m_RigidContacts[index].GetRigidBody(d))
						{
							deltaVelocity = velocityChange[d] + rotationChange[d] * m_RigidContacts[i].GetRelativeContactPosition(b);

							m_RigidContacts[i].SetContactVelocity(m_RigidContacts[i].GetContactVelocity() + m_RigidContacts[i].GetContactToWorld().TransformTranspose(deltaVelocity) * (float)(b ? -1 : 1));
							m_RigidContacts[i].CalculateDesiredDeltavelocity(deltaTime);
						}
					}
				}
			}
		}
		m_VelocityIterationsUsed++;
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::addRunTimeContactGenerators()
{
	std::vector<ContactGenerator*>::iterator contactGeneratorIter;
	for (contactGeneratorIter = mp_ToAddContactGenerators.begin(); contactGeneratorIter != mp_ToAddContactGenerators.end(); contactGeneratorIter++)
	{
		mp_ContactGenerators.push_back((*contactGeneratorIter));
	}

	mp_ToAddContactGenerators.clear();
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
	int checkCount = checkCollisions() * 2 -1;
	m_Collisions = m_Contacts.size();
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

	addRunTimeContactGenerators();
}

//-----------------------------------------------------------------------------
void CollisionHandler::Reset()
{
	mp_ContactGenerators.clear();
	mp_RigidContactGenerators.clear();
	mp_ToAddContactGenerators.clear();
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddGround(PhysicsObject* groundObject)
{
	mp_ContactGenerators.push_back(new GroundContactGenerator(groundObject->GetPosition().Y));
	mp_RigidContactGenerators.push_back(new RigidGroundContactGenerator(groundObject->GetPosition().Y));
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddCollisionObject(PhysicsObject* physicsObject)
{
	mp_PhysicsObjects.push_back(physicsObject);
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddCollisionObject(RigidBody* rigidBody)
{
	mp_RigidBodies.push_back(rigidBody);
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddCollisionObjects(std::vector<RigidBody*> rigidBodies)
{
	std::vector<RigidBody*>::iterator rigidBodyIter;
	for (rigidBodyIter = rigidBodies.begin(); rigidBodyIter != rigidBodies.end(); rigidBodyIter++)
	{
		mp_RigidBodies.push_back(*rigidBodyIter);
	}
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
void CollisionHandler::AddRunTimeContactGenerator(ContactGenerator* contactGeneraor)
{
	mp_ToAddContactGenerators.push_back(contactGeneraor);
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddContactGenerators(std::vector<ContactGenerator*> contactGenerators)
{
	mp_ContactGenerators.insert(mp_ContactGenerators.end(), contactGenerators.begin(), contactGenerators.end());
}
//=============================================================================