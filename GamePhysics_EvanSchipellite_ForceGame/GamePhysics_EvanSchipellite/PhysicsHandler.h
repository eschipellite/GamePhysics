//=============================================================================
//                              PhysicsHandler
//
// Written by Evan Schipellite
//
// Holds onto all Physics-based objects
// Updates, draws, and applies generators to objects
//=============================================================================
#ifndef PHYSICSHANDLER_H
#define PHYSICSHANDLER_H
//=============================================================================
#include <vector>
#include "ForceGenerator.h"
#include "ForceRegistry.h"
#include "CollisionHandler.h"
//=============================================================================
//                              Register
//
// Written by Evan Schipellite
//
// Force Registration with GeneratorType
//=============================================================================
class ForceRegister
{
public:
	ForceGenerator* _ForceGenerator;
	PhysicsObject* _PhysicsObjectOne;
	PhysicsObject* _PhysicsObjectTwo;
public:
	ForceRegister() {};
	
	ForceRegister(ForceGenerator* forceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo = NULL)
	{
		_ForceGenerator = forceGenerator;
		_PhysicsObjectOne = physicsObjectOne;
		_PhysicsObjectTwo = physicsObjectTwo;
	}

	~ForceRegister() {};
};
//=============================================================================

//=============================================================================
class PhysicsHandler
{
private:
	std::vector<ForceGenerator*> m_ForceGenerators;
	ForceRegistry* m_ForceRegistry;
	CollisionHandler* mp_CollisionHandler;

private:
	void cleanUpForceGenerators();

public:
	PhysicsHandler();
	~PhysicsHandler();

	void Initialize();
	void Update(float deltaTime);
	void Reset();
	void CleanUp();

	void AddToRegistry(ForceGenerator* forceGenerator, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo = NULL);
	void AddToRegistry(ForceRegister forceRegister);
	void AddToRegistry(std::vector<ForceRegister> forceRegisters);

	void AddContactGenerators(std::vector<ContactGenerator*> contactGenerators);

	void AddGround(PhysicsObject* groundObject);
	void AddCollisionObject(PhysicsObject* physicsObject);
	void AddCollisionObjects(std::vector<PhysicsObject*> physicsObjects);
};
//=============================================================================
#endif //PHYSICSHANDLER_H

