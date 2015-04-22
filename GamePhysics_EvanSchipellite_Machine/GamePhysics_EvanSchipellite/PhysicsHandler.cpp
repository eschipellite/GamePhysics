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
	updateRigidBodies(deltaTime);
	mp_CollisionHandler->Update(deltaTime);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::Reset()
{
	mp_CollisionHandler->Reset();
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

	mp_RigidBodies.clear();
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
void PhysicsHandler::updateRigidBodies(float deltaTime)
{
	std::vector<RigidBody*>::iterator rigidBodyIter;
	for (rigidBodyIter = mp_RigidBodies.begin(); rigidBodyIter != mp_RigidBodies.end(); rigidBodyIter++)
	{
		(*rigidBodyIter)->Integrate(deltaTime);
	}
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddToRegistry(ForceGenerator* forceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	m_ForceRegistry->AddForceRegistration(forceGenerator, physicsObjectOne);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddToRegistry(ForceGenerator* forceGenerator, RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo)
{
	m_ForceRegistry->AddForceRegistration(forceGenerator, rigidBodyOne);
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
void PhysicsHandler::AddRigidBody(RigidBody* rigidBody)
{
	mp_RigidBodies.push_back(rigidBody);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddRigidBodies(std::vector<RigidBody*> rigidBodies)
{
	std::vector<RigidBody*>::iterator rigidBodyIter;
	for (rigidBodyIter = rigidBodies.begin(); rigidBodyIter != rigidBodies.end(); rigidBodyIter++)
	{
		mp_RigidBodies.push_back((*rigidBodyIter));
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
void PhysicsHandler::AddCollisionObject(RigidBody* rigidBody)
{
	//mp_CollisionHandler->AddCollisionObject(rigidBody);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddCollisionObjects(std::vector<RigidBody*> rigidBodies)
{
	//mp_CollisionHandler->AddCollisionObjects(rigidBodies);
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddContactGenerators(std::vector<ContactGenerator*> contactGenerators)
{
	mp_CollisionHandler->AddContactGenerators(contactGenerators);
}
//=============================================================================