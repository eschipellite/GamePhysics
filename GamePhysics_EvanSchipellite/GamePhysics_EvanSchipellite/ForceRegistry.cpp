//=============================================================================
//                              Force Registry
//
// Written by Evan Schipellite
//
// Handles all force registrations
//=============================================================================
#include "ForceRegistry.h"
//=============================================================================
ForceRegistry::ForceRegistry()
{
}

//-----------------------------------------------------------------------------
ForceRegistry::~ForceRegistry()
{
}

//-----------------------------------------------------------------------------
void ForceRegistry::updateForceGenerators()
{
	std::vector<ForceRegistration>::iterator iter;
	for (iter = m_ForceRegistration.begin(); iter != m_ForceRegistration.end(); iter++)
	{
		(*iter).Update();
	}
}

//-----------------------------------------------------------------------------
void ForceRegistry::updateObjectForceGenerators()
{
	std::vector<ObjectForceRegistration>::iterator iter;
	for (iter = m_ObjectForceRegistration.begin(); iter != m_ObjectForceRegistration.end(); iter++)
	{
		(*iter).Update();
	}
}

//-----------------------------------------------------------------------------
void ForceRegistry::AddRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject)
{
	m_ForceRegistration.push_back(ForceRegistration(forceGenerator, physicsObject));
}

//-----------------------------------------------------------------------------
void ForceRegistry::AddRegistration(ObjectForceGenerator* objectForceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	m_ObjectForceRegistration.push_back(ObjectForceRegistration(objectForceGenerator, physicsObjectOne, physicsObjectTwo));
}

//-----------------------------------------------------------------------------
void ForceRegistry::RemoveRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject)
{
	std::vector<ForceRegistration>::iterator iter;
	for (iter = m_ForceRegistration.begin(); iter != m_ForceRegistration.end(); iter++)
	{
		if ((*iter).GetForceGenerator() == forceGenerator && (*iter).GetPhysicsObject() == physicsObject)
		{
			m_ForceRegistration.erase(iter);
			break;
		}
	}
}

//-----------------------------------------------------------------------------
void ForceRegistry::RemoveRegistration(ObjectForceGenerator* objectForceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo)
{
	std::vector<ObjectForceRegistration>::iterator iter;
	for (iter = m_ObjectForceRegistration.begin(); iter != m_ObjectForceRegistration.end(); iter++)
	{
		if ((*iter).GetObjectForceGenerator() == objectForceGenerator && (*iter).GetPhysicsOneObject() == physicsObjectOne && (*iter).GetPhysicsTwoObject() == physicsObjectTwo)
		{
			m_ObjectForceRegistration.erase(iter);
			break;
		}
	}
}

//-----------------------------------------------------------------------------
void ForceRegistry::Clear()
{
	m_ForceRegistration.clear();
	m_ObjectForceRegistration.clear();
}

//-----------------------------------------------------------------------------
void ForceRegistry::UpdateForces()
{
	updateForceGenerators();
	updateObjectForceGenerators();
}
//=============================================================================
