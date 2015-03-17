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
#include "Level.h"
//=============================================================================
float GameApp::ms_TimeStep = 1;
//=============================================================================
GameApp::GameApp()
{
	mp_Camera = new Camera();
	mp_PhysicsHandler = new PhysicsHandler();
	mp_Skybox = new Skybox();
	mp_Level = new Level();

	m_FocusIndex = -1;
}

//-----------------------------------------------------------------------------
GameApp::~GameApp()
{
	CleanUp();
}

//-----------------------------------------------------------------------------
void GameApp::Initialize()
{
	mp_PhysicsHandler->Initialize();
	mp_Skybox->Initialize("Content/Skybox/Pond/Pond_Front.bmp", "Content/Skybox/Pond/Pond_Back.bmp", "Content/Skybox/Pond/Pond_Up.bmp", "Content/Skybox/Pond/Pond_Down.bmp",
		"Content/Skybox/Pond/Pond_Right.bmp", "Content/Skybox/Pond/Pond_Left.bmp");

	Vector3D centerPosition = Vector3D(0, 0, 0);
	Vector3D centerRotation = Vector3D(0, 0, 0);
	mp_Camera->Initialize(centerPosition, centerRotation);

	mp_Level->Initialize(Vector3D(50, 1, 50), "Content/Textures/Texture_Grass.png", Vector3D(0, 2, 0), "Content/Textures/Texture_Player.jpg");

	mp_PhysicsHandler->AddToRegistry(mp_Level->GetForceRegisters());
}

//-----------------------------------------------------------------------------
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

	if (mp_Skybox != NULL)
	{
		mp_Skybox->CleanUp();
	}
	delete mp_Skybox;
	mp_Skybox = nullptr;

	if (mp_Level != NULL)
	{
		mp_Level->CleanUp();
	}
	delete mp_Level;
	mp_Level = nullptr;
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
			mp_Level->Update(deltaTime);

			currentTime++;
		}
	}
}

//-----------------------------------------------------------------------------
void GameApp::Draw()
{
	mp_Skybox->Render();

	mp_Level->Draw();
}

//-----------------------------------------------------------------------------
void GameApp::Reset()
{
	mp_PhysicsHandler->Reset();
	mp_Camera->Reset();
	mp_Level->Reset();
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
}
//=============================================================================
