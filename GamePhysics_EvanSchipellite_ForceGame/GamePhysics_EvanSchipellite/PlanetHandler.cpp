//=============================================================================
//                              PlanetHandler
//
// Written by Evan Schipellite
//
// Manages all orbiting planets
//=============================================================================
#include "PlanetHandler.h"
#include "GravityGenerator.h"
//=============================================================================
PlanetHandler::PlanetHandler()
{
}

//-----------------------------------------------------------------------------
PlanetHandler::~PlanetHandler()
{
}

//-----------------------------------------------------------------------------
// http://en.wikipedia.org/wiki/Orbital_speed Gives Earth's velocity
// http://www.smartconversion.com/otherInfo/Mass_of_planets_and_the_Sun.aspx
// http://www.astronomynotes.com/tables/tablesb.htm
// http://www.sjsu.edu/faculty/watkins/orbital.htm Gives ratios for velocities
// Mass / Distance Conversions from Robert Bethune
// http://sciencenetlinks.com/interactives/messenger/psc/PlanetSize.html Provides size ratios
void PlanetHandler::Initialize()
{
	Planet* sun = new Planet();
	sun->Initialize(.25f, 1.0f, Vector3D(0, 0, 0), Vector3D(0, 0, 0), "Sun", "Content/Planets/Sun.jpg");
	m_Planets.push_back(sun);

	Planet* mercury = new Planet();
	mercury->Initialize(0.05f, 0.0000001666f, Vector3D(.31f, 0, 0), Vector3D(0, 0, .0000003925392803303289f), "Mercury", "Content/Planets/Mercury.jpg");
	m_Planets.push_back(mercury);

	Planet* venus = new Planet();
	venus->Initialize(0.1f, 0.000002447f, Vector3D(.718f, 0, 0), Vector3D(0, 0, 0.0000002377854700252f), "Venus", "Content/Planets/Venus.jpg");
	m_Planets.push_back(venus);

	Planet* earth = new Planet();
	earth->Initialize(0.1f, 0.000003003f, Vector3D(0.98f, 0, 0), Vector3D(0, 0, 0.000000202542989816901f), "Earth", "Content/Planets/Earth.jpg");
	m_Planets.push_back(earth);

	Planet* mars = new Planet();
	mars->Initialize(0.08f, 0.0000003232f, Vector3D(1.38f, 0, 0), Vector3D(0, 0, 0.0000001624394778196f), "Mars", "Content/Planets/Mars.jpg");
	m_Planets.push_back(mars);

	Planet* jupiter = new Planet();
	jupiter->Initialize(1.1f, 0.0009547919f, Vector3D(4.95f, 0, 0), Vector3D(0, 0, 0.0000000879036575732f), "Jupiter", "Content/Planets/Jupiter.jpg");
	m_Planets.push_back(jupiter);

	Planet* saturn = new Planet();
	saturn->Initialize(0.941f, 0.000285885f, Vector3D(9.02f, 0, 0), Vector3D(0, 0, 0.0000000654213857054f), "Saturn", "Content/Planets/Saturn.jpg");
	m_Planets.push_back(saturn);

	Planet* uranus = new Planet();
	uranus->Initialize(0.4f, 0.000043662f, Vector3D(18.3f, 0, 0), Vector3D(0, 0, 0.0000000461798016744f), "Uranus", "Content/Planets/Uranus.jpg");
	m_Planets.push_back(uranus);

	Planet* neptune = new Planet();
	neptune->Initialize(0.388f, 0.000051513f, Vector3D(30.0f, 0, 0), Vector3D(0, 0, 0.0000000368628241436f), "Neptune", "Content/Planets/Neptune.jpg");
	m_Planets.push_back(neptune);

	//Probably not perfect
	Planet* earthMoon = new Planet();
	earthMoon->Initialize(0.025f, 0.0000000000000123f, Vector3D(0.979f, 0, 0), Vector3D(0, 0, (float)(0.0000002059429908 + 0.000000007197722768554639)), "Earth Moon", "Content/Planets/Moon.jpg");
	m_Planets.push_back(earthMoon);
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
			forceRegisters.push_back(ForceRegister(new GravityGenerator(), *firstPlanet, *secondPlanet));
		}
	}

	return forceRegisters;
}

//-----------------------------------------------------------------------------
Planet* PlanetHandler::GetPlanetAtIndex(int index)
{
	return m_Planets[index];
}
//=============================================================================
