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
#include "ObjectForceGenerator.h"
#include "ForceRegistry.h"
#include "Generator.h"
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
	GeneratorType _GeneratorType;
	PhysicsObject* _PhysicsObjectOne;
	PhysicsObject* _PhysicsObjectTwo;
public:
	ForceRegister() {};
	
	ForceRegister(GeneratorType generatorType, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo = NULL)
	{
		_GeneratorType = generatorType;
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
	std::vector<ObjectForceGenerator*> m_ObjectForceGenerators;
	ForceRegistry* m_ForceRegistry;

private:
	void cleanUpForceGenerators();
	void cleanUpObjectForceGenerators();

	ForceGenerator* getForceGeneratorFromType(GeneratorType generatorType);
	ObjectForceGenerator* getObjectForceGeneratorFromType(GeneratorType generatorType);

public:
	PhysicsHandler();
	~PhysicsHandler();

	void Initialize();
	void Update(float deltaTime);
	void Reset();
	void CleanUp();

	void AddToRegistry(GeneratorType generatorType, PhysicsObject* physicsObjectOne, PhysicsObject* physicsObjectTwo = NULL);
	void AddToRegistry(ForceRegister forceRegister);
	void AddToRegistry(std::vector<ForceRegister> forceRegisters);
};
//=============================================================================
#endif //PHYSICSHANDLER_H

