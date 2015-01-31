//=============================================================================
//                              PlanetHandler
//
// Written by Evan Schipellite
//
// Manages all orbiting planets
//=============================================================================
#include "PlanetHandler.h"
//=============================================================================
PlanetHandler::PlanetHandler()
{
}

//-----------------------------------------------------------------------------
PlanetHandler::~PlanetHandler()
{
}

//-----------------------------------------------------------------------------
void PlanetHandler::Initialize()
{
	Planet* sun = new Planet();
	sun->Initialize(0.5f, 1988500.0f, Vector3D(0, 0, 0), Vector3D(0, 0, 0), "Sun");
	m_Planets.push_back(sun);

	Planet* earth = new Planet();
	earth->Initialize(0.25f, 5.9725f, Vector3D(1.5, 0, 0), Vector3D(0, 0, 1), "Earth");
	m_Planets.push_back(earth);
}

//-----------------------------------------------------------------------------
void PlanetHandler::Update(float deltaTime)
{
	std::vector<Planet*>::iterator iter;
	for (iter = m_Planets.begin(); iter != m_Planets.end(); iter++)
	{
		(*iter)->Update(deltaTime);
	}
}

//-----------------------------------------------------------------------------
void PlanetHandler::Draw()
{
	std::vector<Planet*>::iterator iter;
	for (iter = m_Planets.begin(); iter != m_Planets.end(); iter++)
	{
		(*iter)->Draw();
	}
}

//-----------------------------------------------------------------------------
void PlanetHandler::Reset()
{
	std::vector<Planet*>::iterator iter;
	for (iter = m_Planets.begin(); iter != m_Planets.end(); iter++)
	{
		(*iter)->Reset();
	}
}

//-----------------------------------------------------------------------------
void PlanetHandler::CleanUp()
{
	std::vector<Planet*>::iterator iter;
	for (iter = m_Planets.begin(); iter != m_Planets.end(); iter++)
	{
		(*iter)->CleanUp();
		delete *iter;
	}

	m_Planets.clear();
}

//-----------------------------------------------------------------------------
std::vector<ForceRegister> PlanetHandler::GetForceRegisters()
{
	std::vector<ForceRegister> forceRegisters;

	std::vector<Planet*>::iterator firstPlanet;
	for (firstPlanet = m_Planets.begin(); firstPlanet != m_Planets.end(); firstPlanet++)
	{
		std::vector<Planet*>::iterator secondPlanet;
		for (secondPlanet = firstPlanet + 1; secondPlanet != m_Planets.end(); secondPlanet++)
		{
			forceRegisters.push_back(ForceRegister(GeneratorType::GRAVITY_GENERATOR, *firstPlanet, *secondPlanet));
		}
	}

	return forceRegisters;
}
//=============================================================================
