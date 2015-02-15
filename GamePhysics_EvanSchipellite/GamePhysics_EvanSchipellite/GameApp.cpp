//=============================================================================
//                              GameApp
//
// Written by Evan Schipellite
//
// Holds all GameApp functionality
//=============================================================================
#define _USE_MATH_DEFINES

#include "Skybox.h"
#include "GameApp.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <sstream>
//=============================================================================
float GameApp::ms_TimeStep = 50;
//=============================================================================
GameApp::GameApp()
{
	mp_Camera = new Camera();
	mp_PhysicsHandler = new PhysicsHandler();
	mp_PlanetHandler = new PlanetHandler();
	mp_Skybox = new Skybox();

	m_FocusIndex = -1;
}

//-----------------------------------------------------------------------------
GameApp::~GameApp()
{
	CleanUp();
}

//-----------------------------------------------------------------------------
void GameApp::setFocus(unsigned char key)
{
	int index = -1;

	switch (key)
	{
	case ('1') :
		index = 0;
		break;
	case ('2') :
		index = 1;
		break;
	case ('3') :
		index = 2;
		break;
	case ('4') :
		index = 3;
		break;
	case ('5') :
		index = 4;
		break;
	case ('6') :
		index = 5;
		break;
	case ('7') :
		index = 6;
		break;
	case ('8') :
		index = 7;
		break;
	case ('9') :
		index = 8;
		break;
	case ('0') :
		index = 9;
		break;
	}

	if (index >= 0)
	{
		focusPlanet(index);
	}
}

//-----------------------------------------------------------------------------
void GameApp::focusPlanet(int index)
{
	Planet* planet = mp_PlanetHandler->GetPlanetAtIndex(index);

	mp_Camera->SetFollow(planet);

	std::string planetName = "Name: " + planet->GetPlanetName();
	mp_PlanetName->set_text(planetName.c_str());
	std::string planetMass = "Mass: " + convertFloatToString(planet->GetMass());
	mp_PlanetMass->set_text(planetMass.c_str());

	m_FocusIndex = index;
}

//-----------------------------------------------------------------------------
std::string GameApp::convertFloatToString(float value)
{
	std::ostringstream out;
	out << std::setprecision(20) << value;
	return out.str();
}

//-----------------------------------------------------------------------------
std::string GameApp::convertVector3DToString(Vector3D vector3D)
{
	std::string x = convertFloatToString(vector3D.X);
	std::string y = convertFloatToString(vector3D.Y);
	std::string z = convertFloatToString(vector3D.Z);

	return "Vector3D(" + x + ", " + y + ", " + z + ")";
}

//-----------------------------------------------------------------------------
void GameApp::updateFocusPlanetUI()
{
	if (m_FocusIndex >= 0)
	{
		Planet* planet = mp_PlanetHandler->GetPlanetAtIndex(m_FocusIndex);
		
		Vector3D currentVelocity = planet->GetCurrentVelocity();
		std::string currentVelocityString = convertVector3DToString(currentVelocity);
		std::string planetVelocity = "Velocity: " + currentVelocityString;
		mp_PlanetVelocity->set_text(planetVelocity.c_str());

		Vector3D currentAcceleration = planet->GetCurrentAcceleration();
		std::string currentAccelerationString = convertVector3DToString(currentAcceleration);
		std::string planetAcceleration = "Acceleration: " + currentAccelerationString;
		mp_PlanetAcceleration->set_text(planetAcceleration.c_str());

		Vector3D totalForce = planet->GetPreviousTotalForce();
		std::string totalForceString = convertVector3DToString(totalForce);
		std::string planetTotalForce = "Total Force: " + totalForceString;
		mp_TotalPlanetForce->set_text(planetTotalForce.c_str());
	}
}

//-----------------------------------------------------------------------------
void GameApp::Initialize()
{
	mp_PhysicsHandler->Initialize();
	mp_PlanetHandler->Initialize();
	mp_Skybox->Initialize("Content/Space/Space_Front.jpg", "Content/Space/Space_Back.jpg", "Content/Space/Space_Top.jpg", "Content/Space/Space_Bottom.jpg",
		"Content/Space/Space_Right.jpg", "Content/Space/Space_Left.jpg");

	float distanceFromPlanet = 3;
	Vector3D centerPosition = mp_PlanetHandler->GetPlanetAtIndex(0)->GetPosition();
	Vector3D centerRotation = Vector3D(90.0f, 0, 0);
	centerPosition.Y += distanceFromPlanet;
	mp_Camera->Initialize(centerPosition, centerRotation, distanceFromPlanet);

	mp_PhysicsHandler->AddToRegistry(mp_PlanetHandler->GetForceRegisters());
}

//-----------------------------------------------------------------------------
void GameApp::SetTextReferences(GLUI_StaticText* planetName, GLUI_StaticText* planetMass, GLUI_StaticText* planetVelocity, GLUI_StaticText* planetAcceleration, GLUI_StaticText* totalPlanetForce)
{
	mp_PlanetName = planetName;
	mp_PlanetMass = planetMass;
	mp_PlanetVelocity = planetVelocity;
	mp_PlanetAcceleration = planetAcceleration;
	mp_TotalPlanetForce = totalPlanetForce;
}

//-----------------------------------------------------------------------------
void GameApp::Start()
{
	setFocus('1');
}

//-----------------------------------------------------------------------------
void GameApp::CleanUp()
{
	if (mp_Camera != NULL)
	{
		mp_Camera->CleanUp();
	}
	delete mp_Camera;
	mp_Camera = nullptr;

	if (mp_PhysicsHandler != NULL)
	{
		mp_PhysicsHandler->CleanUp();
	}
	delete mp_PhysicsHandler;
	mp_PhysicsHandler = nullptr;

	if (mp_PlanetHandler != NULL)
	{
		mp_PlanetHandler->CleanUp();
	}
	delete mp_PlanetHandler;
	mp_PlanetHandler = nullptr;

	if (mp_Skybox != NULL)
	{
		mp_Skybox->CleanUp();
	}
	delete mp_Skybox;
	mp_Skybox = nullptr;
}

//-----------------------------------------------------------------------------
void GameApp::Update(float deltaTime, const EditorState* physicsState)
{
	mp_Camera->Update();

	if (!physicsState->GetIsPaused())
	{
		int currentTime = 0;

		while (currentTime < ms_TimeStep)
		{
			mp_PhysicsHandler->Update(deltaTime);

			mp_PlanetHandler->Update(deltaTime);
			currentTime++;
		}
	}

	updateFocusPlanetUI();
}

//-----------------------------------------------------------------------------
void GameApp::Draw()
{
	mp_PlanetHandler->Draw();

	mp_Skybox->Render();
}

//-----------------------------------------------------------------------------
void GameApp::Reset()
{
	mp_PhysicsHandler->Reset();

	mp_PlanetHandler->Reset();

	mp_Camera->Reset();
}

//-----------------------------------------------------------------------------
void GameApp::UpdateScreenSize(Vector3D screenSize)
{
	mp_Camera->UpdateScreenSize(screenSize);
}

//-----------------------------------------------------------------------------
void GameApp::HandleMouse(Vector3D mousePosition)
{
	mp_Camera->HandleMouse(mousePosition);
}

//-----------------------------------------------------------------------------
void GameApp::HandleKeyPressed(unsigned char key)
{
	mp_Camera->HandleKeyPressed(key);
}

//-----------------------------------------------------------------------------
void GameApp::HandleKeyReleased(unsigned char key)
{
	mp_Camera->HandleKeyReleased(key);

	setFocus(key);
}
//=============================================================================
