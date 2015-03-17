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
}

//-----------------------------------------------------------------------------
PhysicsHandler::~PhysicsHandler()
{
}

//-----------------------------------------------------------------------------
void PhysicsHandler::Initialize()
{
	m_ForceGenerators.push_back(new EarthGravityGenerator(Vector3D(0, -9.8, 0)));
}

//-----------------------------------------------------------------------------
void PhysicsHandler::Update(float deltaTime)
{
	m_ForceRegistry->UpdateForces();
}

//-----------------------------------------------------------------------------
void PhysicsHandler::Reset()
{
}

//-----------------------------------------------------------------------------
void PhysicsHandler::CleanUp()
{
	cleanUpForceGenerators();
	cleanUpObjectForceGenerators();
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
void PhysicsHandler::cleanUpObjectForceGenerators()
{
	std::vector<ObjectForceGenerator*>::iterator iter;
	for (iter = m_ObjectForceGenerators.begin(); iter != m_ObjectForceGenerators.end(); iter++)
	{
		delete *iter;
	}

	m_ObjectForceGenerators.clear();
}

//-----------------------------------------------------------------------------
ForceGenerator* PhysicsHandler::getForceGeneratorFromType(GeneratorType generatorType)
{
	std::vector<ForceGenerator*>::iterator iter;
	for (iter = m_ForceGenerators.begin(); iter != m_ForceGenerators.end(); iter++)
	{
		if ((*iter)->GetGeneratorType() == generatorType)
		{
			return (*iter);
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
ObjectForceGenerator* PhysicsHandler::getObjectForceGeneratorFromType(GeneratorType generatorType)
{
	std::vector<ObjectForceGenerator*>::iterator iter;
	for (iter = m_ObjectForceGenerators.begin(); iter != m_ObjectForceGenerators.end(); iter++)
	{
		if ((*iter)->GetGeneratorType() == generatorType)
		{
			return (*iter);
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddToRegistry(GeneratorType generatorType, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	if (physicsObjectTwo == NULL)
	{
		ForceGenerator* forceGenerator = getForceGeneratorFromType(generatorType);

		if (forceGenerator != NULL)
		{
			m_ForceRegistry->AddRegistration(forceGenerator, physicsObjectOne);
		}
	}
	else
	{
		ObjectForceGenerator* objectForceGenerator = getObjectForceGeneratorFromType(generatorType);

		if (objectForceGenerator != NULL)
		{
			m_ForceRegistry->AddRegistration(objectForceGenerator, physicsObjectOne, physicsObjectTwo);
		}
	}
}

//-----------------------------------------------------------------------------
void PhysicsHandler::AddToRegistry(ForceRegister forceRegister)
{
	AddToRegistry(forceRegister._GeneratorType, forceRegister._PhysicsObjectOne, forceRegister._PhysicsObjectTwo);
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
//=============================================================================