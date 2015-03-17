//=============================================================================
//                              Planet Handler
//
// Written by Evan Schipellite
//
// Manages all orbiting planets
//=============================================================================
#ifndef PLANETHANDLER_H
#define PLANETHANDLER_H
//=============================================================================
#include "Planet.h"
#include <vector>
#include "PhysicsHandler.h"
//=============================================================================
class PlanetHandler
{
private:
	std::vector<Planet*> m_Planets;
public:
	PlanetHandler();
	~PlanetHandler();

	void Initialize();
	void Update(float deltaTime);
	void Draw();
	void Reset();
	void CleanUp();

	std::vector<ForceRegister> GetForceRegisters();
	Planet* GetPlanetAtIndex(int index);
};
//=============================================================================
#endif //PLANETHANDLER_H

