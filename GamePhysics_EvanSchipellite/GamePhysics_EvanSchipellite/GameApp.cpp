//=============================================================================
//                              GameApp
//
// Written by Evan Schipellite
//
// Holds all GameApp functionality
//=============================================================================
#define _USE_MATH_DEFINES

#include "GameApp.h"
#include <iostream>
#include <math.h>

using namespace std;
//=============================================================================
float GameApp::ms_TimeStep = 50;
//=============================================================================
GameApp::GameApp()
{
	mp_Camera = new Camera();
	mp_PhysicsHandler = new PhysicsHandler();
	mp_PlanetHandler = new PlanetHandler();
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
	}

	if (index >= 0)
	{
		mp_Camera->SetFollow(mp_PlanetHandler->GetPlanetAtIndex(index));
	}
}

//-----------------------------------------------------------------------------
void GameApp::Initialize()
{
	mp_PhysicsHandler->Initialize();
	mp_PlanetHandler->Initialize();

	float distanceFromPlanet = 3;
	Vector3D centerPosition = mp_PlanetHandler->GetPlanetAtIndex(0)->GetPosition();
	Vector3D centerRotation = Vector3D(90.0f, 0, 0);
	centerPosition.Y += distanceFromPlanet;
	mp_Camera->Initialize(centerPosition, centerRotation, distanceFromPlanet);

	mp_PhysicsHandler->AddToRegistry(mp_PlanetHandler->GetForceRegisters());
}

void GameApp::Start()
{
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
}

//-----------------------------------------------------------------------------
void GameApp::Draw()
{
	mp_PlanetHandler->Draw();
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
