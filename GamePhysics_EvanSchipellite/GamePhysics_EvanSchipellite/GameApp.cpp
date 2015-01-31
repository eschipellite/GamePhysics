//=============================================================================
//                              GameApp
//
// Written by Evan Schipellite
//
// Holds all GameApp functionality
//=============================================================================
#include "GameApp.h"
#include <iostream>

using namespace std;
//=============================================================================
GameApp::GameApp()
{
	mp_Camera = new Camera();
	m_PhysicsHandler = new PhysicsHandler();
	m_PlanetHandler = new PlanetHandler();
}

//-----------------------------------------------------------------------------
GameApp::~GameApp()
{
	CleanUp();
}

//-----------------------------------------------------------------------------
void GameApp::Initialize()
{
	mp_Camera->Initialize(Vector3D(0, 0, 0));
	m_PhysicsHandler->Initialize();
	m_PlanetHandler->Initialize();

	m_PhysicsHandler->AddToRegistry(m_PlanetHandler->GetForceRegisters());
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

	if (m_PhysicsHandler != NULL)
	{
		m_PhysicsHandler->CleanUp();
	}
	delete m_PhysicsHandler;
	m_PhysicsHandler = nullptr;

	if (m_PlanetHandler != NULL)
	{
		m_PlanetHandler->CleanUp();
	}
	delete m_PlanetHandler;
	m_PlanetHandler = nullptr;
}

//-----------------------------------------------------------------------------
void GameApp::Update(float deltaTime, const EditorState* physicsState)
{
	mp_Camera->Update();

	if (!physicsState->GetIsPaused())
	{
		m_PhysicsHandler->Update(deltaTime);

		m_PlanetHandler->Update(deltaTime);
	}
}

//-----------------------------------------------------------------------------
void GameApp::Draw()
{
	m_PlanetHandler->Draw();
}

//-----------------------------------------------------------------------------
void GameApp::Reset()
{
	m_PhysicsHandler->Reset();

	m_PlanetHandler->Reset();
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
