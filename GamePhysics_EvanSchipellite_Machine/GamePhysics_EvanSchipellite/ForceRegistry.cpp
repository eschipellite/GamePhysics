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
void ForceRegistry::AddForceRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject)
{
	m_ForceRegistration.push_back(ForceRegistration(forceGenerator, physicsObject));
}

//-----------------------------------------------------------------------------
void ForceRegistry::RemoveForceRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject)
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
void ForceRegistry::Clear()
{
	m_ForceRegistration.clear();
}

//-----------------------------------------------------------------------------
void ForceRegistry::UpdateForces()
{
	updateForceGenerators();
}
//=============================================================================
