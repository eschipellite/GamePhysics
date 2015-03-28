//=============================================================================
//                              PhysicsHandler
//
// Written by Evan Schipellite
//
// Holds onto all Physics-based objects
// Updates, draws, and applies generators to objects
//=============================================================================
#include "PhysicsHandler.h"
#include "EarthGravityGenerator.h"
//=============================================================================
PhysicsHandler::PhysicsHandler()
{
	m_ForceRegistry = new ForceRegistry();
	mp_CollisionHandler = new CollisionHandler();
}

//-----------------------------------------------------------------------------
PhysicsHandler::~PhysicsHandler()
{
}

//-----------------------------------------------------------------------------
void PhysicsHandler::Initialize()
{
	m_ForceGenerators.push_back(new EarthGravityGenerator(Vector3D(0, -9.8f, 0)));

	mp_CollisionHandler->Initialize();
}

//-----------------------------------------------------------------------------
void PhysicsHandler::Update(float deltaTime)
{
	m_ForceRegistry->UpdateForces();
	mp_CollisionHandler->Update(deltaTime);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::Reset()
{
}

//-----------------------------------------------------------------------------
void PhysicsHandler::CleanUp()
{
	cleanUpForceGenerators();
	
	if (mp_CollisionHandler != NULL)
	{
		mp_CollisionHandler->CleanUp();
	}
	delete mp_CollisionHandler;
	mp_CollisionHandler = nullptr;
}

//-----------------------------------------------------------------------------
void PhysicsHandler::cleanUpForceGenerators()
{
	std::vector<ForceGenerator*>::iterator iter;
	for (iter = m_ForceGenerators.begin(); iter != m_ForceGenerators.end(); iter++)
	{
		delete *iter;
	}

	m_ForceGenerators.clear();
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddToRegistry(ForceGenerator* forceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	m_ForceRegistry->AddForceRegistration(forceGenerator, physicsObjectOne);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddToRegistry(ForceRegister forceRegister)
{
	AddToRegistry(forceRegister._ForceGenerator, forceRegister._PhysicsObjectOne, forceRegister._PhysicsObjectTwo);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddToRegistry(std::vector<ForceRegister> forceRegisters)
{
	std::vector<ForceRegister>::iterator forceRegisterIter;
	for (forceRegisterIter = forceRegisters.begin(); forceRegisterIter != forceRegisters.end(); forceRegisterIter++)
	{
		AddToRegistry(*forceRegisterIter);
	}
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddGround(PhysicsObject* groundObject)
{
	mp_CollisionHandler->AddGround(groundObject);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddCollisionObject(PhysicsObject* physicsObject)
{
	mp_CollisionHandler->AddCollisionObject(physicsObject);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddCollisionObjects(std::vector<PhysicsObject*> physicsObjects)
{
	mp_CollisionHandler->AddCollisionObjects(physicsObjects);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddContactGenerators(std::vector<ContactGenerator*> contactGenerators)
{
	mp_CollisionHandler->AddContactGenerators(contactGenerators);
}
//=============================================================================