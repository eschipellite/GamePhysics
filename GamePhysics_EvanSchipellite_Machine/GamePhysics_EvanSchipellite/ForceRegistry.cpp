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

	std::vector<RigidForceRegistration>::iterator rigidIter;
	for (rigidIter = m_RigidForceRegistration.begin(); rigidIter != m_RigidForceRegistration.end(); rigidIter++)
	{
		(*rigidIter).Update();
	}
}

//-----------------------------------------------------------------------------
void ForceRegistry::AddForceRegistration(ForceGenerator* forceGenerator, PhysicsObject* physicsObject)
{
	m_ForceRegistration.push_back(ForceRegistration(forceGenerator, physicsObject));
}

//-----------------------------------------------------------------------------
void ForceRegistry::AddForceRegistration(ForceGenerator* forceGenerator, RigidBody* rigidBody)
{
	m_RigidForceRegistration.push_back(RigidForceRegistration(forceGenerator, rigidBody));
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
void ForceRegistry::RemoveForceRegistration(ForceGenerator* forceGenerator, RigidBody* rigidBody)
{
	std::vector<RigidForceRegistration>::iterator iter;
	for (iter = m_RigidForceRegistration.begin(); iter != m_RigidForceRegistration.end(); iter++)
	{
		if ((*iter).GetForceGenerator() == forceGenerator && (*iter).GetRigidBody() == rigidBody)
		{
			m_RigidForceRegistration.erase(iter);
			break;
		}
	}
}

//-----------------------------------------------------------------------------
void ForceRegistry::Clear()
{
	m_ForceRegistration.clear();
	m_RigidForceRegistration.clear();
}

//-----------------------------------------------------------------------------
void ForceRegistry::UpdateForces()
{
	updateForceGenerators();
}
//=============================================================================
